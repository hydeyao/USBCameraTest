#include "VideoDecode.h"

VideoDecode::VideoDecode()
{
}

VideoDecode::~VideoDecode()
{
}

bool VideoDecode::open(const std::string& url)
{
	return false;
}

AVFrame* VideoDecode::read()
{
	return nullptr;
}

void VideoDecode::close()
{
}

bool VideoDecode::isEnd()
{
	return false;
}

const int64_t& VideoDecode::pts()
{
	// TODO: �ڴ˴����� return ���
}

void VideoDecode::initFFmpeg()
{
}

void VideoDecode::showErr(int Err)
{
}

double VideoDecode::rational2double(AVRational* rational)
{
	return 0.0;
}

void VideoDecode::clear()
{
}

 void VideoDecode::free()
{
}


