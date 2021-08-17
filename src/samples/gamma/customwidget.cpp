#include "customwidget.h"
#include "parameterserver.h"
#include "renderutil.h"
#include "easylogging++.h"
#include "LasParser.h"
#include "time.h"

CustomWidget::CustomWidget(QWidget *parent) : QWidget(parent), chart(nullptr) {
  qRegisterMetaType<std::shared_ptr<std::vector<PAINT_LINE_UNIT>>>("paint_units");
  _lineChatWidth = this->width();
  _lineChatHeight = this->height();
  auto cfg = ParameterServer::instance()->GetCfgCtrlRoot();
  std::string class_obj_id = "main";

  cfg += {{class_obj_id.c_str(), {
      {"dynamic_mode", 0},
      {"lines", {configuru::Config::array(
        {
          {{"line_color", "#00CD00FF"},    {"line_width", 1}, {"line_colum", 0}, {"title", "GA_1"}, {"unit", "GAPI"}, {"min", 0},{"max", 200} ,
           {"data", ":/test/20210705-123650_wave.las"}},
//          {{"window_type", "glwidget"},    {"line_colum", 2}, {"object",
//                                                                {
//                                                                  {"background_color", "#CDCDCD"}
//                                                                }
//           }
//          },
          {{"line_color", "#EEEE00FF"},    {"line_width", 3}, {"line_colum", 1}, {"title", "GA_3"}, {"unit", "GAPI"}, {"min", 0},{"max", 200} ,
           {"data", nullptr}},
          {{"line_color", "#CDCDCDFF"},    {"line_width", 3}, {"line_colum", 1}, {"title", "GA_4"}, {"unit", "GAPI"}, {"min", 0},{"max", 200} ,
           {"data", nullptr}},
          {{"line_color", "#ff0e00FF"},    {"line_width", 3}, {"line_colum", 2}, {"title", "GA_5"}, {"unit", "GAPI"}, {"min", 0},{"max", 200} ,
           {"data", nullptr}},
        })
      }},
      {"size", {
        {"width", _lineChatWidth},
        {"height", _lineChatHeight}
      }},
      {"max_page_count", 10},
      {"normal_data_count_perpage", 100},
      {"normal_unit_perpage", 10},
      {"min_unit_count_perpage", 5},
      {"max_axial_label_count", 5},
      {"min_bar_value", 0},
      {"max_bar_value", 200},
      {"min_range_value", 0},
      {"max_range_value", 1000},
      {"snap_status", false}
    }}
  };

  auto createNewLines = [this](const configuru::Config &config) -> std::vector<PAINT_LINE_UNIT> {
    if (!config.is_array()) return{};
    auto arry = config.as_array();
    auto res = std::vector<PAINT_LINE_UNIT>();
    int special_count = 0;
    for (size_t i = 0; i < arry.size(); i++) {
      PAINT_LINE_UNIT tmp = {QColor(155, 155, 155, 255), 3, 0, QObject::tr("DEFAULT"), QObject::tr("DEFAULT"), 0, 200, nullptr};
      if(arry[i].has_key("line_colum")) {
        tmp.colum = static_cast<int>(arry[i]["line_colum"]);
      } else {
        continue;
      }
      if(arry[i].has_key("line_color")) {
        tmp.color = color_format_string_to_qcolor(static_cast<std::string>(arry[i]["line_color"]));
      }
      std::string line_window_type = "chart";
      if(arry[i].has_key("window_type")) {
        line_window_type = static_cast<std::string>(arry[i]["window_type"]);
      }
      if (line_window_type == "chart") {
        if(arry[i].has_key("line_width")) {
          tmp.width = static_cast<int>(arry[i]["line_width"]);
        }
        if(arry[i].has_key("title")) {
          tmp.name = static_cast<std::string>(arry[i]["title"]).c_str();
        }
        if(arry[i].has_key("unit")) {
          tmp.unit = static_cast<std::string>(arry[i]["unit"]).c_str();
        }
        if(arry[i].has_key("min")) {
          tmp.min = static_cast<int>(arry[i]["min"]);
        }
        if(arry[i].has_key("max")) {
          tmp.max = static_cast<int>(arry[i]["max"]);
        }
        if(arry[i].has_key("data")) {
          if (arry[i]["data"].is_string()) {
//            uint64_t time = get_micro_second();
            QFile file(static_cast<std::string>(arry[i]["data"]).c_str());
            if(!file.open(QFile::ReadOnly)) {
              LOG(INFO) << "no file named " << static_cast<std::string>(arry[i]["data"]).c_str() << "exeist.";
            } else {
              QString fileStr = file.readAll();
              LasParser a;
              a.importString(fileStr);
//              qDebug() << get_micro_second() - time;
//              LOG(INFO) << a.toString().toLatin1().data();
              file.close();
            }
          }
//        tmp.max = static_cast<int>(arry[i]["max"]);
        }
        res.push_back(tmp);
      } else if (line_window_type == "glwidget" && arry[i].has_key("object") && arry[i]["object"].is_object()) {
        special_count ++;
        if (m_special_widget.size() == 0) {
          SPEC_UNIT a = {nullptr , (int)(tmp.colum), arry[i]["object"]};
          auto widget = new DisplayWidget(this);
          arry[i]["object"]["link"] = widget -> getParamIndexStr();
          auto cfg = ParameterServer::instance()->GetCfgCtrlRoot();
          cfg[widget -> getParamIndexStr().c_str()] << arry[i]["object"];
          a.object = widget;
          m_special_widget.push_back(a);
          if (chart)
            chart->stackUnder(widget);
        }
      }
      if (special_count == 0) {
        for (size_t k = 0;k < m_special_widget.size(); k++) {
          m_special_widget[k].object->deleteLater();
        }
        m_special_widget.clear();
      }
    }
    return res;
  };

  auto cfg_local = cfg[class_obj_id.c_str()];
  cfg_local["lines"].add_callback([this, createNewLines](configuru::Config &a, const configuru::Config &b)->bool {
    if (!b.is_array()) return false;
    m_lines = createNewLines(b);
    emit NewQtekLineChatSIG();
    return true;
  });
  cfg_local["size"].add_callback([this](configuru::Config &, const configuru::Config &b)->bool {
    if (!b.is_object()) return false;
    if(b.has_key("width"))
    _lineChatWidth = (int)(b["width"]);
    if(b.has_key("height"))
    _lineChatHeight = (int)(b["height"]);
    emit NewQtekLineChatSIG();
    return true;
  });
  cfg_local["snap_status"].add_callback([this](configuru::Config &a, const configuru::Config &b)->bool {
    if (!b.is_bool()) return false;
//    this->slotGrabWidgetScreen();
    emit CaptureSIG();
    return false;
  });

  m_lines = createNewLines(cfg_local["lines"]);
  connect(this, SIGNAL(NewQtekLineChatSIG()), this, SLOT(NewQtekLineChat()));
  connect(this, SIGNAL(CaptureSIG()), this, SLOT(Capture()));
}

CustomWidget::~CustomWidget() {
  disconnect(this, SIGNAL(NewQtekLineChatSIG()), this, SLOT(NewQtekLineChat()));
  disconnect(this, SIGNAL(CaptureSIG()), this, SLOT(Capture()));
}

void CustomWidget::NewQtekLineChat(std::vector<PAINT_LINE_UNIT> lines) {
  if (chart)
    chart->deleteLater();
  chart = new QtekLineChat(lines, this);
  chart->show();
}

void CustomWidget::NewQtekLineChat() {
  if (chart)
    chart->deleteLater();
  chart = new QtekLineChat(m_lines, this);
  chart->show();
  chart->resize(_lineChatWidth, _lineChatHeight);
  for (size_t i = 0; i < m_special_widget.size(); ++i) {
    auto rect = chart->getColumRect(m_special_widget[i].colum);
    m_special_widget[i].object->setGeometry(chart->getColumRect(m_special_widget[i].colum));
    chart->stackUnder(m_special_widget[i].object);
  }
}

void CustomWidget::Capture() {
  slotGrabWidgetScreen();
}

void CustomWidget::slotGrabWidgetScreen() {
  if (chart)
    chart->capture();
}

void CustomWidget::resizeEvent(QResizeEvent *event) {
  auto cfg = ParameterServer::instance()->GetCfgCtrlRoot();
  std::string class_obj_id = "main";
  auto cfg_local = cfg[class_obj_id.c_str()];
  _lineChatWidth = this->width();
  _lineChatHeight = this->height();
  cfg_local["size"]["width"] = _lineChatWidth;
  cfg_local["size"]["height"] = _lineChatHeight;
  if (chart) {
    chart->resize(_lineChatWidth, _lineChatHeight);
    for (size_t i = 0; i < m_special_widget.size(); ++i) {
      auto rect = chart->getColumRect(m_special_widget[i].colum);
      m_special_widget[i].object->setGeometry(chart->getColumRect(m_special_widget[i].colum));
      chart->stackUnder(m_special_widget[i].object);
    }
  }
}
