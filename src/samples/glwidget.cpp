/** Copyright 2021 Tiny Oh, Ltd. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


#include <string>
#include "glwidget.h"
#include <math.h>
#include <windows.h>
#include <QMouseEvent>
#include <QOpenGLShaderProgram>
#include <QCoreApplication>
#include <QBasicTimer>
#include "parameterserver.h"
#include "easylogging++.h"

bool GLWidget::m_transparent = false;

GLWidget::GLWidget(QWidget *parent)
  : QOpenGLWidget(parent),
    m_xRot(0),
    m_yRot(0),
    m_zRot(0),
    m_program(nullptr),
    m_tex_buf_render_head(nullptr),
    m_fileMMap(nullptr),
    m_CvertexBuffer(std::make_shared<QOpenGLBuffer>(QOpenGLBuffer::VertexBuffer)),
    m_CindexBuffer(std::make_shared<QOpenGLBuffer>(QOpenGLBuffer::IndexBuffer)),
    m_CcomputeProgram(std::make_shared<QOpenGLShaderProgram>()),
    m_CrenderProgram(std::make_shared<QOpenGLShaderProgram>()),
    m_Ctexture(std::make_shared<QOpenGLTexture>(QOpenGLTexture::Target1D)),
    roll(0.0),
    m_speed(0.1f),
    m_lineThickness(0.01f),
    m_TestFrequency(100.f),
    m_ComputeShaderSwitch(true),
    m_TestSwitch(1),
    m_DisplaySwitch(1) {
  // QSurfaceFormat::CompatibilityProfile
  m_core = QSurfaceFormat::defaultFormat().profile() == QSurfaceFormat::CoreProfile;
  // --transparent causes the clear color to be transparent. Therefore, on systems that
  // support it, the widget will become transparent apart from the logo.
  if (m_transparent) {
    QSurfaceFormat fmt = format();
    fmt.setAlphaBufferSize(8);
    setFormat(fmt);
  }

  auto cfg = ParameterServer::instance()->GetCfgCtrlRoot();
  std::string class_obj_id = typeid(*this).name();
  class_obj_id += std::to_string(int(this));
  cfg += {{class_obj_id.c_str(), {
      {"Speed", m_speed},
      {"lineThickness", m_lineThickness},
      {"compute1_switch", m_ComputeShaderSwitch},
      {"test_switch", m_TestSwitch},
      {"test_frequency", m_TestFrequency},
      {"display_switch", m_DisplaySwitch},
      {"test_file_path", "null"}
    }}
  };
  auto cfg_local = cfg[class_obj_id.c_str()];

  cfg_local["test_file_path"].add_callback([this](configuru::Config &a, const configuru::Config &b)->bool {
    if (!b.is_string()) return false;
    auto tg = static_cast<std::string>(b);
    auto ora = static_cast<std::string>(a);
    if (tg == "null") {
        if (ora != "null" && m_fileMMap) {
          LOG(INFO) << "file name: " << ora << " close";
          m_fileMMap->close();
        }
        return true;
    }

    if (ora != "null" && m_fileMMap) {
      LOG(INFO) << "file name: " << ora << " close";
      m_fileMMap->close();
    }

//    size_t i;
    size_t sz;
//    size_t flushcnt;
    auto st = GetTickCount();
    m_fileMMap = std::make_shared<MemoryMapped::File>(tg);
    if (!m_fileMMap) return false;
    sz = m_fileMMap->size();
//    for(i = 0, flushcnt = 0; i < sz; i++, flushcnt++) {
//      std::cout << (*m_fileMMap)[i];
//      if(flushcnt == 128) {
//        std::cout.flush();
//        flushcnt = 0;
//      }
//    }
//    std::cout << "finished !!!" << std::endl;
    LOG(INFO) << "file name: " << tg << " open, size: " << sz << "  time spend: " << GetTickCount() - st << " ms ";
    return true;
  });

  cfg_local["Speed"].add_callback([this](configuru::Config &, const configuru::Config &b)->bool {
    if (!b.is_float()) return false;
    auto tg = static_cast<float>(b);
    m_speed = tg;
    return true;
  });

  cfg_local["lineThickness"].add_callback([this](configuru::Config &, const configuru::Config &b)->bool{
    if (!b.is_float()) return false;
    auto tg = static_cast<float>(b);
    m_lineThickness = tg;
    return true;
  });

  cfg_local["compute1_switch"].add_callback([this](configuru::Config &, const configuru::Config &b)->bool{
    if (!b.is_bool()) return false;
    auto tg = static_cast<bool>(b);
    m_ComputeShaderSwitch = tg;
    return true;
  });

  cfg_local["test_switch"].add_callback([this](configuru::Config &, const configuru::Config &b)->bool{
    if (!b.is_int()) return false;
    auto tg = static_cast<int>(b);
    m_TestSwitch = tg;
    return true;
  });

  cfg_local["display_switch"].add_callback([this](configuru::Config &, const configuru::Config &b)->bool{
    if (!b.is_int()) return false;
    auto tg = static_cast<int>(b);
    m_DisplaySwitch = tg;
    return true;
  });

  cfg_local["test_frequency"].add_callback([this](configuru::Config &, const configuru::Config &b)->bool{
    if (!b.is_float()) return false;
    auto tg = static_cast<float>(b);
    m_TestFrequency = tg;
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
  auto cfg = ParameterServer::instance()->GetCfgCtrlRoot();
  std::string class_obj_id = typeid(*this).name();
  class_obj_id += std::to_string(int(this));
  cfg.erase(class_obj_id);
}

QSize GLWidget::minimumSizeHint() const {
  return QSize(50, 50);
}

QSize GLWidget::sizeHint() const {
  return QSize(768, 512);
}

static void qNormalizeAngle(const int &) {}

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
    // 模拟通信数据流
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
  float value = static_cast<float>((rand() % 1000) / 1000.f);

  if (m_tex_buf_render_head - m_tex_buf.data() > 0) {
    m_tex_buf_render_head--;
  } else {
    m_tex_buf_render_head = m_tex_buf.data() + MAX_PAINT_BUF_SIZE;
  }

  *m_tex_buf_render_head = value;
  *(m_tex_buf_render_head + MAX_PAINT_BUF_SIZE) = value;
}

void GLWidget::initializeGL() {
  initializeOpenGLFunctions();
  glClearColor(0, 0, 1, 1);

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
  m_CvertexBuffer->allocate(g_vertex_buffer_data, sizeof(g_vertex_buffer_data));

  m_CindexBuffer->create();
  m_CindexBuffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
  m_CindexBuffer->bind();
  m_CindexBuffer->allocate(g_element_buffer_data, sizeof(g_element_buffer_data));

  glActiveTexture(GL_TEXTURE0);
  m_Ctexture->create();
//    m_Ctexture->setFormat(QOpenGLTexture::RGBA8_SNorm);
  m_Ctexture->setFormat(QOpenGLTexture::R32F);
  m_Ctexture->setSize(512, 1);
  m_Ctexture->setMinificationFilter(QOpenGLTexture::Linear);
  m_Ctexture->setMagnificationFilter(QOpenGLTexture::Linear);
  m_Ctexture->allocateStorage();
  m_Ctexture->bind();

//    glBindImageTexture(0, m_Ctexture->textureId(), 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA8);
  glBindImageTexture(0, m_Ctexture->textureId(), 0, GL_FALSE, 0, GL_READ_WRITE, GL_R32F);

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

  connect(&timer, SIGNAL(timeout()), this, SLOT(update()));
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
  getData(); // for test
  static GLint srcLoc = glGetUniformLocation(m_CrenderProgram->programId(), "srcTex");
  static GLint destLoc = glGetUniformLocation(m_CcomputeProgram->programId(), "destTex");
  static GLint rollLoc = glGetUniformLocation(m_CcomputeProgram->programId(), "roll");
  static GLint testFrequencyLoc = glGetUniformLocation(m_CcomputeProgram->programId(), "test_frequency");
  static GLint testSwitchLoc = glGetUniformLocation(m_CcomputeProgram->programId(), "test_switch");
  static GLint lineThicknessLoc = glGetUniformLocation(m_CrenderProgram->programId(), "lineThickness");
  static GLint displaySwitchLoc = glGetUniformLocation(m_CrenderProgram->programId(), "display_switch");

  // compute
  m_Ctexture->setData(0, QOpenGLTexture::Red, QOpenGLTexture::Float32, m_tex_buf_render_head);

  m_Cvao.bind();
  if (m_ComputeShaderSwitch) {
    m_CcomputeProgram->bind();
    m_Ctexture->bind();
    glUniform1i(destLoc, 0);
    glUniform1f(rollLoc, roll);
    glUniform1f(testFrequencyLoc, m_TestFrequency);
    glUniform1i(testSwitchLoc, m_TestSwitch);
    roll += m_speed;
    glDispatchCompute(m_Ctexture->width(), 1, 1);
    glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
  }

  // draw
  m_CrenderProgram->bind();
  // glClear(GL_COLOR_BUFFER_BIT);
  m_Ctexture->bind();
  glUniform1i(srcLoc, 0);
  glUniform1i(displaySwitchLoc, m_DisplaySwitch);
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
//  m_lastPos = event->pos();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event) {
//  int dx = event->x() - m_lastPos.x();
//  int dy = event->y() - m_lastPos.y();

//  if (event->buttons() & Qt::LeftButton) {
//      setXRotation(m_xRot + 8 * dy);
//      setYRotation(m_yRot + 8 * dx);
//  } else if (event->buttons() & Qt::RightButton) {
//      setXRotation(m_xRot + 8 * dy);
//      setZRotation(m_zRot + 8 * dx);
//  }
//  m_lastPos = event->pos();
}