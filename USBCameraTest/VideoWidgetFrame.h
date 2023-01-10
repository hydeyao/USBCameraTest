#pragma once

#include <QOpenGLWidget>
#include <qopenglfunctions_3_3_core.h>
#include <qopenglshaderprogram.h>
#include <QOpenGLTexture>
#include <qopenglpixeltransferoptions.h>
#include "ConfigParser.h"


struct AVFrame;

class VideoWidgetFrame  : public QOpenGLWidget
{
	Q_OBJECT


public:
	VideoWidgetFrame(QWidget *parent);
	VideoWidgetFrame(QString path, QString project, QWidget *parent = nullptr);
	~VideoWidgetFrame();

	virtual void repaint(AVFrame* frame) {};
	virtual void paint_image(QImage img) {};

	void setDrawType(int type = 0);
	int initDrawRoiArr(QString project, QString path);

	virtual void paintOnVideo();
	virtual void draw_cross_line() {};
	virtual void draw_rects() {};

	const static int PAINT_CLEAR = 0;
	const static int PAINT_CROSS_LINE = 1;
	const static int PAINT_RECTS = 2;

	std::vector<Draw_ROI*> m_vecDrawRoi;
	std::map<std::string, Draw_ROI*> m_mapDrawRoi;

protected:
	int mDrawType;
	virtual void initializeGL() override;
	

signals:
	void stopVideo();

private:
	std::shared_ptr<ConfigParser> mspConfigParse = nullptr;
	int initWidget();

};

class GLVideoWidget : public VideoWidgetFrame, public  QOpenGLFunctions_3_3_Core
{
	Q_OBJECT

public:
	GLVideoWidget(QWidget* parent);
	~GLVideoWidget() override;

	virtual void repaint(AVFrame* frame) override;
protected:
	virtual void initializeGL() override;
	virtual void resizeGL(int w, int h) override;
	virtual void paintGL() override;

	virtual void draw_cross_line();
	virtual void draw_rects();

private:
	QOpenGLShaderProgram* m_shaderProg = nullptr;
	QOpenGLShaderProgram* m_paintProg = nullptr;
	QOpenGLTexture* m_texY = nullptr;
	QOpenGLTexture* m_texU = nullptr;
	QOpenGLTexture* m_texV = nullptr;
	QOpenGLPixelTransferOptions m_options;

	GLuint VBO = 0;
	GLuint VAO = 0;
	GLuint EBO = 0;

	GLuint PAINT_VAO = 0;
	GLuint PAINT_VBO = 0;

	QSize m_size;
	QSizeF m_zoomSize;
	QPointF m_pos;

private:
	void initCrossLineShader();
};

class NormalVideoWidget : public VideoWidgetFrame
{

	Q_OBJECT

public:
	NormalVideoWidget(QWidget * par);
	~NormalVideoWidget();

	virtual void paint_image(QImage img);

protected:
	virtual void paintEvent(QPaintEvent* e) override;

	virtual void draw_cross_line() override;
	virtual void draw_rects() override;

private:
	QImage mShowImg;
};