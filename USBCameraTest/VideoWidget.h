#pragma once

#include <QOpenGLWidget>
#include <qopenglfunctions_3_3_core.h>
#include <qopenglshaderprogram.h>
#include <QOpenGLTexture>
#include <qopenglpixeltransferoptions.h>
#include <qimage.h>


enum DRAW_TYEP
{
	DRAW_CLEAR = 0,
	DRAW_CROSS_LINE = 1, 
	DRAW_RECTS = 2 
};

struct AVFrame;

class VideoWidget  : public QOpenGLWidget, public  QOpenGLFunctions_3_3_Core
{
	Q_OBJECT

public:
	explicit VideoWidget(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
	~VideoWidget() override;

	void repaint(AVFrame* frame);

	void setDrawType(int type = 0);

protected:
	virtual void initializeGL() override;
	virtual void resizeGL(int w, int h) override;
	virtual void paintGL() override;
	virtual void paintEvent(QPaintEvent* e) override;

signals:
	void stopVideo();


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

	QImage mShowImg;
	bool _useGL = false;

	int mDrawType;

public slots:
	void paint_image(QImage img);



private:
	void initDrawShader();
	void paint_with_shader();
	void drawVideo();
	void show_cross_line(QPainter& painter);
	void show_cross_line();




};
