#include "ReadThread.h"
#include <qeventloop.h>
#include <qtimer.h>
#include "VideoDecode.h"
#include <qdebug.h>

ReadThread::ReadThread(QObject *parent)
	: QThread(parent)
{
	msp_videoDecode.reset(new VideoDecode(), [](VideoDecode* p) {delete p; });
}

ReadThread::~ReadThread()
{}

void ReadThread::open(const QString & url, const QString& res)
{
	if (!this->isRunning())
	{
		m_url = url.startsWith("video=") ? url : "video=" % url;
		m_res = res;
		emit this->start();
	}
}

void ReadThread::pause(bool flag)
{
	m_play = flag;
}

void ReadThread::close()
{
	m_play = false;
}

const QString& ReadThread::url()
{
	return m_url;
}

void sleepMsec(int msec) 
{
	if (msec <= 0) return;
	QEventLoop loop;
	QTimer::singleShot(msec, &loop, SLOT(quit()));
	loop.exec();
}

void ReadThread::run()
{
	bool ret = msp_videoDecode->open(m_url.toStdString(), m_res.toStdString());
	if (ret)
	{
		m_play = true;
		emit play_stat(play);
	}
	else
	{
		qWarning() << "Open Failed";
	}

	//Read Video Loop
	while (m_play)
	{
		AVFrame* frame = msp_videoDecode->read();
		if (frame)
		{
			emit repaint(frame);
		}
		else
		{
			if (msp_videoDecode->isEnd())
			{
				break;
			}
			sleepMsec(1);
		}
	}

	qDebug() << "play end";
	msp_videoDecode->close();
	emit play_stat(end);

}
