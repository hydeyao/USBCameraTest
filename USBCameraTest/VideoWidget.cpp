#include "VideoWidget.h"
#include <QPainter>
#include <qmessagebox.h>

extern "C" {
#include "libavcodec/avcodec.h"
}

VideoWidget::VideoWidget(QWidget* parent, Qt::WindowFlags f)
	: QOpenGLWidget(parent,f)
{
	m_pos = QPointF(0, 0);
	m_zoomSize = QSize(0, 0);
}

VideoWidget::~VideoWidget()
{
    if (!isValid()) return;        // 如果控件和OpenGL资源（如上下文）已成功初始化，则返回true。
    this->makeCurrent(); // 通过将相应的上下文设置为当前上下文并在该上下文中绑定帧缓冲区对象，为呈现此小部件的OpenGL内容做准备。
    // 释放纹理
    if (m_texY)
    {
        m_texY->destroy();
        delete m_texY;
    }
    if (m_texU)
    {
        m_texU->destroy();
        delete m_texU;
    }
    if (m_texV)
    {
        m_texV->destroy();
        delete m_texV;
    }
    this->doneCurrent();    // 释放上下文
    // 释放
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteVertexArrays(1, &VAO);
}

void VideoWidget::repaint(AVFrame * frame)
{
    _useGL = true;

	if (!frame || frame->width == 0 || frame->height == 0)	return;

	if (frame->width != m_size.width() || frame->height != m_size.height())
	{
		if (m_texY && m_texU && m_texV)
		{
			m_texY->destroy();
			m_texU->destroy();
			m_texV->destroy();
			delete m_texY;
			delete m_texU;
			delete m_texV;
			m_texY = nullptr;
			m_texU = nullptr;
			m_texV = nullptr;
		}
	}

	if (!m_texY)
	{
		// 创建2D纹理
		m_texY = new QOpenGLTexture(QOpenGLTexture::Target2D);
		m_texU = new QOpenGLTexture(QOpenGLTexture::Target2D);
		m_texV = new QOpenGLTexture(QOpenGLTexture::Target2D);

        // 设置纹理大小                                                //  YUV444    YUV422    YUV422
        m_texY->setSize(frame->width, frame->height);                //   w,h      w,h       w,h
        m_texU->setSize(frame->width / 2, frame->height);            //   w,h      w/2,h      w/2,h/2
        m_texV->setSize(frame->width / 2, frame->height);            //   w,h      w/2,h      w/2,h/2

        // 设置放大、缩小过滤器
        m_texY->setMinMagFilters(QOpenGLTexture::LinearMipMapLinear, QOpenGLTexture::Linear);
        m_texU->setMinMagFilters(QOpenGLTexture::LinearMipMapLinear, QOpenGLTexture::Linear);
        m_texV->setMinMagFilters(QOpenGLTexture::LinearMipMapLinear, QOpenGLTexture::Linear);

        // 设置图像格式
        m_texY->setFormat(QOpenGLTexture::R8_UNorm);
        m_texU->setFormat(QOpenGLTexture::R8_UNorm);
        m_texV->setFormat(QOpenGLTexture::R8_UNorm);

        // 分配内存
        m_texY->allocateStorage();
        m_texU->allocateStorage();
        m_texV->allocateStorage();

        // 记录图像分辨率
        m_size.setWidth(frame->width);
        m_size.setHeight(frame->height);
        resizeGL(this->width(), this->height());
    }

    if (!frame->data[0] || !frame->data[1] || !frame->data[2])
    {
        emit stopVideo();
        av_frame_unref(frame);
        return;
    }

    m_options.setImageHeight(frame->height);
    m_options.setRowLength(frame->linesize[0]);
    m_texY->setData(QOpenGLTexture::Red, QOpenGLTexture::UInt8, static_cast<const void*>(frame->data[0]), &m_options);   // 设置图像数据 Y
    m_options.setRowLength(frame->linesize[1]);
    m_texU->setData(QOpenGLTexture::Red, QOpenGLTexture::UInt8, static_cast<const void*>(frame->data[1]), &m_options);   // 设置图像数据 U
    m_options.setRowLength(frame->linesize[2]);
    m_texV->setData(QOpenGLTexture::Red, QOpenGLTexture::UInt8, static_cast<const void*>(frame->data[2]), &m_options);   // 设置图像数据 V
    av_frame_unref(frame);



    this->update();
}




static GLfloat vertices[] = {  // 前三列点坐标，后两列为纹理坐标
     1.0f,  1.0f, 0.0f, 1.0f, 1.0f,      // 右上角
     1.0f, -1.0f, 0.0f, 1.0f, 0.0f,      // 右下
    -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,      // 左下
    -1.0f,  1.0f, 0.0f, 0.0f, 1.0f      // 左上
};

static GLuint indices[] = {
    0, 1, 3,
    1, 2, 3
};


void VideoWidget::initializeGL()
{
    initializeOpenGLFunctions();

    // 加载shader脚本程序
    m_shaderProg = new QOpenGLShaderProgram(this);
#if 1
    m_shaderProg->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/USBCameraTest/Resourses/vertex.vsh");
    m_shaderProg->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/USBCameraTest/Resourses/fragment.fsh");
#else
    m_shaderProg->addShaderFromSourceFile(QOpenGLShader::Vertex, "E:\\QtProject\\USBCameraTest\\USBCameraTest\\Resourses\\vertex.vsh");
    m_shaderProg->addShaderFromSourceFile(QOpenGLShader::Fragment, "E:\\QtProject\\USBCameraTest\\USBCameraTest\\Resourses\\fragment.fsh");
#endif


    m_shaderProg->link();

    // 绑定YUV 变量值
    m_shaderProg->bind();
    m_shaderProg->setUniformValue("tex_y", 0);
    m_shaderProg->setUniformValue("tex_u", 1);
    m_shaderProg->setUniformValue("tex_v", 2);

    // 返回属性名称在此着色器程序的参数列表中的位置。如果名称不是此着色器程序的有效属性，则返回-1。
    GLuint posAttr = GLuint(m_shaderProg->attributeLocation("aPos"));
    GLuint texCord = GLuint(m_shaderProg->attributeLocation("aTexCord"));

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glGenBuffers(1, &EBO);    // 创建一个EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);


    // 为当前绑定到的缓冲区对象创建一个新的数据存储target。任何预先存在的数据存储都将被删除。
    glBufferData(GL_ARRAY_BUFFER,        // 为VBO缓冲绑定顶点数据
        sizeof(vertices),      // 数组字节大小
        vertices,               // 需要绑定的数组
        GL_STATIC_DRAW);        // 指定数据存储的预期使用模式,GL_STATIC_DRAW： 数据几乎不会改变
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);  // 将顶点索引数组传入EBO缓存
    // 设置顶点坐标数据
    glVertexAttribPointer(posAttr,                     // 指定要修改的通用顶点属性的索引
        3,                     // 指定每个通用顶点属性的组件数（如vec3：3，vec4：4）
        GL_FLOAT,              // 指定数组中每个组件的数据类型(数组中一行有几个数)
        GL_FALSE,              // 指定在访问定点数据值时是否应规范化 ( GL_TRUE) 或直接转换为定点值 ( GL_FALSE)，如果vertices里面单个数超过-1或者1可以选择GL_TRUE
        5 * sizeof(GLfloat),   // 指定连续通用顶点属性之间的字节偏移量。
        nullptr);              // 指定当前绑定到目标的缓冲区的数据存储中数组中第一个通用顶点属性的第一个组件的偏移量。初始值为0 (一个数组从第几个字节开始读)
// 启用通用顶点属性数组
    glEnableVertexAttribArray(posAttr);                // 属性索引是从调用glGetAttribLocation接收的，或者传递给glBindAttribLocation。

    // 设置纹理坐标数据
    glVertexAttribPointer(texCord, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), reinterpret_cast<const GLvoid*>(3 * sizeof(GLfloat)));              // 指定当前绑定到目标的缓冲区的数据存储中数组中第一个通用顶点属性的第一个组件的偏移量。初始值为0 (一个数组从第几个字节开始读)
    // 启用通用顶点属性数组
    glEnableVertexAttribArray(texCord);                // 属性索引是从调用glGetAttribLocation接收的，或者传递给glBindAttribLocation。

    // 释放
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);                        // 设置为零以破坏现有的顶点数组对象绑定

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);        // 指定颜色缓冲区的清除值(背景色)


}

void VideoWidget::resizeGL(int w, int h)
{
    if (m_size.width() < 0 || m_size.height() < 0) return;

    // 计算需要显示图片的窗口大小，用于实现长宽等比自适应显示
    if ((double(w) / h) < (double(m_size.width()) / m_size.height()))
    {
        m_zoomSize.setWidth(w);
        m_zoomSize.setHeight(((double(w) / m_size.width()) * m_size.height()));   // 这里不使用QRect，使用QRect第一次设置时有误差bug
    }
    else
    {
        m_zoomSize.setHeight(h);
        m_zoomSize.setWidth((double(h) / m_size.height()) * m_size.width());
    }
    m_pos.setX(double(w - m_zoomSize.width()) / 2);
    m_pos.setY(double(h - m_zoomSize.height()) / 2);
    this->update(QRect(0, 0, w, h));

}

void VideoWidget::paintGL()
{

    glClear(GL_COLOR_BUFFER_BIT);     // 将窗口的位平面区域（背景）设置为先前由glClearColor、glClearDepth和选择的值
    glViewport(m_pos.x(), m_pos.y(), m_zoomSize.width(), m_zoomSize.height());  // 设置视图大小实现图片自适应

    m_shaderProg->bind();               // 绑定着色器
    // 绑定纹理
    if (m_texY && m_texU && m_texV)
    {
        m_texY->bind(0);
        m_texU->bind(1);
        m_texV->bind(2);
    }

    glBindVertexArray(VAO);           // 绑定VAO

    glDrawElements(GL_TRIANGLES,      // 绘制的图元类型
        6,                 // 指定要渲染的元素数(点数)
        GL_UNSIGNED_INT,   // 指定索引中值的类型(indices)
        nullptr);          // 指定当前绑定到GL_ELEMENT_array_buffer目标的缓冲区的数据存储中数组中第一个索引的偏移量。
    glBindVertexArray(0);
    if (m_texY && m_texU && m_texV)
    {
        m_texY->release();
        m_texU->release();
        m_texV->release();
    }
    m_shaderProg->release();

}

#if 1
void VideoWidget::paintEvent(QPaintEvent* e)
{
    QPainter painter(this);
    if (!_useGL)
    {
        
        painter.drawImage(0, 0, mShowImg);
    }
    else
    {
        QOpenGLWidget::paintEvent(e);
    }   

    painter.setPen(QPen(Qt::red));
    painter.drawLine(this->rect().left(), this->rect().height() / 2, this->rect().right(), this->rect().height() / 2);
    painter.drawLine(this->rect().width() / 2,this->rect().top(), this->rect().width() / 2, this->rect().bottom());
}

#endif

void VideoWidget::show_cross_line(bool show)
{


}


void VideoWidget::paint_image(QImage img)
{
    _useGL = false;
    mShowImg = img.scaled(this->size());
    mShowImg.save("D:\\test11.bmp");
    update();
}
