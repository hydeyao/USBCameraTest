#pragma once

#include <QOpenGLWidget>
#include <qopenglfunctions_3_3_core.h>
#include <qopenglshaderprogram.h>
#include <QOpenGLTexture>
#include <qopenglpixeltransferoptions.h>
#include <qimage.h>


struct AVFrame;

class VideoWidget  : public QOpenGLWidget, public  QOpenGLFunctions_3_3_Core
{
	Q_OBJECT

public:
	explicit VideoWidget(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
	~VideoWidget() override;

	void repaint(AVFrame* frame);

protected:
	virtual void initializeGL() override;
	virtual void resizeGL(int w, int h) override;
	virtual void paintGL() override;

	virtual void paintEvent(QPaintEvent* e) override;

signals:
	void stopVideo();


private:
	QOpenGLShaderProgram* m_shaderProg = nullptr;
	QOpenGLTexture* m_texY = nullptr;
	QOpenGLTexture* m_texU = nullptr;
	QOpenGLTexture* m_texV = nullptr;
	QOpenGLPixelTransferOptions m_options;

	GLuint VBO = 0;
	GLuint VAO = 0;
	GLuint EBO = 0;

	QSize m_size;
	QSizeF m_zoomSize;
	QPointF m_pos;

	QImage mShowImg;
	bool _useGL = true;

public slots:
	void paint_image(QImage img);
	void show_cross_line(bool show);


};
