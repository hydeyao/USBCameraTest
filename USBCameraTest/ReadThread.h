#pragma once

#include <QThread>
#include <qstring.h>
#include <qstringbuilder.h>
#include <QTime>
#include <memory>

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
	explicit ReadThread(QObject *parent);
	~ReadThread() override;

	void open(const QString& url = QString());
	void pause(bool flag);
	void close();
	const QString& url();

protected:
	virtual void run() override;

signals:
	void repaint(AVFrame* frame);
	void play_stat(int stat);

private:
	std::shared_ptr<VideoDecode> msp_videoDecode = nullptr;
	QString m_url;
	bool m_play = false;

};

