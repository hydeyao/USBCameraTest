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
};

class VideoDecode
{
public:
	VideoDecode();
	~VideoDecode();

	bool open(const std::string& url = nullptr);
	AVFrame* read();
	void close();
	bool isEnd();
	const int64_t & pts();

private:
	void initFFmpeg();
	void showErr(int Err);
	double rational2double(AVRational* rational);
	void clear();
	void free();

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
	VideoSize* m_videoSize = nullptr;

	char* m_errBuf = nullptr;
	bool m_end = false;
	uchar* m_buf = nullptr;

                        

};

