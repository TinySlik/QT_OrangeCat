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
      m_Ctexture(std::make_shared<QOpenGLTexture>(QOpenGLTexture::Target1D)) {
    m_core = QSurfaceFormat::defaultFormat().profile() == QSurfaceFormat::CoreProfile;
    // --transparent causes the clear color to be transparent. Therefore, on systems that
    // support it, the widget will become transparent apart from the logo.
    if (m_transparent) {
        QSurfaceFormat fmt = format();
        fmt.setAlphaBufferSize(8);
        setFormat(fmt);
    }

    auto cfg = ParameterServer::instance()->GetCfgCtrlRoot();
    cfg["X"].add_callback([this](configuru::Config &, const configuru::Config &b)->bool{
        if (!b.is_int()) return false;
        auto tg = int(b);
        setXRotation(8 * tg);
        return true;
      });
    cfg["Y"].add_callback([this](configuru::Config &, const configuru::Config &b)->bool{
        if (!b.is_int()) return false;
        auto tg = int(b);
        setYRotation(8 * tg);
        return true;
      });
    cfg["Z"].add_callback([this](configuru::Config &, const configuru::Config &b)->bool{
        if (!b.is_int()) return false;
        auto tg = int(b);
        setZRotation(8 * tg);
        return true;
      });
    reset();

    roll=0.0;
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
    float value = float(rand() % 100);

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
        qDebug() << "VAO created!";
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
    qDebug() << m_Ctexture->width() << m_Ctexture->height();

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

//    // In this example the widget's corresponding top-level window can change
//    // several times during the widget's lifetime. Whenever this happens, the
//    // QOpenGLWidget's associated context is destroyed and a new one is created.
//    // Therefore we have to be prepared to clean up the resources on the
//    // aboutToBeDestroyed() signal, instead of the destructor. The emission of
//    // the signal will be followed by an invocation of initializeGL() where we
//    // can recreate all resources.
//    connect(context(), &QOpenGLContext::aboutToBeDestroyed, this, &GLWidget::cleanup);

//    initializeOpenGLFunctions();
//    glClearColor(0, 0, 0, m_transparent ? 0 : 1);

//    m_program = std::make_shared<QOpenGLShaderProgram>();

////    m_program = new QOpenGLShaderProgram;
//    if (!m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shader/vshader.glsl"))
//        close();
//    if (!m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shader/fshader.glsl"))
//        close();
////    m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, m_core ? vertexShaderSourceCore : vertexShaderSource);
////    m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, m_core ? fragmentShaderSourceCore : fragmentShaderSource);
//    m_program->bindAttributeLocation("vertex", 0);
//    m_program->bindAttributeLocation("normal", 1);
//    m_program->link();

//    m_program->bind();
//    m_projMatrixLoc = m_program->uniformLocation("projMatrix");
//    m_mvMatrixLoc = m_program->uniformLocation("mvMatrix");
//    m_normalMatrixLoc = m_program->uniformLocation("normalMatrix");
//    m_lightPosLoc = m_program->uniformLocation("lightPos");
//    m_time_ = m_program->uniformLocation("time");

//    // Create a vertex array object. In OpenGL ES 2.0 and OpenGL 2.x
//    // implementations this is optional and support may not be present
//    // at all. Nonetheless the below code works in all cases and makes
//    // sure there is a VAO when one is needed.
//    m_vao.create();
//    QOpenGLVertexArrayObject::Binder vaoBinder(&m_vao);

//    // Setup our vertex buffer object.
//    m_logoVbo.create();
//    m_logoVbo.bind();
//    m_logoVbo.allocate(m_logo.constData(), m_logo.count() * sizeof(GLfloat));

//    // Store the vertex attribute bindings for the program.
//    setupVertexAttribs();

//    // Our camera never changes in this example.
//    m_camera.setToIdentity();
//    m_camera.translate(0, 0, -1);

//    // Light position is fixed.
//    m_program->setUniformValue(m_lightPosLoc, QVector3D(0, 0, 70));

//    m_program->release();
//    setXRotation(0);
//    setYRotation(0);
//    setZRotation(0);

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
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    glEnable(GL_DEPTH_TEST);
//    glEnable(GL_CULL_FACE);

//    m_world.setToIdentity();
//    m_world.rotate(180.0f - (m_xRot / 16.0f), 1, 0, 0);
//    m_world.rotate(m_yRot / 16.0f, 0, 1, 0);
//    m_world.rotate(m_zRot / 16.0f, 0, 0, 1);

//    QOpenGLVertexArrayObject::Binder vaoBinder(&m_vao);
//    m_program->bind();
//    m_program->setUniformValue(m_projMatrixLoc, m_proj);
//    m_program->setUniformValue(m_mvMatrixLoc, m_camera * m_world);
//    QMatrix3x3 normalMatrix = m_world.normalMatrix();
//    m_program->setUniformValue(m_normalMatrixLoc, normalMatrix);
//    float time = (float)(GetTickCount()) / 1000.f ;
//    m_program->setUniformValue(m_time_, time);

//    glDrawArrays(GL_TRIANGLES, 0, m_logo.vertexCount());

////    getData();
////    qDebug() << "======================" << m_tex_buf_render_head - m_tex_buf.data();
////    for (size_t i = 0; i < 20; ++i) {
////        qDebug() << m_tex_buf_render_head[i] << "|||";
////    }

//    m_program->release();

    static GLint srcLoc= glGetUniformLocation(m_CrenderProgram->programId(), "srcTex");
    static GLint destLoc=glGetUniformLocation(m_CcomputeProgram->programId(), "destTex");
    static GLint rollLoc=glGetUniformLocation(m_CcomputeProgram->programId(), "roll");

//    qDebug() << srcLoc;
//    qDebug() << destLoc;
//    qDebug() << rollLoc;
//    qDebug() << roll;

    // compute
    m_Cvao.bind();

    m_CcomputeProgram->bind();
    m_Ctexture->bind();
    glUniform1i(destLoc, 0);
    glUniform1f(rollLoc, roll);
    roll += 0.15;
    glDispatchCompute(m_Ctexture->width() / 256, 1, 1);
    glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);

//    m_texture

    // draw
    m_CrenderProgram->bind();
    //glClear(GL_COLOR_BUFFER_BIT);
    m_Ctexture->bind();
    glUniform1i(srcLoc, 0);
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
//    m_proj.perspective(fov, aspect, zNear, zFar);

//    m_proj.setToIdentity();
//    m_proj.perspective(45.0f, GLfloat(w) / h, 0.01f, 100.0f);
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
