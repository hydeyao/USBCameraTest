#include "VideoDecode.h"
#include <mutex>
#include <qimage.h>

extern "C" { 
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libavutil/avutil.h"
#include "libswscale/swscale.h"
#include "libavutil/imgutils.h"
#include "libavdevice/avdevice.h"
}

using namespace std;

#define ERR_LEN 1024

#define ERR_RET(ret) showErr(ret);\
					 free();\
					 return false

VideoDecode::VideoDecode()
{
	initFFmpeg();
	mspErrBuf.reset(new char[ERR_LEN], [](char* p) {delete[] p; });
	m_inputFmt = av_find_input_format("dshow");
	if (!m_inputFmt)
	{
		cout << "Query AVInputFormat Fail" << endl;
	}

}

VideoDecode::~VideoDecode()
{
	close();
}

bool VideoDecode::open(const std::string& url, const std::string& resolution)
{
	if (url.size() == 0) return false;

	AVDictionary* config_dict = nullptr;
	av_dict_set(&config_dict, "input_format", "mjpeg", 0);
	av_dict_set(&config_dict, "video_size", resolution.c_str(), 0);

	//Open input stream
	int ret = avformat_open_input(&m_fmtCtx, url.data(), m_inputFmt, &config_dict);

	if (config_dict)
	{
		av_dict_free(&config_dict);
	}

	//Open Failed
	if (ret < 0)
	{
		ERR_RET(ret);
	}

	//Open Input To Query Stream Info
	ret = avformat_find_stream_info(m_fmtCtx, nullptr);
	if (ret < 0)
	{
		ERR_RET(ret);
	}

	//get video Len
	m_toltalTime = m_fmtCtx->duration / (AV_TIME_BASE / 1000);

	//get Video Stream index
	m_videoIdx = av_find_best_stream(m_fmtCtx, AVMEDIA_TYPE_VIDEO, -1, -1, nullptr, 0);
	if (m_videoIdx < 0)
	{
		ERR_RET(m_videoIdx);
	}

	AVStream* videoStream = m_fmtCtx->streams[m_videoIdx];
	msp_videoSize.reset(new VideoSize(videoStream->codecpar->width,videoStream->codecpar->height),\
		[](VideoSize* p) {delete p; });

	m_fps = rational2double(&videoStream->avg_frame_rate);
	const AVCodec* codec = avcodec_find_decoder(videoStream->codecpar->codec_id);
	m_toltalFrame = videoStream->nb_frames;
	
	printf("Resolution: [w:%s,h:%s] Fps: %s AllFrame: %s decoder: %s \n", \
		to_string(msp_videoSize->width).c_str(), to_string(msp_videoSize->height).c_str(), \
		to_string(m_fps).c_str(), to_string(m_toltalFrame).c_str(), codec->name);

	//alloc AVCodeCtx to Codec
	m_codeCtx = avcodec_alloc_context3(codec);
	if (!m_codeCtx)
	{
		cout << "Create Video CodeContext Fail \n";
		free();
		return false;
	}

	ret = avcodec_parameters_to_context(m_codeCtx, videoStream->codecpar);
	if (ret < 0)
	{
		ERR_RET(ret);
	}

	m_codeCtx->flags2 |= AV_CODEC_FLAG2_FAST;
	m_codeCtx->thread_count = 8;//use 8 Thread decode;

	//init decoder ctx
	ret = avcodec_open2(m_codeCtx, nullptr, nullptr);
	if (ret < 0)
	{
		ERR_RET(ret);
	}

	m_pkt = av_packet_alloc();
	if (!m_pkt)
	{
		cout << "av packet alloc Failed\n";
		free();
		return false;
	}

	m_frame = av_frame_alloc();
	if (!m_frame)
	{
		cout << "Av frame Alloc Failed\n";
		free();
		return false;
	}

	int size = av_image_get_buffer_size(AV_PIX_FMT_RGBA, msp_videoSize->width, msp_videoSize->height, 4);

	mspRGB_Buf.reset(new uchar(size + 1000), [](uchar* p) {delete[] p; });
	m_end = false;

	cout << "Open Success" << endl;
	return true;
}

AVFrame* VideoDecode::read()
{
	int ret = 0;

	if (!m_fmtCtx)
	{
		return nullptr;
	}

	int readRet = av_read_frame(m_fmtCtx, m_pkt);
	if (readRet < 0)
	{
		avcodec_send_packet(m_codeCtx, m_pkt);
	}
	else
	{
		if (m_pkt->stream_index == m_videoIdx)
		{
			//cal cur time
			m_pkt->pts = int64_t(m_pkt->pts * (1000 * rational2double(&m_fmtCtx->streams[m_videoIdx]->time_base)) + 0.5f);
			m_pkt->dts = int64_t(m_pkt->dts * (1000 * rational2double(&m_fmtCtx->streams[m_videoIdx]->time_base)) + 0.5f);
			
			ret = avcodec_send_packet(m_codeCtx, m_pkt);
			if (ret < 0)
			{
				showErr(ret);
			}
		}
	}

	av_packet_unref(m_pkt);
	av_frame_unref(m_frame);

	ret = avcodec_receive_frame(m_codeCtx, m_frame);
	if (ret < 0)
	{
		av_frame_unref(m_frame);
		if (readRet < 0)
		{
			m_end = true;
		}
		return nullptr;
	}
	m_pts = m_frame->pts;
	return m_frame;
}

void VideoDecode::close()
{
	clear();
	free();
	m_toltalTime = 0;
	m_videoIdx = 0;
	m_toltalFrame = 0;
	m_obtainFrames = 0;
	m_pts = 0;
	m_fps = 0;
	msp_videoSize.reset(new VideoSize(), [](VideoSize* p) {delete p; });
}

bool VideoDecode::isEnd()
{
	return m_end;
}

const int64_t& VideoDecode::pts()
{
	return m_pts;
}

void VideoDecode::initFFmpeg()
{
	static bool isFirst = true;
	static std::mutex _mutex;
	{
		std::lock_guard<std::mutex> lk(_mutex);
		avformat_network_init();
		avdevice_register_all();
		isFirst = false;
	}

}

void VideoDecode::showErr(int Err)
{
	memset(mspErrBuf.get(), 0, ERR_LEN);
	av_strerror(Err, mspErrBuf.get(), ERR_LEN);
	cout << "Decode Err: " << mspErrBuf.get();
}



void VideoDecode::clear()
{
	if (m_fmtCtx && m_fmtCtx->pb)
	{
		avio_flush(m_fmtCtx->pb);
	}

	if (m_fmtCtx)
	{
		avformat_flush(m_fmtCtx);
	}
}

 void VideoDecode::free()
{
	 if (m_swsCtx)
	 {
		 sws_freeContext(m_swsCtx);
		 m_swsCtx = nullptr;
	 }

	 if (m_codeCtx)
	 {
		 avcodec_free_context(&m_codeCtx);
	 }

	 if (m_fmtCtx)
	 {
		 avformat_free_context(m_fmtCtx);
	 }

	 if (m_pkt)
	 {
		 av_packet_free(&m_pkt);
	 }

	 if (m_frame)
	 {
		 av_frame_free(&m_frame);
	 }

}

 double VideoDecode::rational2double(AVRational* rational)
 {
	 return rational->den == 0 ? 0.0 : double(rational->num) / rational->den;
 }


