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
#include "dataprocesswidget.h"
#include <math.h>
#include <windows.h>
#include <QMouseEvent>
#include <QOpenGLShaderProgram>
#include <QCoreApplication>
#include <QBasicTimer>
#include "parameterserver.h"
#include "easylogging++.h"

#define DEFAULT_COMPUTE_SHADER_PATH ":/shader/example_c.glsl"
#define DEFAULT_VERT_SHADER_PATH ":/shader/example_v.glsl"
#define DEFAULT_FAGERMENT_SHADER_PATH ":/shader/example_f.glsl"

bool DataProcessWidget::m_transparent = false;

DataProcessWidget::DataProcessWidget(QWidget *parent)
  : QOpenGLWidget(parent),
    m_tex_buf_render_head(nullptr),
    m_fileMMap(nullptr),
    m_CvertexBuffer(std::make_shared<QOpenGLBuffer>(QOpenGLBuffer::VertexBuffer)),
    m_CindexBuffer(std::make_shared<QOpenGLBuffer>(QOpenGLBuffer::IndexBuffer)),
    m_CcomputeProgram(std::make_shared<QOpenGLShaderProgram>()),
    m_CrenderProgram(std::make_shared<QOpenGLShaderProgram>()),
    m_Ctexture(std::make_shared<QOpenGLTexture>(QOpenGLTexture::Target1D)),
    m_roll(0.0),
    m_speed(0.0333f),
    m_lineThickness(0.01f),
    m_TestFrequency(100.f),
    m_ComputeShaderSwitch(true),
    m_TestSwitch(1),
    m_DisplaySwitch(4),
    m_file_find_index(0),
    m_fft_level(512),
//    m_reset_buf_tag(false),
    m_reset_computeshader_tag(false) {
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

  connect(this, SIGNAL(TitelChanged(const QString &)), parent, SLOT(setWindowTitle(const QString &)));

  cfg += {{class_obj_id.c_str(), {
      {"Speed", m_speed},
      {"lineThickness", m_lineThickness},
      {"compute1_switch", m_ComputeShaderSwitch},
      {"test_switch", m_TestSwitch},
      {"test_frequency", m_TestFrequency},
      {"display_switch", m_DisplaySwitch},
      {"test_file_path", "empty"},
      {"file_load_location", m_file_find_index},
      {"fft_level", m_fft_level}
    }}
  };

  auto cfg_local = cfg[class_obj_id.c_str()];
  cfg_local["fft_level"].add_callback([this](configuru::Config &a, const configuru::Config &b)->bool {
    if (!b.is_int()) return false;
    auto tg = static_cast<int>(b);
    if (tg >= 256 && tg <= 512) {
      m_fft_level = 512;
    } else if (tg > 512 && tg <= 1024) {
      m_fft_level = 1024;
    } else if (tg > 1024 && tg <= 2048) {
      m_fft_level = 2048;
    } else if (tg > 2048 && tg <= 4096) {
      m_fft_level = 4096;
    } else {
      return false;
    }
//    m_reset_buf_tag = true;
    m_reset_computeshader_tag = true;
    LOG(INFO) << "FFT level set to " << m_fft_level;
    return true;
  });

  cfg_local["file_load_location"].add_callback([this](configuru::Config &, const configuru::Config &b)->bool {
    if (!b.is_int()) return false;
    auto tg = static_cast<int>(b);
    m_file_find_index = tg;
    return true;
  });

  cfg_local["test_file_path"].add_callback([this](configuru::Config &a, const configuru::Config &b)->bool {
    if (!b.is_string()) return false;
    auto tg = static_cast<std::string>(b);
    auto ora = static_cast<std::string>(a);
    if (tg == "empty") {
      if (ora != "empty" && m_fileMMap) {
        LOG(INFO) << "file name: " << ora << " close";
        m_fileMMap->close();
        m_fileMMap = nullptr;
        m_file_find_index = 0;
      }
      return true;
    }

    if (ora != "empty" && m_fileMMap) {
      LOG(INFO) << "file name: " << ora << " close";
      m_fileMMap->close();
      m_fileMMap = nullptr;
      m_file_find_index = 0;
    }

    size_t sz;
    auto st = GetTickCount();
    m_fileMMap = std::make_shared<MemoryMapped::File>(tg);
    if (!m_fileMMap) return false;
    sz = m_fileMMap->size();
    emit TitelChanged(QString(tg.c_str()));
    LOG(INFO) << "file name: " << tg << " open, size: " << sz << "  time spend: " << GetTickCount() - st << " ms ";
    return true;
  });

  cfg_local["Speed"].add_callback([this](configuru::Config &, const configuru::Config &b)->bool {
    if (!b.is_float()) return false;
    auto tg = static_cast<float>(b);
    m_speed = tg;
    return true;
  });

  cfg_local["lineThickness"].add_callback([this](configuru::Config &, const configuru::Config &b)->bool {
    if (!b.is_float()) return false;
    auto tg = static_cast<float>(b);
    m_lineThickness = tg;
    return true;
  });

  cfg_local["compute1_switch"].add_callback([this](configuru::Config &, const configuru::Config &b)->bool {
    if (!b.is_bool()) return false;
    auto tg = static_cast<bool>(b);
    m_ComputeShaderSwitch = tg;
    return true;
  });

  cfg_local["test_switch"].add_callback([this](configuru::Config &, const configuru::Config &b)->bool {
    if (!b.is_int()) return false;
    auto tg = static_cast<int>(b);
    m_TestSwitch = tg;
    return true;
  });

  cfg_local["display_switch"].add_callback([this](configuru::Config &, const configuru::Config &b)->bool {
    if (!b.is_int()) return false;
    auto tg = static_cast<int>(b);
    m_DisplaySwitch = tg;
    return true;
  });

  cfg_local["test_frequency"].add_callback([this](configuru::Config &, const configuru::Config &b)->bool {
    if (!b.is_float()) return false;
    auto tg = static_cast<float>(b);
    m_TestFrequency = tg;
    return true;
  });
  reset(MAX_PAINT_BUF_SIZE * 2);

  QSurfaceFormat format;
  format.setVersion(4, 3);
  format.setProfile(QSurfaceFormat::CoreProfile);
  setFormat(format);
}

void DataProcessWidget::reset(size_t size) {
  m_tex_buf.clear();
  m_tex_buf.resize(size);
  m_tex_buf_render_head = m_tex_buf.data() + size / 2;
}

void DataProcessWidget::resetBuf(int size) {
  makeCurrent();
  m_Ctexture->destroy();
  glActiveTexture(GL_TEXTURE0);
  m_Ctexture->create();
  m_Ctexture->setFormat(QOpenGLTexture::R32F);
  m_Ctexture->setSize(size);
  m_Ctexture->setMinificationFilter(QOpenGLTexture::Linear);
  m_Ctexture->setMagnificationFilter(QOpenGLTexture::Linear);
  m_Ctexture->allocateStorage();
  m_Ctexture->bind();
  glBindImageTexture(0, m_Ctexture->textureId(), 0, GL_FALSE, 0, GL_READ_WRITE, GL_R32F);
}

DataProcessWidget::~DataProcessWidget() {
  auto cfg = ParameterServer::instance()->GetCfgCtrlRoot();
  std::string class_obj_id = typeid(*this).name();
  class_obj_id += std::to_string(int(this));
  cfg.erase(class_obj_id);
  m_CcomputeProgram->removeAllShaders();
  m_CrenderProgram->removeAllShaders();
  makeCurrent();
  m_Ctexture->destroy();
}

QSize DataProcessWidget::minimumSizeHint() const {
  return QSize(50, 50);
}

QSize DataProcessWidget::sizeHint() const {
  return QSize(768, 512);
}

void DataProcessWidget::getData() {
  float value = 0.f;
  if (m_fileMMap) {
    size_t size = m_fileMMap->size();
    auto head = m_fileMMap->data();
    if( m_file_find_index % 600 == 0) {
      auto cfg = ParameterServer::instance()->GetCfgCtrlRoot();
      std::string class_obj_id = typeid(*this).name();
      class_obj_id += std::to_string(int(this));
      auto cfg_local = cfg[class_obj_id.c_str()];
      cfg_local["file_load_location"] = m_file_find_index;
    }

    auto cur_index = 1711 + m_file_find_index + 2;
    if (cur_index > size - 6) {
      m_file_find_index = 0;
    }

    uint l1 = (uint)(head[cur_index]);
    uint l2 = (uint)(head[cur_index + 1]);
    uint l3 = (uint)(head[cur_index + 2]);
    uint res_i = l3 | l2 << 1 | l1 << 2;
    value = 10000.f * ((float)res_i/(float)(0xffffff));

    m_file_find_index += 6;
  } else {
    value = static_cast<float>((rand() % 1000) / 1000.f);
  }

  if (m_tex_buf_render_head - m_tex_buf.data() > 0) {
    m_tex_buf_render_head--;
  } else {
    m_tex_buf_render_head = m_tex_buf.data() + MAX_PAINT_BUF_SIZE;
  }

  *m_tex_buf_render_head = value;
  *(m_tex_buf_render_head + MAX_PAINT_BUF_SIZE) = value;
}

void DataProcessWidget::initializeGL() {
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
  m_Ctexture->setFormat(QOpenGLTexture::R32F);
  m_Ctexture->setSize(m_fft_level);
  m_Ctexture->setMinificationFilter(QOpenGLTexture::Linear);
  m_Ctexture->setMagnificationFilter(QOpenGLTexture::Linear);
  m_Ctexture->allocateStorage();
  m_Ctexture->bind();

  glBindImageTexture(0, m_Ctexture->textureId(), 0, GL_FALSE, 0, GL_READ_WRITE, GL_R32F);

  m_CcomputeProgram->addShaderFromSourceFile(QOpenGLShader::Compute, DEFAULT_COMPUTE_SHADER_PATH);
  m_CcomputeProgram->link();
  m_CcomputeProgram->bind();

  m_CrenderProgram->addShaderFromSourceFile(QOpenGLShader::Vertex, DEFAULT_VERT_SHADER_PATH);
  m_CrenderProgram->addShaderFromSourceFile(QOpenGLShader::Fragment, DEFAULT_FAGERMENT_SHADER_PATH);
  m_CrenderProgram->link();
  m_CrenderProgram->bind();

  GLint posPtr = glGetAttribLocation(m_CrenderProgram->programId(), "pos");
  glVertexAttribPointer(posPtr, 2, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(posPtr);

  m_vao.release();

  connect(&timer, SIGNAL(timeout()), this, SLOT(update()));
  timer.start(16);
  m_CcomputeProgram->release();
  m_CrenderProgram->release();
}

bool DataProcessWidget::resetComputeShader(int level) {
  m_CcomputeProgram->removeAllShaders();

  std::string ora = ":/shader/example_fft";
  ora += std::to_string(level);
  ora += "_c.glsl";

  if (m_CcomputeProgram->addShaderFromSourceFile(QOpenGLShader::Compute, QString(ora.c_str()))) {
    m_CcomputeProgram->link();
    m_CcomputeProgram->bind();
    LOG(INFO) << "compute shader -" << ora << "load success.";
    m_CcomputeProgram->release();
    return true;
  } else {
    LOG(INFO) << "compute shader -" << ora << "load failed." << " back to 512 default size.";
    m_CcomputeProgram->addShaderFromSourceFile(QOpenGLShader::Compute, DEFAULT_COMPUTE_SHADER_PATH);
    return false;
  }
}

void DataProcessWidget::paintGL() {
  getData(); // for test
  static GLint srcLoc = glGetUniformLocation(m_CrenderProgram->programId(), "srcTex");
  static GLint destLoc = glGetUniformLocation(m_CcomputeProgram->programId(), "destTex");
  static GLint rollLoc = glGetUniformLocation(m_CcomputeProgram->programId(), "roll");
  static GLint testFrequencyLoc = glGetUniformLocation(m_CcomputeProgram->programId(), "test_frequency");
  static GLint testSwitchLoc = glGetUniformLocation(m_CcomputeProgram->programId(), "test_switch");
  static GLint lineThicknessLoc = glGetUniformLocation(m_CrenderProgram->programId(), "lineThickness");
  static GLint displaySwitchLoc = glGetUniformLocation(m_CrenderProgram->programId(), "display_switch");
  static GLint timeLoc = glGetUniformLocation(m_CrenderProgram->programId(), "time");
  static GLint resolutionLoc = glGetUniformLocation(m_CrenderProgram->programId(), "resolution");

  if (m_reset_computeshader_tag) {
    if (resetComputeShader(m_fft_level)) {
      resetBuf(m_fft_level);
    } else {
      m_fft_level = 512;
      resetBuf(m_fft_level);
    }
    auto cfg = ParameterServer::instance()->GetCfgCtrlRoot();
    std::string class_obj_id = typeid(*this).name();
    class_obj_id += std::to_string(int(this));
    auto cfg_local = cfg[class_obj_id.c_str()];
    cfg_local["fft_level"] = m_fft_level;
    m_reset_computeshader_tag = false;
  }
  // compute
  m_Ctexture->setData(0, QOpenGLTexture::Red, QOpenGLTexture::Float32, m_tex_buf_render_head);

  m_Cvao.bind();
  if (m_ComputeShaderSwitch) {
    m_CcomputeProgram->bind();
    m_Ctexture->bind();
    glUniform1i(destLoc, 0);
    glUniform1f(rollLoc, m_roll);
    glUniform1f(testFrequencyLoc, m_TestFrequency);
    glUniform1i(testSwitchLoc, m_TestSwitch);
    m_roll += m_speed;
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
  static float ori = GetTickCount()/ 1000.f;
  glUniform1f(timeLoc, GetTickCount()/ 1000.f - ori);
  glUniform2f(resolutionLoc, 1920.f, 1080.f);
  glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, 0);

  m_Cvao.release();
  m_CcomputeProgram->release();
  m_CrenderProgram->release();
  m_Ctexture->release();
}

void DataProcessWidget::resizeGL(int w, int h) {
  // Calculate aspect ratio
  qreal aspect = qreal(w) / qreal(h ? h : 1);

  // Set near plane to 3.0, far plane to 7.0, field of view 45 degrees
  const qreal zNear = 0.01f, zFar = 100.0f, fov = 45.0;

  // Reset projection
  m_proj.setToIdentity();

  // Set perspective projection
  m_proj.ortho(+0.5f, -0.5f, +0.5f, -0.5f, zNear, zFar);
}

void DataProcessWidget::mousePressEvent(QMouseEvent *) {
}

void DataProcessWidget::mouseMoveEvent(QMouseEvent *) {
}
