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

#include "dataprocesswidget.h"
#include <string>
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
#include "async++.h"
#include "cdf.h"
#ifdef ADLINK_32
#include "adlink.h"
#endif
#include "renderutil.h"

#include "bitdecoder/personificationdecoder.h"
#include "bitdecoder/personificationdecoderv2.h"
#include "bitdecoder/highfrequencysensivitydecoder.h"

#include "msgdecoder/tinimsgdecoderv1.h"
#include "msgdecoder/tinimsgdecoderv2.h"

#define DEFAULT_COMPUTE_SHADER_PATH ":/shader/filter_c.glsl"
#define DEFAULT_VERT_SHADER_PATH ":/shader/general_v.glsl"
#define DEFAULT_FAGERMENT_SHADER_PATH ":/shader/general_f.glsl"

#define DEFAULT_FFT_LEVEL 512
//#define FILE_FORMAT_LOCATION_FIX 1713
#define FILE_FORMAT_LOCATION_FIX 0

bool DataProcessWidget::m_transparent = false;

DataProcessWidget::DataProcessWidget(QWidget *parent)
  : QOpenGLWidget(parent),
    mousePressedTag_(false),
    mouseX_(0),
    mouseY_(0),
    ctrlPressed_(false),
    m_tex_buf_render_head(nullptr),
    m_tex_tmp_ptr(new std::vector<float>()),
    code_step1_trust_count(0),
    m_fileMMap(nullptr),
    m_fileCdfMMap(nullptr),
    m_CvertexBuffer(std::make_shared<QOpenGLBuffer>(QOpenGLBuffer::VertexBuffer)),
    m_CindexBuffer(std::make_shared<QOpenGLBuffer>(QOpenGLBuffer::IndexBuffer)),
    m_CcomputeProgram(std::make_shared<QOpenGLShaderProgram>()),
    m_CrenderProgram(std::make_shared<QOpenGLShaderProgram>()),
    m_Ctexture(std::make_shared<QOpenGLTexture>(QOpenGLTexture::Target1D)),
    m_SVGRender(nullptr),
    _decoder_active_index(-1),
    _msgdecoder(nullptr),
    decode_info(""),
    m_lineThickness(0.01f),
    m_ComputeShaderSwitch(true),
    m_TestSwitch(0),
    m_DisplaySwitch(4),
    m_file_find_index(0),
    _file_find_index_set_tmp(0),
    m_fft_level(512),
    m_reset_buf_tag(false),
    buffer_size(512),
    m_reset_computeshader_tag(false),
    m_samplingSpeed(1),
    m_position(0, 0, -1.f),
    m_scale(.5f, .5f, 1.f),
    m_rotation(0, 0, 1),
    m_angle(180.f),
    m_color(0x00FF00FF),
    m_backgroundColor(0x00000000),
    m_max_cut_filter(2.f),
    m_min_cut_filter(1.f),
    m_fft_display_scale(0.01f),
    m_decoder_unsigned(true),
    m_adlink_card_current_ID(256) {
  // QSurfaceFormat::CompatibilityProfile
  m_core = QSurfaceFormat::defaultFormat().profile() == QSurfaceFormat::CoreProfile;
  // --transparent causes the clear color to be transparent. Therefore, on systems that
  // support it, the widget will become transparent apart from the logo.
  if (m_transparent) {
    QSurfaceFormat fmt = format();
    fmt.setAlphaBufferSize(8);
    setFormat(fmt);
  }
  PLUG_PROCESS_UNIT register_table[] = {
    {"EmptyDefault",                              std::make_shared<EmptyDefault>()                  },
    {"PersonificationDecoder",                    std::make_shared<PersonificationDecoder>()        },
    {"HighFrequencySensivityDecoder",             std::make_shared<HighFrequencySensivityDecoder>() },
    {"PersonificationDecoderV2",                  std::make_shared<PersonificationDecoderV2>()      }
  };

  for (size_t i = 0; i < sizeof(register_table) / sizeof(PLUG_PROCESS_UNIT); ++i) {
    registerDecoder(register_table[i].name, register_table[i].object);
  }

  PLUG_MSG_PROCESS_UNIT msg_register_table[] = {
    {"EmptyDefault",                              EmptyMsgDecoder::create                  },
    {"TiniMsgDecoderv1",                          TiniMsgDecoderv1::create                 },
    {"TiniMsgDecoderv2",                          TiniMsgDecoderv2::create                 }
  };

  for (size_t i = 0; i < sizeof(msg_register_table) / sizeof(PLUG_MSG_PROCESS_UNIT); ++i) {
    registerMsgDecoder(msg_register_table[i].name, msg_register_table[i].create);
  }

  auto cfg = ParameterServer::instance()->GetCfgCtrlRoot();
  std::string class_obj_id = typeid(*this).name();
  class_obj_id += std::to_string(reinterpret_cast<long>(this));
  this->grabKeyboard();

  connect(this, SIGNAL(TitelChanged(const QString &)), parent, SLOT(setWindowTitle(const QString &)));

  cfg += {{class_obj_id.c_str(), {
      {"lineThickness", m_lineThickness},
      {"compute1_switch", m_ComputeShaderSwitch},
      {"test_switch", m_TestSwitch},
      {"display_switch", m_DisplaySwitch},
      {"static_file_info", {
        {"test_file_path", "empty"},
        {"file_load_location", m_file_find_index},
        {"cdf", "empty"},
        {"m_msg_decoder", "empty"},
      }},
      {"svg_background_path", "empty"},
      {"fft_level", m_fft_level},
      {"buffer_size", buffer_size},
      {"m_max_cut_filter", m_max_cut_filter},
      {"m_min_cut_filter", m_min_cut_filter},
      {"m_fft_display_scale", m_fft_display_scale},
      {"m_samplingSpeed", m_samplingSpeed},
      {"m_decoder", "empty"},
      {"m_decoder_unsigned", m_decoder_unsigned},
#ifdef ADLINK_32
      {"adlink_card_ID", m_adlink_card_current_ID},
      {"adlink_card_enable", false},
#endif
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
      std::string color_string = static_cast<std::string>(b);
      m_color = color_format_string_to_int(color_string);
      return true;
    });
  cfg_local["background_color"].add_callback([this](configuru::Config &, const configuru::Config &b)->bool {
      if (!b.is_string()) return false;
      std::string color_string = static_cast<std::string>(b);
      m_backgroundColor = color_format_string_to_int(color_string);
      return true;
    });

  cfg_local["m_decoder"].add_callback([this](configuru::Config &a, const configuru::Config &b)->bool {
    if (!b.is_string()) return false;
    auto str1 = std::string(a);
    auto str2 = std::string(b);
    if (str1 == str2) return false;
    size_t i = 0;
    for(auto it:_decoders) {
      if (it.name == str2) {
        _decoder_active_index = static_cast<int>(i);
      }
      i++;
    }
    return true;
  });

  cfg_local["static_file_info"]["m_msg_decoder"].add_callback([this](configuru::Config &a, const configuru::Config &b)->bool {
    if (!b.is_string()) return false;
    auto str1 = std::string(a);
    auto str2 = std::string(b);
    if (str1 == str2) return false;
    size_t i = 0;
    for(auto it:_msg_decoders) {
      if (it.name == str2) {
        if (decode_info.size() > 0) {
          _msgdecoder = it.create(decode_info);
        }
      }
      i++;
    }
    return true;
  });

  cfg_local["m_samplingSpeed"].add_callback([this](configuru::Config &, const configuru::Config &b)->bool {
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

  cfg_local["fft_level"].add_callback([this](configuru::Config &, const configuru::Config &b)->bool {
    if (!b.is_int()) return false;
    auto tg = static_cast<int>(b);
    int lev = 1 << 9;
    while (lev < 1 << 14) {
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

  cfg_local["static_file_info"]["file_load_location"].add_callback([this](configuru::Config &, const configuru::Config &b)->bool {
    if (!b.is_int()) return false;
    auto tg = static_cast<int>(b);
    m_file_find_index = static_cast<size_t>(tg);
    _file_find_index_set_tmp = m_file_find_index;
    LOG(INFO) << "File load location set to : " << m_file_find_index;
    return true;
  });
  cfg_local["static_file_info"]["file_load_location"].set_hiden(true);

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

  cfg_local["static_file_info"]["test_file_path"].add_callback([this](configuru::Config &a, const configuru::Config &b)->bool {
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
    sz = static_cast<size_t>(m_fileMMap->size());
    emit TitelChanged(QString(tg.c_str()));
    LOG(INFO) << "file name: " << tg << " open, size: " << sz;
    return true;
  });

  cfg_local["static_file_info"]["cdf"].add_callback([this](configuru::Config &a, const configuru::Config &b)->bool {
    if (!b.is_string()) return false;
    auto tg = static_cast<std::string>(b);
    auto ora = static_cast<std::string>(a);

    if (tg == "default") {
      if (m_fileMMap) {
        auto head = m_fileMMap->data();
        head += 512;
        decode_info = cdf::cdfStringToInfoListJson_v1_0((char *)(head));
        auto cfg = ParameterServer::instance()->GetCfgCtrlRoot();
        std::string class_obj_id = typeid(*this).name();
        class_obj_id += std::to_string(reinterpret_cast<long>(this));
        auto cfg_local = cfg[class_obj_id.c_str()];
        if (std::string(cfg_local["static_file_info"]["m_msg_decoder"]) != "empty") {
          for(auto it:_msg_decoders) {
            if (it.name == std::string(cfg_local["static_file_info"]["m_msg_decoder"])) {
              _msgdecoder = it.create(decode_info);
            }
          }
        }
      }
      return true;
    }

    if (tg == "empty") {
      if (ora != "empty" && m_fileCdfMMap) {
        LOG(INFO) << "cdf file name: " << ora << " closed";
        m_fileCdfMMap->close();
        m_fileCdfMMap = nullptr;
        decode_info = "";
      }
      return true;
    }

    if (ora != "empty" && m_fileCdfMMap) {
      LOG(INFO) << "cdf file name: " << ora << " closed";
      m_fileCdfMMap->close();
      m_fileCdfMMap = nullptr;
      decode_info = "";
    }

    size_t sz;
    m_fileCdfMMap = std::make_shared<MemoryMapped::File>(tg);
    if (!m_fileCdfMMap) return false;
    sz = static_cast<size_t>(m_fileCdfMMap->size());
    LOG(INFO) << "file name: " << tg << " open, size: " << sz;
    decode_info = cdf::cdfStringToInfoListJson_v1_0((char *)(m_fileCdfMMap->data()));
    auto cfg = ParameterServer::instance()->GetCfgCtrlRoot();
    std::string class_obj_id = typeid(*this).name();
    class_obj_id += std::to_string(reinterpret_cast<long>(this));
    auto cfg_local = cfg[class_obj_id.c_str()];
    if (std::string(cfg_local["static_file_info"]["m_msg_decoder"]) != "empty") {
      for(auto it:_msg_decoders) {
        if (it.name == std::string(cfg_local["static_file_info"]["m_msg_decoder"])) {
          _msgdecoder = it.create(decode_info);
        }
      }
    }
    return true;
  });

  cfg_local["static_file_info"].add_callback([](configuru::Config &a, const configuru::Config &b)->bool {
    if (!b.is_object()) return false;
    if (a.has_key("test_file_path"))
        a["test_file_path"] << b["test_file_path"];
    if (a.has_key("cdf"))
        a["cdf"] << b["cdf"];
    if (a.has_key("m_msg_decoder"))
        a["m_msg_decoder"] << b["m_msg_decoder"];
    if (a.has_key("file_load_location"))
        a["file_load_location"] << b["file_load_location"];
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
#ifdef ADLINK_32
  cfg_local["adlink_card_enable"].add_callback([this](configuru::Config &a, const configuru::Config &b)->bool {
      if (!b.is_bool()) return false;
      if (m_adlink_card_current_ID == 256) {
        auto cardIDVec = adlink::instance()->getAvailCardID();
        if(cardIDVec.size() > 0) {
          auto cfg = ParameterServer::instance()->GetCfgCtrlRoot();
          std::string class_obj_id = typeid(*this).name();
          class_obj_id += std::to_string(reinterpret_cast<long>(this));
          auto cfg_local = cfg[class_obj_id.c_str()];
          m_adlink_card_current_ID = cardIDVec[0];
          cfg_local["adlink_card_ID"] = m_adlink_card_current_ID;
          adlink::instance()->openCard(m_adlink_card_current_ID);
        } else {
          return false;
        }
      }
      auto tg = static_cast<bool>(b);
      auto org = static_cast<bool>(a);
      if (tg != org) {
        if (tg) {
          adlink::instance()->startAI(true, false, false, false, 8192 ,false);
          // about 64 Hz
          adlink::instance()->setRawDataCallback1([this](std::shared_ptr<std::vector<unsigned char>> data) {
            std::cout.flush();
            std::vector<float> res;
            unsigned char * cur = data->data();
            for (size_t i = 0; i < data->size() / 4; i++) {
              uint l1 = cur[0];
              uint l2 = cur[1];
              uint l3 = cur[2];
              uint res_i = l3 | l2 << 8 | l1 << 16 ;
              auto value = (static_cast<float>(res_i)/static_cast<float>(0xffffff));
              if (value < 0.5f) value += 0.5f;
              else value -= 0.5f;
              res.push_back(value);
              cur += 4;
            }
             getData(std::make_shared<std::vector<float>>(res));
          });
        } else {
          adlink::instance()->stopAI();
          m_adlink_card_current_ID = 256;
        }
        return true;
      }
      return false;
    });
#endif
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

  QFile file_testcase("D:/develop/OIL/res/test/testcase.json");
  if (file_testcase.exists()) {
    auto jsonconfig = configuru::make_json_options();
    jsonconfig.single_line_comments     = true;
    jsonconfig.block_comments           = true;
    jsonconfig.nesting_block_comments   = true;
    auto cfg_ = configuru::parse_file("D:/develop/OIL/res/test/testcase.json", jsonconfig)["test_msg_decoder"];
    LOG(INFO) << __FUNCTION__ << "load config: " << cfg;
    cfg_local << cfg_;
  }
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

void DataProcessWidget::getData(std::shared_ptr<std::vector<float>> data) {
  if (!data) {
    float value = 0.f;
    if (m_fileMMap) {
      size_t size = static_cast<size_t>(m_fileMMap->size());
      auto head = m_fileMMap->data();
      if((m_file_find_index - _file_find_index_set_tmp) % 600 == 0) {
        auto cfg = ParameterServer::instance()->GetCfgCtrlRoot();
        std::string class_obj_id = typeid(*this).name();
        class_obj_id += std::to_string(reinterpret_cast<long>(this));
        auto cfg_local = cfg[class_obj_id.c_str()];
        cfg_local["static_file_info"]["file_load_location"] = m_file_find_index;
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

void DataProcessWidget::initializeGL() {
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
  m_Ctexture->setSize(m_fft_level);
  m_tex_tmp_ptr->resize(static_cast<size_t>(m_fft_level));
  m_Ctexture->setMinificationFilter(QOpenGLTexture::Linear);
  m_Ctexture->setMagnificationFilter(QOpenGLTexture::Linear);
  m_Ctexture->allocateStorage();
  m_Ctexture->bind();

  glBindImageTexture(0, m_Ctexture->textureId(), 0, GL_FALSE, 0, GL_READ_WRITE, GL_R32F);

  m_CcomputeProgram->addShaderFromSourceCode(QOpenGLShader::Compute, getComputeShaderContent(DEFAULT_FFT_LEVEL).c_str());
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

//  connect(&timer, SIGNAL(timeout()), this, SLOT(update()));
  connect(&timer, SIGNAL(timeout()), this, SLOT(paintGLSLOT()));
  timer.start(10);
  m_CcomputeProgram->release();
  m_CrenderProgram->release();
}

bool DataProcessWidget::resetComputeShader(int level) {
  m_CcomputeProgram->removeAllShaders();
  if (m_CcomputeProgram->addShaderFromSourceCode(QOpenGLShader::Compute, getComputeShaderContent(level).c_str())) {
    m_CcomputeProgram->link();
    m_CcomputeProgram->bind();
    LOG(INFO) << "compute shader -" << level << " load success.";
    m_CcomputeProgram->release();
    return true;
  } else {
    LOG(INFO) << "compute shader -" << level << " load failed, " << " back to " << DEFAULT_FFT_LEVEL << " default size.";
    m_CcomputeProgram->addShaderFromSourceCode(QOpenGLShader::Compute, getComputeShaderContent(DEFAULT_FFT_LEVEL).c_str());
    return false;
  }
}

std::string DataProcessWidget::getComputeShaderContent(int level) {
  QFile file(DEFAULT_COMPUTE_SHADER_PATH);
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
      return "";
  QByteArray data = file.readAll();
  char *content = data.data();

  std::string ora = "#version 430 \n\
                     #define SIZE ";
  ora += std::to_string(level);
  ora += "\n";
  ora += content;
  return ora;
}

void DataProcessWidget::paintGL() {
  glEnable(GL_ALPHA_TEST);
  glEnable(GL_DEPTH_TEST);
  glDepthMask(true);

  glClearColor((float)((m_backgroundColor >> 24)&(0x000000ff)) / 255.0,
               (float)((m_backgroundColor >> 16)&(0x000000ff)) / 255.0,
               (float)((m_backgroundColor >> 8) &(0x000000ff)) / 255.0,
               (float)((m_backgroundColor)      &(0x000000ff)) / 255.0);
  if (m_adlink_card_current_ID == 256)
      for (size_t i = m_samplingSpeed; i >0; i--) {
        getData();
      }
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

    if (m_TestSwitch == 1 || m_TestSwitch == 2) {
      glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
      glFinish();
    } else {
      std::shared_ptr<ManchesterDecoder> _decoder = nullptr;
      if (_decoder_active_index >= 0)
          _decoder = _decoders[static_cast<size_t>(_decoder_active_index)].object;
      auto task_cpu = async::spawn([this, _decoder] {
        if (_decoder) _decoder->decodeBeforeWait(m_tex_tmp_ptr);
        if (_msgdecoder) {
          auto res = _decoder->getCurrentResualt();
          if (res == '0')
            _msgdecoder->decode(false);
          else if(res == '1')
            _msgdecoder->decode(true);
        }
      });

      // about 16ms ~ 32 ms
      glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
      glFinish();
      task_cpu.get();

      if (_decoder) _decoder->decodeAfterWait();

      if (_decoder && !_msgdecoder) {
        auto res = _decoder->getCurrentResualt();
        if (res == -1) {
          // todo
        } else {
          LOG(INFO) << _decoders[static_cast<size_t>(_decoder_active_index)].name << ": current res---" << res << " || file location: "
                    << m_file_find_index;
        }
      }

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
  }

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
  m_CcomputeProgram->release();
  m_CrenderProgram->release();
  m_Ctexture->release();
  glDisable(GL_ALPHA_TEST);
  glDisable(GL_DEPTH_TEST);
}

bool DataProcessWidget::registerDecoder(const std::string & name, std::shared_ptr<ManchesterDecoder> obj) {
  _decoders.push_back({name, obj});
  return true;
}

bool DataProcessWidget::registerMsgDecoder(const std::string & name, std::function<std::shared_ptr<MsgDecoder>(const std::string &cfg)>  create) {
  _msg_decoders.push_back({name, create});
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

void DataProcessWidget::mousePressEvent(QMouseEvent *event) {
  mousePressedTag_ = true;
  mouseX_ = event->x();
  mouseY_ = event->y();
}
void DataProcessWidget::mouseReleaseEvent(QMouseEvent *event) {
  mousePressedTag_ = false;
  mouseX_ = event->x();
  mouseY_ = event->y();
}

void DataProcessWidget::mouseMoveEvent(QMouseEvent *event) {
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

void DataProcessWidget::wheelEvent(QWheelEvent *event) {
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

void DataProcessWidget::keyPressEvent(QKeyEvent *event) {
  if(event->key() == Qt::Key_Control) {
    ctrlPressed_ = true;
  }
}
void DataProcessWidget::keyReleaseEvent(QKeyEvent *event) {
  if(event->key() == Qt::Key_Control) {
    ctrlPressed_ = false;
  }
}
