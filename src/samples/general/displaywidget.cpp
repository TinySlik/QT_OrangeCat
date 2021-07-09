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
#include "displaywidget.h"
#include <math.h>
#ifdef OS_WIN
#include <windows.h>
#endif
#include <QMouseEvent>
#include <QOpenGLShaderProgram>
#include <QCoreApplication>
#include <QBasicTimer>
#include <QtSvg>
#include "parameterserver.h"
#include "easylogging++.h"
#include "time.h"
#include "renderutil.h"

#define DEFAULT_VERT_SHADER_PATH ":/shader/general_v.glsl"
#define DEFAULT_FAGERMENT_SHADER_PATH ":/shader/general_f.glsl"

#define DEFAULT_FFT_LEVEL 512
#define FILE_FORMAT_LOCATION_FIX 0

bool DisplayWidget::m_transparent = false;

DisplayWidget::DisplayWidget(QWidget *parent)
  : QOpenGLWidget(parent),
    mousePressedTag_(false),
    mouseX_(0),
    mouseY_(0),
    ctrlPressed_(false),
    m_tex_buf_render_head(nullptr),
    m_tex_tmp_ptr(new std::vector<float>()),
    code_step1_trust_count(0),
    m_fileMMap(nullptr),
    m_CvertexBuffer(std::make_shared<QOpenGLBuffer>(QOpenGLBuffer::VertexBuffer)),
    m_CrenderProgram(std::make_shared<QOpenGLShaderProgram>()),
    m_Ctexture(std::make_shared<QOpenGLTexture>(QOpenGLTexture::Target1D)),
    m_SVGRender(nullptr),
    m_lineThickness(0.01f),
    m_TestSwitch(0),
    m_DisplaySwitch(5),
    m_file_find_index(0),
    _file_find_index_set_tmp(0),
    m_reset_buf_tag(false),
    buffer_size(512),
    m_samplingSpeed(1),
    m_position(0, 0, -1.f),
    m_scale(.5f, .5f, 1.f),
    m_rotation(0, 0, 1),
    m_angle(180.f),
    m_color(0x00FF00FF),
    m_backgroundColor(0x00000000),
    m_decoder_unsigned(true) {
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
  class_obj_id += std::to_string(reinterpret_cast<long>(this));
  this->grabKeyboard();

  connect(this, SIGNAL(TitelChanged(const QString &)), parent, SLOT(setWindowTitle(const QString &)));

  cfg += {{class_obj_id.c_str(), {
      {"lineThickness", m_lineThickness},
      {"test_switch", m_TestSwitch},
      {"display_switch", m_DisplaySwitch},
      {"test_file_path", "empty"},
      {"svg_background_path", "empty"},
      {"file_load_location", m_file_find_index},
      {"buffer_size", buffer_size},
      {"m_samplingSpeed", m_samplingSpeed},
      {"m_decoder_unsigned", m_decoder_unsigned},
      {"front_color", color_format_int_to_string(m_color).c_str()},
      {"background_color", color_format_int_to_string(m_backgroundColor).c_str()},
      {"transform", {
        {
          "m_translate", {
            {"x", m_position.x()},
            {"y", m_position.y()},
            {"z", m_position.z()},
          }
        },
        {
          "m_rotate", {
            {"x", m_rotation.x()},
            {"y", m_rotation.y()},
            {"z", m_rotation.z()},
          },
        },
        {"m_angle", m_angle},
        {
          "m_scale", {
            {"x", m_scale.x()},
            {"y", m_scale.y()},
            {"z", m_scale.z()},
          }
        }
      }}
    }}
  };

  auto cfg_local = cfg[class_obj_id.c_str()];

  cfg_local["front_color"].add_callback([this](configuru::Config &, const configuru::Config &b)->bool {
      if (!b.is_string()) return false;
      std::string color_string = (std::string)b;
      m_color = color_format_string_to_int(color_string);
      return true;
    });
  cfg_local["background_color"].add_callback([this](configuru::Config &, const configuru::Config &b)->bool {
      if (!b.is_string()) return false;
      std::string color_string = (std::string)b;
      m_backgroundColor = color_format_string_to_int(color_string);
      return true;
    });

  cfg_local["m_samplingSpeed"].add_callback([this](configuru::Config &a, const configuru::Config &b)->bool {
    if (!b.is_int()) return false;
    auto tg = int(b);
    m_samplingSpeed = tg;
    return true;
  });

  cfg_local["transform"]["m_translate"].add_callback([this](configuru::Config &, const configuru::Config &b)->bool {
    m_position.setX(static_cast<float>(b["x"]));
    m_position.setY(static_cast<float>(b["y"]));
    m_position.setZ(static_cast<float>(b["z"]));
    return true;
  });

  cfg_local["transform"]["m_rotate"].add_callback([this](configuru::Config &, const configuru::Config &b)->bool {
    m_rotation.setX(static_cast<float>(b["x"]));
    m_rotation.setY(static_cast<float>(b["y"]));
    m_rotation.setZ(static_cast<float>(b["z"]));
    return true;
  });

  cfg_local["transform"]["m_angle"].add_callback([this](configuru::Config &, const configuru::Config &b)->bool {
    m_angle = static_cast<float>(b);
    return true;
  });

  cfg_local["transform"]["m_scale"].add_callback([this](configuru::Config &, const configuru::Config &b)->bool {
    m_scale.setX(static_cast<float>(b["x"]));
    m_scale.setY(static_cast<float>(b["y"]));
    m_scale.setZ(static_cast<float>(b["z"]));
    return true;
  });

  cfg_local["buffer_size"].add_callback([this](configuru::Config &, const configuru::Config &b)->bool {
    if (!b.is_int()) return false;
    auto tg = static_cast<int>(b);
    if (tg <= 1 << 28) {
      buffer_size = tg;
    } else {
      return false;
    }
    m_reset_buf_tag = true;
    LOG(INFO) << "Buf size set to " << buffer_size;
    return true;
  });

  cfg_local["file_load_location"].add_callback([this](configuru::Config &, const configuru::Config &b)->bool {
    if (!b.is_int()) return false;
    auto tg = static_cast<int>(b);
    m_file_find_index = static_cast<size_t>(tg);
    _file_find_index_set_tmp = m_file_find_index;
    LOG(INFO) << "File load location set to : " << m_file_find_index;
    return true;
  });
  cfg_local["file_load_location"].set_hiden(true);

  cfg_local["svg_background_path"].add_callback([this](configuru::Config &a, const configuru::Config &b)->bool {
    if (!b.is_string()) return false;
    auto tg = static_cast<std::string>(b);
    auto ora = static_cast<std::string>(a);
    if (!m_SVGRender) m_SVGRender = std::make_shared<QSvgRenderer>();

    if (tg == "empty") {
      if (ora != "empty" && m_SVGRender->isValid()) {
        LOG(INFO) << "file name: " << ora << " closed";
        m_SVGRender = nullptr;
      }
      return true;
    }

    if (m_SVGRender->load(QLatin1String(tg.c_str()))) {
      LOG(INFO) << "pic name: " << tg << " load";
      return true;
    }
    else return false;
  });

  cfg_local["test_file_path"].add_callback([this](configuru::Config &a, const configuru::Config &b)->bool {
    if (!b.is_string()) return false;
    auto tg = static_cast<std::string>(b);
    auto ora = static_cast<std::string>(a);
    if (tg == "empty") {
      if (ora != "empty" && m_fileMMap) {
        LOG(INFO) << "file name: " << ora << " closed";
        m_fileMMap->close();
        m_fileMMap = nullptr;
        m_file_find_index = 0;
      }
      return true;
    }

    if (ora != "empty" && m_fileMMap) {
      LOG(INFO) << "file name: " << ora << " closed";
      m_fileMMap->close();
      m_fileMMap = nullptr;
      m_file_find_index = 0;
    }

    size_t sz;
    m_fileMMap = std::make_shared<MemoryMapped::File>(tg);
    if (!m_fileMMap) return false;
    sz = m_fileMMap->size();
    emit TitelChanged(QString(tg.c_str()));
    LOG(INFO) << "file name: " << tg << " open, size: " << sz;
    return true;
  });

  cfg_local["lineThickness"].add_callback([this](configuru::Config &, const configuru::Config &b)->bool {
    if (!b.is_float()) return false;
    auto tg = static_cast<float>(b);
    m_lineThickness = tg;
    return true;
  });


  cfg_local["m_decoder_unsigned"].add_callback([this](configuru::Config &, const configuru::Config &b)->bool {
    if (!b.is_bool()) return false;
    auto tg = static_cast<bool>(b);
    m_decoder_unsigned = tg;
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

  reset(MAX_PAINT_BUF_SIZE * 2);

  QSurfaceFormat format;
  format.setVersion(4, 3);
  format.setProfile(QSurfaceFormat::CoreProfile);
  setFormat(format);
}

void DisplayWidget::reset(size_t size) {
  m_tex_buf.resize(size);
  m_tex_buf.clear();
  m_tex_buf_render_head = m_tex_buf.data() + size / 2;
}

void DisplayWidget::resetBuf(int size) {
  makeCurrent();
  m_Ctexture->destroy();
  glActiveTexture(GL_TEXTURE0);
  m_Ctexture->create();
  m_Ctexture->setFormat(QOpenGLTexture::R32F);
  m_Ctexture->setSize(size);
  m_tex_tmp_ptr->resize(static_cast<size_t>(size));
  m_Ctexture->setMinificationFilter(QOpenGLTexture::Linear);
  m_Ctexture->setMagnificationFilter(QOpenGLTexture::Linear);
  m_Ctexture->allocateStorage();
  m_Ctexture->bind();
  glBindImageTexture(0, m_Ctexture->textureId(), 0, GL_FALSE, 0, GL_READ_WRITE, GL_R32F);
}

DisplayWidget::~DisplayWidget() {
  auto cfg = ParameterServer::instance()->GetCfgCtrlRoot();
  std::string class_obj_id = typeid(*this).name();
  class_obj_id += std::to_string(reinterpret_cast<long>(this));
  cfg.erase(class_obj_id);
  m_CrenderProgram->removeAllShaders();
  makeCurrent();
  m_Ctexture->destroy();
}

QSize DisplayWidget::minimumSizeHint() const {
  return QSize(50, 50);
}

QSize DisplayWidget::sizeHint() const {
  return QSize(1024, 256);
}


void DisplayWidget::getData(std::shared_ptr<std::vector<float>> data) {
  if (!data) {
    float value = 0.f;
    if (m_fileMMap) {
      size_t size = m_fileMMap->size();
      auto head = m_fileMMap->data();
      if((m_file_find_index - _file_find_index_set_tmp) % 600 == 0) {
        auto cfg = ParameterServer::instance()->GetCfgCtrlRoot();
        std::string class_obj_id = typeid(*this).name();
        class_obj_id += std::to_string(reinterpret_cast<long>(this));
        auto cfg_local = cfg[class_obj_id.c_str()];
        cfg_local["file_load_location"] = m_file_find_index;
      }

      auto cur_index = FILE_FORMAT_LOCATION_FIX + m_file_find_index ;
      if (cur_index > size - 6) {
        m_file_find_index = _file_find_index_set_tmp;
      }

      uint l1 = static_cast<uint>(head[cur_index]);
      uint l2 = static_cast<uint>(head[cur_index + 1]);
      uint l3 = static_cast<uint>(head[cur_index + 2]);
      if (m_decoder_unsigned) {
        uint res_i = l3 | l2 << 8 | l1 << 16;
        value = (static_cast<float>(res_i)/static_cast<float>(0xffffff));
      } else {
        uint res_i = l3 | l2 << 8 | l1 << 16;
        value = (static_cast<float>(res_i)/static_cast<float>(0xffffff));
        if (value < 0.5f) value += 0.5f;
        else value -= 0.5f;
      }

      m_file_find_index += 6;
    }

    if (m_tex_buf_render_head - m_tex_buf.data() > 0) {
      m_tex_buf_render_head--;
    } else {
      m_tex_buf_render_head = m_tex_buf.data() + MAX_PAINT_BUF_SIZE;
    }

    *m_tex_buf_render_head = value;
    *(m_tex_buf_render_head + MAX_PAINT_BUF_SIZE) = value;
  } else {
    for (size_t i = 0; i < data->size(); i++) {
      float value = (*data)[i];
      if (m_tex_buf_render_head - m_tex_buf.data() > 0) {
        m_tex_buf_render_head--;
      } else {
        m_tex_buf_render_head = m_tex_buf.data() + MAX_PAINT_BUF_SIZE;
      }

      *m_tex_buf_render_head = value;
      *(m_tex_buf_render_head + MAX_PAINT_BUF_SIZE) = value;
    }
  }
}

void DisplayWidget::initializeGL() {
  initializeOpenGLFunctions();
  glClearColor((float)((m_backgroundColor >> 24)&(0x000000ff)) / 255.0,
               (float)((m_backgroundColor >> 16)&(0x000000ff)) / 255.0,
               (float)((m_backgroundColor >> 8) &(0x000000ff)) / 255.0,
               (float)((m_backgroundColor)      &(0x000000ff)) / 255.0);

  m_Cvao.create();
  if (m_Cvao.isCreated()) {
      m_Cvao.bind();
      LOG(INFO) << "VAO created!";
  }

  for (size_t i = 0; i<= 1024; i++ ) {
    verts_.push_back(-1.0 + i * 2.f / 1024.0);
    verts_.push_back(-1.0);
    verts_.push_back(-1.0 + i * 2.f / 1024.0);
    verts_.push_back(1.0);
  }

  m_CvertexBuffer->create();
  m_CvertexBuffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
  m_CvertexBuffer->bind();
  m_CvertexBuffer->allocate(verts_.data(), sizeof(GLfloat) * verts_.size());

  glActiveTexture(GL_TEXTURE0);
  m_Ctexture->create();
  m_Ctexture->setFormat(QOpenGLTexture::R32F);
  m_Ctexture->setSize(512);
  m_tex_tmp_ptr->resize(static_cast<size_t>(512));
  m_Ctexture->setMinificationFilter(QOpenGLTexture::Linear);
  m_Ctexture->setMagnificationFilter(QOpenGLTexture::Linear);
  m_Ctexture->allocateStorage();
  m_Ctexture->bind();

  glBindImageTexture(0, m_Ctexture->textureId(), 0, GL_FALSE, 0, GL_READ_WRITE, GL_R32F);

  m_CrenderProgram->addShaderFromSourceFile(QOpenGLShader::Vertex, DEFAULT_VERT_SHADER_PATH);
  m_CrenderProgram->addShaderFromSourceFile(QOpenGLShader::Fragment, DEFAULT_FAGERMENT_SHADER_PATH);
  m_CrenderProgram->link();
  m_CrenderProgram->bind();

  auto posPtr = static_cast<GLuint>(glGetAttribLocation(m_CrenderProgram->programId(), "pos"));
  glVertexAttribPointer(posPtr, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
  glEnableVertexAttribArray(posPtr);

  m_vao.release();

  connect(&timer, SIGNAL(timeout()), this, SLOT(update()));
  timer.start(10);
  m_CrenderProgram->release();
}

void DisplayWidget::paintGL() {
  glEnable(GL_ALPHA_TEST);
  glEnable(GL_DEPTH_TEST);
  glDepthMask(true);

  glClearColor((float)((m_backgroundColor >> 24)&(0x000000ff)) / 255.0,
               (float)((m_backgroundColor >> 16)&(0x000000ff)) / 255.0,
               (float)((m_backgroundColor >> 8) &(0x000000ff)) / 255.0,
               (float)((m_backgroundColor)      &(0x000000ff)) / 255.0);

  getData();
  static GLint srcLoc = glGetUniformLocation(m_CrenderProgram->programId(), "srcTex");
  static GLint lineThicknessLoc = glGetUniformLocation(m_CrenderProgram->programId(), "lineThickness");
  static GLint displaySwitchLoc = glGetUniformLocation(m_CrenderProgram->programId(), "display_switch");
  static GLint timeLoc = glGetUniformLocation(m_CrenderProgram->programId(), "time");
  static GLint resolutionLoc = glGetUniformLocation(m_CrenderProgram->programId(), "resolution");

  if (m_SVGRender) {
    QPainter p(this);
    p.setRenderHint(QPainter::HighQualityAntialiasing);
    p.save();
    p.translate(width()/2, height()/2);
    p.translate(-width()/2, -height()/2);
    m_SVGRender->render(&p);
    p.restore();
  }

  if (m_reset_buf_tag) {
    resetBuf(buffer_size);
    m_reset_buf_tag = false;
  }

  // compute
  const float *data = m_tex_buf_render_head;
  m_Ctexture->setData(QOpenGLTexture::Red, QOpenGLTexture::Float32, data);
  m_Cvao.bind();
  // draw
  m_CrenderProgram->bind();
  // glClear(GL_COLOR_BUFFER_BIT);
  m_Ctexture->bind();
  glUniform1i(srcLoc, 0);
  glUniform1i(displaySwitchLoc, m_DisplaySwitch);
  glUniform1f(lineThicknessLoc, m_lineThickness);

  auto color = color_format_int_to_qcolor(m_color);
  m_CrenderProgram->setUniformValue("front_color",
                                   (GLfloat)(color.redF()),
                                   (GLfloat)(color.greenF()),
                                   (GLfloat)(color.blueF()),
                                   (GLfloat)(color.alphaF()));
  auto back_color = color_format_int_to_qcolor(m_backgroundColor);
  m_CrenderProgram->setUniformValue("background_color",
                                   (GLfloat)(back_color.redF()),
                                   (GLfloat)(back_color.greenF()),
                                   (GLfloat)(back_color.blueF()),
                                   (GLfloat)(back_color.alphaF()));

#ifdef OS_WIN
  static float ori = get_micro_second() / 1000.f;
  glUniform1f(timeLoc, float((get_micro_second() / 1000.f)) - ori);
#else
  glUniform1f(timeLoc, float((get_micro_second() % 1000000000)) / 1000.f);
#endif

  glUniform2f(resolutionLoc, 1920.f, 1080.f);

  // Calculate model view transformation
  QMatrix4x4 matrix;
  matrix.translate(m_position);
  matrix.rotate(m_angle, m_rotation);
  matrix.scale(m_scale);

  // Set modelview-projection matrix
  m_CrenderProgram->setUniformValue("mvp_matrix", m_proj * matrix);

//  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 2048);

  m_Cvao.release();
  m_CrenderProgram->release();
  m_Ctexture->release();
  glDisable(GL_ALPHA_TEST);
  glDisable(GL_DEPTH_TEST);
}

void DisplayWidget::resizeGL(int /*w*/, int /*h*/) {
  // Calculate aspect ratio
//  qreal aspect = qreal(w) / qreal(h ? h : 1);

  // Set near plane to 3.0, far plane to 7.0, field of view 45 degrees
  const float zNear = 0.01f, zFar = 100.0f ; //, fov = 45.0;

  // Reset projection
  m_proj.setToIdentity();

  // Set perspective projection
  m_proj.ortho(+0.5f, -0.5f, +0.5f, -0.5f, zNear, zFar);
}

void DisplayWidget::mousePressEvent(QMouseEvent *event) {
  mousePressedTag_ = true;
  mouseX_ = event->x();
  mouseY_ = event->y();
}
void DisplayWidget::mouseReleaseEvent(QMouseEvent *event) {
  mousePressedTag_ = false;
  mouseX_ = event->x();
  mouseY_ = event->y();
}

void DisplayWidget::mouseMoveEvent(QMouseEvent *event) {
  auto cfg = ParameterServer::instance()->GetCfgCtrlRoot();
  std::string class_obj_id = typeid(*this).name();
  class_obj_id += std::to_string(reinterpret_cast<long>(this));
  auto cfg_local = cfg[class_obj_id.c_str()];
  configuru::Config translate{
    {"x",     m_position.x() - (float(event->x()) / (float)(this->width()) - float(mouseX_) / (float)(this->width()))},
    {"y",     m_position.y() + (float(event->y()) / (float)(this->height()) - float(mouseY_) / (float)(this->height()))},
    {"z",     m_position.z()}
  };
  cfg_local["transform"]["m_translate"] << translate;
  mouseX_ = event->x();
  mouseY_ = event->y();
}

void DisplayWidget::wheelEvent(QWheelEvent *event) {
  auto cfg = ParameterServer::instance()->GetCfgCtrlRoot();
  std::string class_obj_id = typeid(*this).name();
  class_obj_id += std::to_string(reinterpret_cast<long>(this));
  auto cfg_local = cfg[class_obj_id.c_str()];
  configuru::Config sc{
    {"x",     (ctrlPressed_) ? m_scale.x() : (m_scale.x() + float(event->angleDelta().ry()) * 1.0 / 4800.0)},
    {"y",     (!ctrlPressed_) ? m_scale.y() : (m_scale.y() + float(event->angleDelta().ry()) * 1.0 / 4800.0)},
    {"z",     m_scale.z()}
  };

  cfg_local["transform"]["m_scale"] << sc;
}

void DisplayWidget::keyPressEvent(QKeyEvent *event) {
  if(event->key() == Qt::Key_Control) {
    ctrlPressed_ = true;
  }
}
void DisplayWidget::keyReleaseEvent(QKeyEvent *event) {
  if(event->key() == Qt::Key_Control) {
    ctrlPressed_ = false;
  }
}
