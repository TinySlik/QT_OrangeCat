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
#ifdef OS_WIN
#include <windows.h>
#endif
#include <QMouseEvent>
#include <QOpenGLShaderProgram>
#include <QCoreApplication>
#include <QBasicTimer>
#include "parameterserver.h"
#include "easylogging++.h"
#include "async++.h"

#define DEFAULT_COMPUTE_SHADER_PATH ":/shader/example_fft512_c.glsl"
#define DEFAULT_VERT_SHADER_PATH ":/shader/example_v.glsl"
#define DEFAULT_FAGERMENT_SHADER_PATH ":/shader/example_f.glsl"
#define FILE_FORMAT_LOCATION_FIX 1713

bool DataProcessWidget::m_transparent = false;

static GLfloat g_vertex_buffer_data[] = {
    -1.0f, -1.0f,
    -1.0f, 1.0f,
    1.0f, -1.0f,
    1.0f, 1.0f
};
static GLushort g_element_buffer_data[] = { 0, 1, 2, 3 };

DataProcessWidget::DataProcessWidget(QWidget *parent)
  : QOpenGLWidget(parent),
    m_tex_buf_render_head(nullptr),
    m_tex_tmp_ptr(new std::vector<float>()),
    code_step1_trust_count(0),
    m_fileMMap(nullptr),
    m_CvertexBuffer(std::make_shared<QOpenGLBuffer>(QOpenGLBuffer::VertexBuffer)),
    m_CindexBuffer(std::make_shared<QOpenGLBuffer>(QOpenGLBuffer::IndexBuffer)),
    m_CcomputeProgram(std::make_shared<QOpenGLShaderProgram>()),
    m_CrenderProgram(std::make_shared<QOpenGLShaderProgram>()),
    m_Ctexture(std::make_shared<QOpenGLTexture>(QOpenGLTexture::Target1D)),
    _decoder_active_index(-1),
    m_lineThickness(0.01f),
    m_ComputeShaderSwitch(true),
    m_TestSwitch(0),
    m_DisplaySwitch(4),
    m_file_find_index(0),
    m_fft_level(512),
    m_reset_buf_tag(false),
    buffer_size(512),
    m_reset_computeshader_tag(false),
    m_match_alpha(50),
    m_matchClockFrequency(100),
    m_position(0, 0, -1.f),
    m_scale(.5f, .5f, 1.f),
    m_rotation(0, 0, 1),
    m_angle(180.f),
    m_max_cut_filter(2.f),
    m_min_cut_filter(1.f),
    m_fft_display_scale(0.01f) {
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

  connect(this, SIGNAL(TitelChanged(const QString &)), parent, SLOT(setWindowTitle(const QString &)));

  cfg += {{class_obj_id.c_str(), {
      {"lineThickness", m_lineThickness},
      {"compute1_switch", m_ComputeShaderSwitch},
      {"test_switch", m_TestSwitch},
      {"display_switch", m_DisplaySwitch},
      {"test_file_path", "empty"},
      {"file_load_location", m_file_find_index},
      {"fft_level", m_fft_level},
      {"buffer_size", buffer_size},
      {"m_max_cut_filter", m_max_cut_filter},
      {"m_min_cut_filter", m_min_cut_filter},
      {"m_fft_display_scale", m_fft_display_scale},
      {"m_match_alpha", m_match_alpha},
      {"m_matchClockFrequency", m_matchClockFrequency},
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
    if (tg <= 1 << 12) {
      buffer_size = tg;
    } else {
      return false;
    }
    m_reset_buf_tag = true;
    LOG(INFO) << "Buf size set to " << buffer_size;
    return true;
  });

  cfg_local["fft_level"].add_callback([this](configuru::Config &, const configuru::Config &b)->bool {
    if (!b.is_int()) return false;
    auto tg = static_cast<int>(b);
    int lev = 1 << 9;
    while (lev < 1 << 12) {
      if (tg <= lev) {
        m_fft_level = lev;
        LOG(INFO) << "FFT level set to " << m_fft_level;
        m_reset_computeshader_tag = true;
        return true;
      }
      lev <<= 1;
    }
    return false;
  });

  cfg_local["file_load_location"].add_callback([this](configuru::Config &, const configuru::Config &b)->bool {
    if (!b.is_int()) return false;
    auto tg = static_cast<int>(b);
    m_file_find_index = static_cast<size_t>(tg);
    LOG(INFO) << "File load location set to : " << m_file_find_index;
    return true;
  });
  cfg_local["file_load_location"].set_hiden(true);
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
//    auto st = GetTickCount();
    m_fileMMap = std::make_shared<MemoryMapped::File>(tg);
    if (!m_fileMMap) return false;
    sz = m_fileMMap->size();
    emit TitelChanged(QString(tg.c_str()));
    LOG(INFO) << "file name: " << tg << " open, size: " << sz;
    return true;
  });

  cfg_local["m_max_cut_filter"].add_callback([this](configuru::Config &, const configuru::Config &b)->bool {
    if (!b.is_float()) return false;
    auto tg = static_cast<float>(b);
    m_max_cut_filter = tg;
    return true;
  });

  cfg_local["m_min_cut_filter"].add_callback([this](configuru::Config &, const configuru::Config &b)->bool {
    if (!b.is_float()) return false;
    auto tg = static_cast<float>(b);
    m_min_cut_filter = tg;
    return true;
  });

  cfg_local["m_fft_display_scale"].add_callback([this](configuru::Config &, const configuru::Config &b)->bool {
    if (!b.is_float()) return false;
    auto tg = static_cast<float>(b);
    m_fft_display_scale = tg;
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

  reset(MAX_PAINT_BUF_SIZE * 2);

  QSurfaceFormat format;
  format.setVersion(4, 3);
  format.setProfile(QSurfaceFormat::CoreProfile);
  setFormat(format);
}

void DataProcessWidget::reset(size_t size) {
  m_tex_buf.resize(size);
  m_tex_buf.clear();
  m_tex_buf_render_head = m_tex_buf.data() + size / 2;
}

void DataProcessWidget::resetBuf(int size) {
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

DataProcessWidget::~DataProcessWidget() {
  auto cfg = ParameterServer::instance()->GetCfgCtrlRoot();
  std::string class_obj_id = typeid(*this).name();
  class_obj_id += std::to_string(reinterpret_cast<long>(this));
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
  return QSize(1024, 256);
}

void DataProcessWidget::getData() {
  float value = 0.f;
  if (m_fileMMap) {
    size_t size = m_fileMMap->size();
    auto head = m_fileMMap->data();
    if( m_file_find_index % 600 == 0) {
      auto cfg = ParameterServer::instance()->GetCfgCtrlRoot();
      std::string class_obj_id = typeid(*this).name();
      class_obj_id += std::to_string(reinterpret_cast<long>(this));
      auto cfg_local = cfg[class_obj_id.c_str()];
      cfg_local["file_load_location"] = m_file_find_index;
    }

    auto cur_index = FILE_FORMAT_LOCATION_FIX + m_file_find_index ;
    if (cur_index > size - 6) {
      m_file_find_index = 0;
    }

    uint l1 = static_cast<uint>(head[cur_index]);
    uint l2 = static_cast<uint>(head[cur_index + 1]);
    uint l3 = static_cast<uint>(head[cur_index + 2]);
    uint res_i = l3 | l2 << 8 | l1 << 16;
    value = (static_cast<float>(res_i)/static_cast<float>(0xffffff));

    m_file_find_index += 6;
  } else {
//    value = static_cast<float>((rand() % 1000) / 1000.f);
      value = 0.f;
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
  m_tex_tmp_ptr->resize(static_cast<size_t>(m_fft_level));
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

  auto posPtr = static_cast<GLuint>(glGetAttribLocation(m_CrenderProgram->programId(), "pos"));
  glVertexAttribPointer(posPtr, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
  glEnableVertexAttribArray(posPtr);

  m_vao.release();

  connect(&timer, SIGNAL(timeout()), this, SLOT(update()));
  timer.start(20);
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
    LOG(INFO) << "compute shader -" << ora << "load failed, " << " back to 512 default size.";
    m_CcomputeProgram->addShaderFromSourceFile(QOpenGLShader::Compute, DEFAULT_COMPUTE_SHADER_PATH);
    return false;
  }
}

void DataProcessWidget::paintGL() {
  getData();
  static GLint srcLoc = glGetUniformLocation(m_CrenderProgram->programId(), "srcTex");
  static GLint destLoc = glGetUniformLocation(m_CcomputeProgram->programId(), "destTex");
  static GLint testSwitchLoc = glGetUniformLocation(m_CcomputeProgram->programId(), "test_switch");
  static GLint min_cut_filterLoc = glGetUniformLocation(m_CcomputeProgram->programId(), "min_cut_filter");
  static GLint max_cut_filterLoc = glGetUniformLocation(m_CcomputeProgram->programId(), "max_cut_filter");
  static GLint fft_display_scaleLoc = glGetUniformLocation(m_CcomputeProgram->programId(), "fft_display_scale");
  static GLint lineThicknessLoc = glGetUniformLocation(m_CrenderProgram->programId(), "lineThickness");
  static GLint displaySwitchLoc = glGetUniformLocation(m_CrenderProgram->programId(), "display_switch");
  static GLint timeLoc = glGetUniformLocation(m_CrenderProgram->programId(), "time");
  static GLint resolutionLoc = glGetUniformLocation(m_CrenderProgram->programId(), "resolution");

  if (m_reset_buf_tag) {
    resetBuf(buffer_size);
    m_reset_buf_tag = false;
  }

  if (m_reset_computeshader_tag) {
    if (resetComputeShader(m_fft_level)) {
      resetBuf(m_fft_level);
    } else {
      m_fft_level = 512;
      resetBuf(m_fft_level);
    }
    auto cfg = ParameterServer::instance()->GetCfgCtrlRoot();
    std::string class_obj_id = typeid(*this).name();
    class_obj_id += std::to_string(reinterpret_cast<long>(this));
    auto cfg_local = cfg[class_obj_id.c_str()];
    cfg_local["fft_level"] = m_fft_level;
    buffer_size = m_fft_level;
    cfg_local["buffer_size"] = buffer_size;
    m_reset_computeshader_tag = false;
  }
  // compute
  const float *data = m_tex_buf_render_head;
  m_Ctexture->setData(QOpenGLTexture::Red, QOpenGLTexture::Float32, data);
  m_Cvao.bind();
  if (m_ComputeShaderSwitch) {
    m_CcomputeProgram->bind();
    m_Ctexture->bind();
    glUniform1i(destLoc, 0);
    glUniform1i(testSwitchLoc, m_TestSwitch);
    glUniform1f(min_cut_filterLoc, m_min_cut_filter);
    glUniform1f(max_cut_filterLoc, m_max_cut_filter);
    glUniform1f(fft_display_scaleLoc, m_fft_display_scale);
    glDispatchCompute(static_cast<GLuint>(m_Ctexture->width()), 1, 1);

    // add cpu mutil thread code here for compute time improve.
    if (m_TestSwitch == 4 || m_TestSwitch == 5 || m_TestSwitch == 6) {
      std::shared_ptr<ManchesterDecoder> _decoder = nullptr;
      if (_decoder_active_index >= 0)
          _decoder = _decoders[static_cast<size_t>(_decoder_active_index)].object;
      auto task_cpu = async::spawn([this, _decoder] {
//        LOG(INFO) << "in size: " << m_tex_tmp_ptr->size();
//        for (size_t i = 0; i < m_tex_tmp_ptr->size(); i++) {
//          LOG(INFO) <<"in " << "i: " << i << " ||"<< (*m_tex_tmp_ptr)[i];
//        }
        if (_decoder) _decoder->decodeBeforeWait(m_tex_tmp_ptr);
      });

      glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
      glFinish();
      task_cpu.get();

      if (_decoder) _decoder->decodeAfterWait();

      if (_decoder) {
        if (_decoder->getCurrentResualt() == -1) {
          // todo
        } else {
          LOG(INFO) << _decoders[static_cast<size_t>(_decoder_active_index)].name << ": current res---" << _decoder->getCurrentResualt();
        }
      }
      if (m_TestSwitch == 4 || m_TestSwitch == 5) {
          static int count = 0;
          static int init_wait = 1024;
          static int count_case4 = 0;
          if (init_wait >= 0) init_wait --;
          count++;
          const void *const_data_ptr = m_tex_tmp_ptr->data();
          glGetTexImage(
            GL_TEXTURE_1D,
            0,
            GL_RED,
            GL_FLOAT,
            m_tex_tmp_ptr->data()
          );
          m_Ctexture->release();
          m_Ctexture->bind();

          float average = 0.f;
          auto sz = static_cast<int>(m_tex_tmp_ptr->size());
          for(int i = 0; i < sz; i++) {
            average += (*m_tex_tmp_ptr)[static_cast<size_t>(i)] / sz;
          }
          bool init_test_case = (*m_tex_tmp_ptr)[0] > average;

          bool tg = ++count_case4 >= 20;
          std::vector<int> tm;
          if (tg) count_case4 = 0;
          for(int i = 0; i < sz; i++) {
            static int count_i = 0;
            if ((*m_tex_tmp_ptr)[static_cast<size_t>(i)] > average) {
              (*m_tex_tmp_ptr)[static_cast<size_t>(i)] = 1.f;
              if (!init_test_case) {
                int res = 4;
                if (count_i > 150) {
                  res = 6;
                } else if (count_i > 15) {
                  res = 5;
                }
                if (tg && i > 30 && i < (sz - 30))
                    tm.push_back(res);
    //            LOG(INFO) << "compute decode test 0:" << res <<"   "<< count_i;
                count_i = 0;
                init_test_case = true;
              }
            } else {
              (*m_tex_tmp_ptr)[static_cast<size_t>(i)] = 0.f;
              if (tg && init_test_case) {
                int res = 1;
                if (count_i > 130) {
                  res = 3;
                } else if (count_i > 15) {
                  res = 2;
                }
    //            LOG(INFO) << "compute decode test 1:" << res <<"   "<< count_i;
                if (tg && i > 30 && i < (sz - 30))
                    tm.push_back(res);
                count_i = 0;
                init_test_case = false;
              }
            }
            count_i++;
          }
          static bool m_code_step1_tmp_start_tag = false;
          static bool m_decode_step2_tmp_start_tag = false;
          if (tg && tm.size() > 3) {
            if (!m_code_step1_tmp_start_tag ) {
              // before start
    //          static int code_step1_trust_count = 0;
              std::string tms="";
              for (size_t h = tm.size() - 2; h > 0; h--) {
                tms += std::to_string(tm[h]);
              }
              if (m_code_step1_tmp_str == tms) {
                code_step1_trust_count ++;
                if (code_step1_trust_count > 2) {
                  LOG(INFO) << "Repeat code repeat times > 2, start decode: ";
                  m_code_step1_tmp_start_tag = true;
                  for (size_t n = 0; n < tms.size(); n++) {
                    m_code_step1_tmp.push_back(tms.c_str()[n]);
                  }
                  m_code_step1_tmp_cur_head = 0;
                  m_decode_step2_tmp_cur_head = 0;
                  code_step1_trust_count = 0;
                }
              } else {
                code_step1_trust_count = 0;
              }
              m_code_step1_tmp_str = tms;
              LOG(INFO) << tms << ".";
            } else {
              // start to decode.
              std::string tms="";
              for (size_t h = tm.size() - 2; h > 0; h--) {
                tms += std::to_string(tm[h]);
              }

              std::string tp;
              for (size_t bp = m_code_step1_tmp_cur_head; bp < m_code_step1_tmp.size(); bp++) {
                tp += m_code_step1_tmp[bp];
              }
              int case_ = 0;

              // case 1:
              // xxxxx^abcdefg... + abcyyyyy -> xxxxx^abcyyyyy
              if (int(m_code_step1_tmp.size()) - int(m_code_step1_tmp_cur_head) > 2 &&!strncmp(tp.c_str(), tms.c_str(), 3)) {
    //            LOG(INFO) << "case 1";
                case_ = 1;
                if (tms.size() > tp.size()) {
    //              LOG(INFO) << "tms.size()" << tms.size() << "|" << tp.size();
                  for (size_t i = 0; i < tms.size() - tp.size(); i++) {
                    m_code_step1_tmp.push_back('0');
                  }
                }
                for (size_t n = 0; n < tms.size(); n++) {
                  m_code_step1_tmp[m_code_step1_tmp_cur_head + n] = tms.c_str()[n];
                }
              }

              // case 2:
              // xxxxx^abcdefg... + bcdyyyy -> xxxxx^abcdyyyy
              else if (int(m_code_step1_tmp.size()) - int(m_code_step1_tmp_cur_head) > 3 &&
                  !strncmp(tp.c_str() + 1, tms.c_str(), 3)) {
    //            LOG(INFO) << "case 2";
                case_ = 2;
                if (tms.size() > (tp.size() - 1)) {
    //              LOG(INFO) << "tms.size()" << tms.size() << "|" << tp.size() - 1;
                  for (size_t i = 0; i < (tms.size() - (tp.size() - 1)); i++) {
                    m_code_step1_tmp.push_back('0');
                  }
                }
                for (size_t n = 0; n < tms.size(); n++) {
                  m_code_step1_tmp[m_code_step1_tmp_cur_head + 1 + n] = tms.c_str()[n];
                }
                m_code_step1_tmp_cur_head++;
              }

              // case 3:
              // xxxxx^abc + bc
              else if (int(m_code_step1_tmp.size()) - int(m_code_step1_tmp_cur_head) == 3 &&
                  !strncmp(tp.c_str() + 1, tms.c_str(), 2)) {
                LOG(INFO) << "case 3" << "[warning] may error occor.";
                case_ = 3;
                m_code_step1_tmp_cur_head++;
              }
              // case 4:
              // xxxxx^ab + abcXXX
              else if (int(m_code_step1_tmp.size()) - int(m_code_step1_tmp_cur_head) == 2 &&
                  !strncmp(tp.c_str(), tms.c_str(), 2)) {
                LOG(INFO) << "case 4";
                case_ = 4;
                if (tms.size() > (tp.size())) {
                  LOG(INFO) << "tms.size()" << tms.size() << "|" << tp.size();
                  for (size_t i = 0; i < (tms.size() - (tp.size())); i++) {
                    m_code_step1_tmp.push_back('0');
                  }
                }
                for (size_t n = 0; n < tms.size(); n++) {
                  m_code_step1_tmp[m_code_step1_tmp_cur_head + n] = tms.c_str()[n];
                }
              } else {
                LOG(INFO) << "other case";
                m_code_step1_tmp.clear();
                m_code_step1_tmp_start_tag = false;
                m_decode_step2_tmp_start_tag = false;
              }

    //          // case 4:
    //          // xxxxx^abcdefg... + cdexxxxx

    //          // case 5:
    //          // xxxxx^abcdefg... + wabcxxxxx

    //          // case 6:
    //          // xxxxx^abcdefg... + wbcdxxxx

    //          // case 7:
    //          // xxxxx^abcdefg... + sfdgsdgsd


    #define DEBUG_CAT_STR
    #ifdef DEBUG_CAT_STR
    //          LOG(INFO) << "decode: " << tms;
              std::string tp1;
              for (size_t bp = 0; bp < m_code_step1_tmp.size(); bp++) {
                tp1 += m_code_step1_tmp[bp];
              }

              LOG(INFO) << "current cache: " << tp1 << " || curdecode_target: " << tms << " || head:" << m_code_step1_tmp_cur_head;
    #endif

              if (case_ == 2 ||
                  case_ == 3) {
                if (!m_decode_step2_tmp_start_tag &&
                    (m_code_step1_tmp[m_code_step1_tmp_cur_head] == '3' ||
                    m_code_step1_tmp[m_code_step1_tmp_cur_head] == '6')) {
                  m_decode_step2_tmp_cur_head = m_code_step1_tmp_cur_head;
                  m_decode_step2_tmp_start_tag = true;
                }
                if (m_decode_step2_tmp_start_tag) {
                  if (m_code_step1_tmp_cur_head - m_decode_step2_tmp_cur_head == 1) {
                    int t1 = m_code_step1_tmp[m_code_step1_tmp_cur_head];
                    int t2 = m_code_step1_tmp[m_decode_step2_tmp_cur_head];
                    if (t2 == '3') {
                      if (t1 == '6') {
                        LOG(INFO) << "file_location" << m_file_find_index << "---------------------" << 1;
                        m_decode_step2_tmp_cur_head++;
                      } else if (t1 == '5') {
                        LOG(INFO) << "file_location" << m_file_find_index << "---------------------" << 1;
                        m_decode_step2_tmp_cur_head++;
                      }
                    } else if (t2 == '6') {
                      if (t1 == '3') {
                        LOG(INFO) << "file_location" << m_file_find_index << "---------------------" << 0;
                        m_decode_step2_tmp_cur_head++;
                      } else if (t1 == '2') {
                        LOG(INFO) << "file_location" << m_file_find_index << "---------------------" << 0;
                        m_decode_step2_tmp_cur_head++;
                      }
                    } else if (t2 == '2') {
                      if (t1 == '6') {
                        LOG(INFO) << "file_location" << m_file_find_index << "Clock error!";
                        m_decode_step2_tmp_cur_head++;
                      } else if (t1 == '5') {
                        LOG(INFO) << "file_location" << m_file_find_index << "---------------------" << 0;
                        m_decode_step2_tmp_cur_head++;
                        m_decode_step2_tmp_cur_head++;
                      }
                    } else if (t2 == '5') {
                      if (t1 == '3') {
                        LOG(INFO) << "file_location" << m_file_find_index << "Clock error!";
                        m_decode_step2_tmp_cur_head++;
                      } else if (t1 == '2') {
                        LOG(INFO) << "file_location" << m_file_find_index << "---------------------" << 1;
                        m_decode_step2_tmp_cur_head++;
                        m_decode_step2_tmp_cur_head++;
                      }
                    }
                  } else if (m_code_step1_tmp_cur_head - m_decode_step2_tmp_cur_head > 0) {
                    LOG(ERROR) << (m_code_step1_tmp_cur_head - m_decode_step2_tmp_cur_head) << "error";
                  }
                }
              }
            }
          }

          bool is_case_5_pass = true;
          static std::vector<float> s_tmp(4096);
          if (init_wait < 0 && count >= (m_matchClockFrequency - 1)) {
            if (m_TestSwitch == 5) {
              for(int j = 0; j < sz / m_matchClockFrequency; j++) {
                int count_j = 0;
                for (int k = 0; k < m_matchClockFrequency; k++) {
                  if ((*m_tex_tmp_ptr)[static_cast<size_t>(j * m_matchClockFrequency + k) + sz % m_matchClockFrequency] > average) {
                    count_j++;
                  }
                }
      //          LOG(INFO) << "Reindex num: " << count;
                if (count_j > m_match_alpha) {
                  for (int k = 0; k < m_matchClockFrequency; k++) {
                    (*m_tex_tmp_ptr)[static_cast<size_t>(j * m_matchClockFrequency + k) + sz % m_matchClockFrequency] = 1.f;
                  }
                } else {
                  for (int k = 0; k < m_matchClockFrequency; k++) {
                    (*m_tex_tmp_ptr)[static_cast<size_t>(j * m_matchClockFrequency + k) + sz % m_matchClockFrequency] = 0.f;
                  }
                }
              }
              static bool ct_tag = true;
              if (ct_tag) {
                if ((*m_tex_tmp_ptr)[m_matchClockFrequency * 1.5 + sz % m_matchClockFrequency] > .5f && (*m_tex_tmp_ptr)[m_matchClockFrequency * 2.5 + sz % m_matchClockFrequency] < .5f) {
                  LOG(INFO) << "1";
                } else if ((*m_tex_tmp_ptr)[m_matchClockFrequency * 1.5 + sz % m_matchClockFrequency] < .5f && (*m_tex_tmp_ptr)[m_matchClockFrequency * 2.5 + sz % m_matchClockFrequency] > .5f) {
                  LOG(INFO) << "0";
                } else {
                  LOG(INFO) << "Clock Frequency Error.";
                  ct_tag = !ct_tag;
                }
              }
              s_tmp = *m_tex_tmp_ptr;
              ct_tag = !ct_tag;
            }

            count = 0;
          } else {
            if (m_TestSwitch == 5) {
              is_case_5_pass = false;
            }
          }
          if (is_case_5_pass)
              m_Ctexture->setData(QOpenGLTexture::Red, QOpenGLTexture::Float32, const_data_ptr);
          else {
              m_Ctexture->setData(QOpenGLTexture::Red, QOpenGLTexture::Float32, s_tmp.data());
          }
      } else {
        glGetTexImage(
          GL_TEXTURE_1D,
          0,
          GL_RED,
          GL_FLOAT,
          m_tex_tmp_ptr->data()
        );
        m_Ctexture->release();
        m_Ctexture->bind();

        const void *const_data_ptr = _decoder ? _decoder->displayBuffer()->data() : m_tex_tmp_ptr->data();
        m_Ctexture->setData(QOpenGLTexture::Red, QOpenGLTexture::Float32, const_data_ptr);
      }
//      static int asdadsy = 0;
//      m_test_tmp.push_back(asdadsy ++);
//      LOG(INFO) << "out size: " << m_test_tmp.size();
//      for (size_t i = 0; i < m_test_tmp.size(); i++) {
//        LOG(INFO) << "out "<< m_test_tmp[i];
//        qDebug() << "out "<< m_test_tmp[i];
//      }
    // ---end of cpu mutil thread here

    } else {
      glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
      glFinish();
    }
  }

  // draw
  m_CrenderProgram->bind();
  // glClear(GL_COLOR_BUFFER_BIT);
  m_Ctexture->bind();
  glUniform1i(srcLoc, 0);
  glUniform1i(displaySwitchLoc, m_DisplaySwitch);
  glUniform1f(lineThicknessLoc, m_lineThickness);
//  static float ori = GetTickCount()/ 1000.f;
  glUniform1f(timeLoc, 2000);
  glUniform2f(resolutionLoc, 1920.f, 1080.f);

  // Calculate model view transformation
  QMatrix4x4 matrix;
  matrix.translate(m_position);
  matrix.rotate(m_angle, m_rotation);
  matrix.scale(m_scale);

  // Set modelview-projection matrix
  m_CrenderProgram->setUniformValue("mvp_matrix", m_proj * matrix);

  glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, nullptr);

  m_Cvao.release();
  m_CcomputeProgram->release();
  m_CrenderProgram->release();
  m_Ctexture->release();
}

bool DataProcessWidget::registerDecoder(const std::string & name, std::shared_ptr<ManchesterDecoder> obj) {
  _decoders.push_back({name, obj});
  return true;
}

bool DataProcessWidget::unRegisterDecoder(const std::string & name) {
  for (std::vector<PLUG_PROCESS_UNIT>::iterator iter = _decoders.begin(); iter != _decoders.end(); ++iter) {
    if (iter->name == name) {
      _decoders.erase(iter);
      return true;
    }
  }
  return false;
}

void DataProcessWidget::resizeGL(int /*w*/, int /*h*/) {
  // Calculate aspect ratio
//  qreal aspect = qreal(w) / qreal(h ? h : 1);

  // Set near plane to 3.0, far plane to 7.0, field of view 45 degrees
  const float zNear = 0.01f, zFar = 100.0f ; //, fov = 45.0;

  // Reset projection
  m_proj.setToIdentity();

  // Set perspective projection
  m_proj.ortho(+0.5f, -0.5f, +0.5f, -0.5f, zNear, zFar);
}

void DataProcessWidget::mousePressEvent(QMouseEvent *) {
}

void DataProcessWidget::mouseMoveEvent(QMouseEvent *) {
}
