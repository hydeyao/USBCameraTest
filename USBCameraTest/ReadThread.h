#pragma once

#include <QThread>
#include <qstring.h>
#include <qstringbuilder.h>
#include <QTime>
#include <memory>
#include <qimage.h>

class VideoDecode;
struct AVFrame;

enum PlayState
{
	end = 0,
	play = 1
};



class ReadThread  : public QThread
{
	Q_OBJECT

public:
	explicit ReadThread(QObject *parent = nullptr);
	~ReadThread() override;

	void open(const QString& url = QString(),const QString& res = QString());
	void pause(bool flag);
	void close();
	void useGL(bool use);
	const QString& url();

protected:
	virtual void run() override;

signals:
	void repaint(AVFrame* frame);
	void play_stat(int stat);
	void send_img(QImage img);

private:
	std::shared_ptr<VideoDecode> msp_videoDecode = nullptr;
	QString m_url;
	QString m_res;
	bool m_play = false;
	bool mb_userGL = true;


};

