/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "glwidget.h"
#include <QMouseEvent>
#include <QOpenGLShaderProgram>
#include <QCoreApplication>
#include <math.h>
#include "parameterserver.h"
#include <windows.h>
#include <QBasicTimer>
#include "easylogging++.h"

bool GLWidget::m_transparent = false;

GLWidget::GLWidget(QWidget *parent)
    : QOpenGLWidget(parent),
      m_xRot(0),
      m_yRot(0),
      m_zRot(0),
      m_program(nullptr),
      m_tex_buf_render_head(nullptr),
      m_CvertexBuffer(std::make_shared<QOpenGLBuffer>(QOpenGLBuffer::VertexBuffer)),
      m_CindexBuffer(std::make_shared<QOpenGLBuffer>(QOpenGLBuffer::IndexBuffer)),
      m_CcomputeProgram(std::make_shared<QOpenGLShaderProgram>()),
      m_CrenderProgram(std::make_shared<QOpenGLShaderProgram>()),
      m_Ctexture(std::make_shared<QOpenGLTexture>(QOpenGLTexture::Target1D)),
      roll(0.0),
      m_speed(0.15f),
      m_lineThickness(0.02f),
      m_ComputeShaderSwitch(false) {
    m_core = QSurfaceFormat::defaultFormat().profile() == QSurfaceFormat::CoreProfile;
    // --transparent causes the clear color to be transparent. Therefore, on systems that
    // support it, the widget will become transparent apart from the logo.
    if (m_transparent) {
        QSurfaceFormat fmt = format();
        fmt.setAlphaBufferSize(8);
        setFormat(fmt);
    }

    auto cfg = ParameterServer::instance()->GetCfgCtrlRoot();

    cfg += {
        {"Speed", m_speed},
        {"lineThickness", m_lineThickness},
        {"compute1_switch", m_ComputeShaderSwitch}
    };

    cfg["Speed"].add_callback([this](configuru::Config &, const configuru::Config &b)->bool{
        if (!b.is_float()) return false;
        auto tg = float(b);
        m_speed = tg;
        return true;
      });

    cfg["lineThickness"].add_callback([this](configuru::Config &, const configuru::Config &b)->bool{
        if (!b.is_float()) return false;
        auto tg = float(b);
        m_lineThickness = tg;
        return true;
      });

    cfg["compute1_switch"].add_callback([this](configuru::Config &, const configuru::Config &b)->bool{
        if (!b.is_bool()) return false;
        auto tg = bool(b);
        m_ComputeShaderSwitch = tg;
        return true;
      });
    reset();

    QSurfaceFormat format;
    format.setVersion(4, 3);
    format.setProfile(QSurfaceFormat::CoreProfile);
    setFormat(format);
}

void GLWidget::reset() {
    m_tex_buf.clear();
    m_tex_buf.resize(MAX_PAINT_BUF_SIZE * 2);
    m_tex_buf_render_head = m_tex_buf.data() + MAX_PAINT_BUF_SIZE;
}

GLWidget::~GLWidget() {
    cleanup();
}

QSize GLWidget::minimumSizeHint() const {
    return QSize(50, 50);
}

QSize GLWidget::sizeHint() const {
    return QSize(768, 512);
}

static void qNormalizeAngle(int &angle) {
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360 * 16)
        angle -= 360 * 16;
}

void GLWidget::setXRotation(int angle) {
    qNormalizeAngle(angle);
    if (angle != m_xRot) {
        m_xRot = angle;
        emit xRotationChanged(angle);
        update();
    }
}

void GLWidget::setYRotation(int angle) {
    qNormalizeAngle(angle);
    if (angle != m_yRot) {
        m_yRot = angle;
        emit yRotationChanged(angle);
        update();
    }
}

void GLWidget::setZRotation(int angle) {
    qNormalizeAngle(angle);
    if (angle != m_zRot) {
        m_zRot = angle;
        emit zRotationChanged(angle);
        update();
    }
}

void GLWidget::cleanup() {
    if (m_program == nullptr)
        return;
    makeCurrent();
    m_logoVbo.destroy();
//    delete m_program;
//    m_program = 0;
    doneCurrent();
}

void GLWidget::getData() {
    //模擬
//    std::vector<float> cache;
//    size_t sz = rand()%50 + 50;
//    for (size_t i = 0; i < sz; i++) {
//        cache.push_back(float(rand() % 100));
//    }

    //==================
//    if (sz > MAX_PAINT_BUF_SIZE) {
//        qDebug() << "error";
//        return;
//    }
    float value = float((rand() % 1000) / 1000.f);

    if (m_tex_buf_render_head - m_tex_buf.data() > 0) {
        m_tex_buf_render_head --;
    } else {
        m_tex_buf_render_head = m_tex_buf.data() + MAX_PAINT_BUF_SIZE;
    }

    *m_tex_buf_render_head = value;
    *(m_tex_buf_render_head + MAX_PAINT_BUF_SIZE) = value;
}

void GLWidget::initializeGL() {
    initializeOpenGLFunctions();
    glClearColor(0,0,1,1);

    m_Cvao.create();
    if (m_Cvao.isCreated()) {
        m_Cvao.bind();
        LOG(INFO) << "VAO created!";
    }

    static const GLfloat g_vertex_buffer_data[] = {
        -1.0f, -1.0f,
        -1.0f, 1.0f,
        1.0f, -1.0f,
        1.0f, 1.0f
    };
    static const GLushort g_element_buffer_data[] = { 0, 1, 2, 3 };

    m_CvertexBuffer->create();
    m_CvertexBuffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_CvertexBuffer->bind();
    m_CvertexBuffer->allocate(g_vertex_buffer_data,sizeof(g_vertex_buffer_data));

    m_CindexBuffer->create();
    m_CindexBuffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_CindexBuffer->bind();
    m_CindexBuffer->allocate(g_element_buffer_data,sizeof(g_element_buffer_data));

    glActiveTexture(GL_TEXTURE0);
    m_Ctexture->create();
    m_Ctexture->setFormat(QOpenGLTexture::RGBA8_UNorm);
    m_Ctexture->setSize(512, 1);
    m_Ctexture->setMinificationFilter(QOpenGLTexture::Linear);
    m_Ctexture->setMagnificationFilter(QOpenGLTexture::Linear);
    m_Ctexture->allocateStorage();
    m_Ctexture->bind();

    glBindImageTexture(0, m_Ctexture->textureId(), 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA8);

    m_CcomputeProgram->addShaderFromSourceFile(QOpenGLShader::Compute, ":/shader/example_c.glsl");
    m_CcomputeProgram->link();
    m_CcomputeProgram->bind();

    m_CrenderProgram->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shader/example_v.glsl");
    m_CrenderProgram->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shader/example_f.glsl");
    m_CrenderProgram->link();
    m_CrenderProgram->bind();

    GLint posPtr = glGetAttribLocation(m_CrenderProgram->programId(), "pos");
    glVertexAttribPointer(posPtr, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(posPtr);

    m_vao.release();

    connect(&timer,SIGNAL(timeout()),this,SLOT(update()));
    timer.start(16);
}

void GLWidget::setupVertexAttribs() {
    m_logoVbo.bind();
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<void *>(3 * sizeof(GLfloat)));
    m_logoVbo.release();
}

void GLWidget::paintGL() {
    getData();
//    qDebug() << "======================" << m_tex_buf_render_head - m_tex_buf.data();
//    for (size_t i = 0; i < 10; ++i) {
//        qDebug() << m_tex_buf_render_head[i] << "|||";
//    }
    static GLint srcLoc = glGetUniformLocation(m_CrenderProgram->programId(), "srcTex");
    static GLint destLoc = glGetUniformLocation(m_CcomputeProgram->programId(), "destTex");
    static GLint rollLoc = glGetUniformLocation(m_CcomputeProgram->programId(), "roll");
    static GLint lineThicknessLoc = glGetUniformLocation(m_CrenderProgram->programId(), "lineThickness");

//    qDebug() << srcLoc;
//    qDebug() << destLoc;
//    qDebug() << rollLoc;
//    qDebug() << roll;

    // compute

//    glTexImage2D(GL_TEXTURE_2D,
//          0,                        // GLint  	   level
//          GL_R8UI,                  // internal    format
//          nWidth,                   // GLsizei  	width,
//          nHeight,                  // GLsizei  	height,
//          0,                        // GLint  	   border,
//          GL_RED_INTEGER,           // GLenum  	   format,
//          GL_UNSIGNED_BYTE,        // data type
//          (const GLvoid*)_data.data());       // texels
    /**
     * @brief getData
     * (int mipLevel,
                 PixelFormat sourceFormat, PixelType sourceType,
                 const void *data, const QOpenGLPixelTransferOptions * const options = nullptr);
     */
    m_Ctexture->setData(0, QOpenGLTexture::Red, QOpenGLTexture::Float32, m_tex_buf_render_head);

    m_Cvao.bind();
    if (m_ComputeShaderSwitch) {
        m_CcomputeProgram->bind();
        m_Ctexture->bind();
        glUniform1i(destLoc, 0);
        glUniform1f(rollLoc, roll);
        roll += m_speed;
        glDispatchCompute(m_Ctexture->width() / 256, 1, 1);
        glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
    }

    // draw
    m_CrenderProgram->bind();
    //glClear(GL_COLOR_BUFFER_BIT);
    m_Ctexture->bind();
    glUniform1i(srcLoc, 0);
    glUniform1f(lineThicknessLoc, m_lineThickness);
    glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, 0);

    m_Cvao.release();
}

void GLWidget::resizeGL(int w, int h) {
    // Calculate aspect ratio
    qreal aspect = qreal(w) / qreal(h ? h : 1);

    // Set near plane to 3.0, far plane to 7.0, field of view 45 degrees
    const qreal zNear = 0.01f, zFar = 100.0f, fov = 45.0;

    // Reset projection
    m_proj.setToIdentity();

    // Set perspective projection
    m_proj.ortho(+0.5f, -0.5f, +0.5f, -0.5f, zNear, zFar);
}

void GLWidget::mousePressEvent(QMouseEvent *event) {
    m_lastPos = event->pos();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event){
    int dx = event->x() - m_lastPos.x();
    int dy = event->y() - m_lastPos.y();

    if (event->buttons() & Qt::LeftButton) {
        setXRotation(m_xRot + 8 * dy);
        setYRotation(m_yRot + 8 * dx);
    } else if (event->buttons() & Qt::RightButton) {
        setXRotation(m_xRot + 8 * dy);
        setZRotation(m_zRot + 8 * dx);
    }
    m_lastPos = event->pos();
}