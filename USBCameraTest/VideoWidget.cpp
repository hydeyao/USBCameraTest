#include "VideoWidget.h"

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
    if (!isValid()) return;        // ����ؼ���OpenGL��Դ���������ģ��ѳɹ���ʼ�����򷵻�true��
    this->makeCurrent(); // ͨ������Ӧ������������Ϊ��ǰ�����Ĳ��ڸ��������а�֡����������Ϊ���ִ�С������OpenGL������׼����
    // �ͷ�����
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
    this->doneCurrent();    // �ͷ�������
    // �ͷ�
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteVertexArrays(1, &VAO);
}

void VideoWidget::repaint(AVFrame * frame)
{
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
		// ����2D����
		m_texY = new QOpenGLTexture(QOpenGLTexture::Target2D);
		m_texU = new QOpenGLTexture(QOpenGLTexture::Target2D);
		m_texV = new QOpenGLTexture(QOpenGLTexture::Target2D);

        // ���������С                                                //  YUV444    YUV422    YUV422
        m_texY->setSize(frame->width, frame->height);                //   w,h      w,h       w,h
        m_texU->setSize(frame->width / 2, frame->height);            //   w,h      w/2,h      w/2,h/2
        m_texV->setSize(frame->width / 2, frame->height);            //   w,h      w/2,h      w/2,h/2

        // ���÷Ŵ���С������
        m_texY->setMinMagFilters(QOpenGLTexture::LinearMipMapLinear, QOpenGLTexture::Linear);
        m_texU->setMinMagFilters(QOpenGLTexture::LinearMipMapLinear, QOpenGLTexture::Linear);
        m_texV->setMinMagFilters(QOpenGLTexture::LinearMipMapLinear, QOpenGLTexture::Linear);

        // ����ͼ���ʽ
        m_texY->setFormat(QOpenGLTexture::R8_UNorm);
        m_texU->setFormat(QOpenGLTexture::R8_UNorm);
        m_texV->setFormat(QOpenGLTexture::R8_UNorm);

        // �����ڴ�
        m_texY->allocateStorage();
        m_texU->allocateStorage();
        m_texV->allocateStorage();

        // ��¼ͼ��ֱ���
        m_size.setWidth(frame->width);
        m_size.setHeight(frame->height);
        resizeGL(this->width(), this->height());
    }
    m_options.setImageHeight(frame->height);
    m_options.setRowLength(frame->linesize[0]);
    m_texY->setData(QOpenGLTexture::Red, QOpenGLTexture::UInt8, static_cast<const void*>(frame->data[0]), &m_options);   // ����ͼ������ Y
    m_options.setRowLength(frame->linesize[1]);
    m_texU->setData(QOpenGLTexture::Red, QOpenGLTexture::UInt8, static_cast<const void*>(frame->data[1]), &m_options);   // ����ͼ������ U
    m_options.setRowLength(frame->linesize[2]);
    m_texV->setData(QOpenGLTexture::Red, QOpenGLTexture::UInt8, static_cast<const void*>(frame->data[2]), &m_options);   // ����ͼ������ V

    av_frame_unref(frame);  //  ȡ������֡���õ����л�����������֡�ֶΡ�

    this->update();
}

static GLfloat vertices[] = {  // ǰ���е����꣬������Ϊ��������
     1.0f,  1.0f, 0.0f, 1.0f, 1.0f,      // ���Ͻ�
     1.0f, -1.0f, 0.0f, 1.0f, 0.0f,      // ����
    -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,      // ����
    -1.0f,  1.0f, 0.0f, 0.0f, 1.0f      // ����
};

static GLuint indices[] = {
    0, 1, 3,
    1, 2, 3
};


void VideoWidget::initializeGL()
{
    initializeOpenGLFunctions();

    // ����shader�ű�����
    m_shaderProg = new QOpenGLShaderProgram(this);
#if 1
    m_shaderProg->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/USBCameraTest/Resourses/vertex.vsh");
    m_shaderProg->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/USBCameraTest/Resourses/fragment.fsh");
#else
    m_shaderProg->addShaderFromSourceFile(QOpenGLShader::Vertex, "E:\\QtProject\\USBCameraTest\\USBCameraTest\\Resourses\\vertex.vsh");
    m_shaderProg->addShaderFromSourceFile(QOpenGLShader::Fragment, "E:\\QtProject\\USBCameraTest\\USBCameraTest\\Resourses\\fragment.fsh");
#endif


    m_shaderProg->link();

    // ��YUV ����ֵ
    m_shaderProg->bind();
    m_shaderProg->setUniformValue("tex_y", 0);
    m_shaderProg->setUniformValue("tex_u", 1);
    m_shaderProg->setUniformValue("tex_v", 2);

    // �������������ڴ���ɫ������Ĳ����б��е�λ�á�������Ʋ��Ǵ���ɫ���������Ч���ԣ��򷵻�-1��
    GLuint posAttr = GLuint(m_shaderProg->attributeLocation("aPos"));
    GLuint texCord = GLuint(m_shaderProg->attributeLocation("aTexCord"));

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glGenBuffers(1, &EBO);    // ����һ��EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);


    // Ϊ��ǰ�󶨵��Ļ��������󴴽�һ���µ����ݴ洢target���κ�Ԥ�ȴ��ڵ����ݴ洢������ɾ����
    glBufferData(GL_ARRAY_BUFFER,        // ΪVBO����󶨶�������
        sizeof(vertices),      // �����ֽڴ�С
        vertices,               // ��Ҫ�󶨵�����
        GL_STATIC_DRAW);        // ָ�����ݴ洢��Ԥ��ʹ��ģʽ,GL_STATIC_DRAW�� ���ݼ�������ı�
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);  // �������������鴫��EBO����
    // ���ö�����������
    glVertexAttribPointer(posAttr,                     // ָ��Ҫ�޸ĵ�ͨ�ö������Ե�����
        3,                     // ָ��ÿ��ͨ�ö������Ե����������vec3��3��vec4��4��
        GL_FLOAT,              // ָ��������ÿ���������������(������һ���м�����)
        GL_FALSE,              // ָ���ڷ��ʶ�������ֵʱ�Ƿ�Ӧ�淶�� ( GL_TRUE) ��ֱ��ת��Ϊ����ֵ ( GL_FALSE)�����vertices���浥��������-1����1����ѡ��GL_TRUE
        5 * sizeof(GLfloat),   // ָ������ͨ�ö�������֮����ֽ�ƫ������
        nullptr);              // ָ����ǰ�󶨵�Ŀ��Ļ����������ݴ洢�������е�һ��ͨ�ö������Եĵ�һ�������ƫ��������ʼֵΪ0 (һ������ӵڼ����ֽڿ�ʼ��)
// ����ͨ�ö�����������
    glEnableVertexAttribArray(posAttr);                // ���������Ǵӵ���glGetAttribLocation���յģ����ߴ��ݸ�glBindAttribLocation��

    // ����������������
    glVertexAttribPointer(texCord, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), reinterpret_cast<const GLvoid*>(3 * sizeof(GLfloat)));              // ָ����ǰ�󶨵�Ŀ��Ļ����������ݴ洢�������е�һ��ͨ�ö������Եĵ�һ�������ƫ��������ʼֵΪ0 (һ������ӵڼ����ֽڿ�ʼ��)
    // ����ͨ�ö�����������
    glEnableVertexAttribArray(texCord);                // ���������Ǵӵ���glGetAttribLocation���յģ����ߴ��ݸ�glBindAttribLocation��

    // �ͷ�
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);                        // ����Ϊ�����ƻ����еĶ�����������

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);        // ָ����ɫ�����������ֵ(����ɫ)


}

void VideoWidget::resizeGL(int w, int h)
{
    if (m_size.width() < 0 || m_size.height() < 0) return;

    // ������Ҫ��ʾͼƬ�Ĵ��ڴ�С������ʵ�ֳ���ȱ�����Ӧ��ʾ
    if ((double(w) / h) < (double(m_size.width()) / m_size.height()))
    {
        m_zoomSize.setWidth(w);
        m_zoomSize.setHeight(((double(w) / m_size.width()) * m_size.height()));   // ���ﲻʹ��QRect��ʹ��QRect��һ������ʱ�����bug
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
    glClear(GL_COLOR_BUFFER_BIT);     // �����ڵ�λƽ�����򣨱���������Ϊ��ǰ��glClearColor��glClearDepth��ѡ���ֵ
    glViewport(m_pos.x(), m_pos.y(), m_zoomSize.width(), m_zoomSize.height());  // ������ͼ��Сʵ��ͼƬ����Ӧ

    m_shaderProg->bind();               // ����ɫ��
    // ������
    if (m_texY && m_texU && m_texV)
    {
        m_texY->bind(0);
        m_texU->bind(1);
        m_texV->bind(2);
    }

    glBindVertexArray(VAO);           // ��VAO

    glDrawElements(GL_TRIANGLES,      // ���Ƶ�ͼԪ����
        6,                 // ָ��Ҫ��Ⱦ��Ԫ����(����)
        GL_UNSIGNED_INT,   // ָ��������ֵ������(indices)
        nullptr);          // ָ����ǰ�󶨵�GL_ELEMENT_array_bufferĿ��Ļ����������ݴ洢�������е�һ��������ƫ������
    glBindVertexArray(0);
    if (m_texY && m_texU && m_texV)
    {
        m_texY->release();
        m_texU->release();
        m_texV->release();
    }
    m_shaderProg->release();

}
