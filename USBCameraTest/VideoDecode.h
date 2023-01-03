#pragma once

#include <iostream>
#include <string>
#include <memory>

using uchar = unsigned char;

struct AVFormatContext;
struct AVCodecContext;
struct AVRational;
struct AVPacket;
struct AVFrame;
struct SwsContext;
struct AVBufferRef;
struct AVInputFormat;
class QImage;

struct VideoSize
{
	int width;
	int height;

	VideoSize(int w, int h)
	{
		width = w;
		height = h;
	}

	VideoSize()
	{
		width = 0;
		height = 0;
	}
};

class VideoDecode
{
public:
	VideoDecode();
	~VideoDecode();

	bool open(const std::string& url = nullptr,const std::string &resolution = "800x600");
	AVFrame* read();
	void close();
	bool isEnd();
	const int64_t & pts();

private:
	void initFFmpeg();
	void showErr(int Err);
	void clear();
	void free();

	double rational2double(AVRational* rational);

private:
	const AVInputFormat* m_inputFmt = nullptr;
	AVFormatContext* m_fmtCtx = nullptr;
	AVCodecContext* m_codeCtx = nullptr;
	SwsContext* m_swsCtx = nullptr;
	AVPacket* m_pkt = nullptr;
	AVFrame* m_frame = nullptr;
	
	int m_videoIdx = 0;
	int64_t m_toltalTime = 0;
	int64_t m_toltalFrame = 0;
	int64_t m_obtainFrames = 0;
	int64_t m_pts = 0;
	double m_fps = 0;
	std::shared_ptr<VideoSize> msp_videoSize = nullptr;
	std::shared_ptr<char> mspErrBuf = nullptr;
	bool m_end = false;
	std::shared_ptr<uchar> mspRGB_Buf = nullptr;
                        

};

