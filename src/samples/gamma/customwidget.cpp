#include "customwidget.h"
#include "parameterserver.h"
#include "renderutil.h"

#include <QMetaType>

CustomWidget::CustomWidget(QWidget *parent) : QWidget(parent), chart(nullptr)
{
  qRegisterMetaType<std::shared_ptr<std::vector<PAINT_LINE_UNIT>>>("paint_units");
  _lineChatWidth = this->width();
  _lineChatHeight = this->height();
  auto cfg = ParameterServer::instance()->GetCfgCtrlRoot();
  std::string class_obj_id = "main";
  cfg += {{class_obj_id.c_str(), {
      {"lines", {configuru::Config::array(
        {
          {{"line_color", "#00CD00FF"},    {"line_width", 3}, {"line_colum", 0}, {"title", "GA_1"}, {"unit", "GAPI"}, {"min", 0},{"max", 200} , {"call_back", nullptr}},
          {{"line_color", "#EE4000FF"},    {"line_width", 3}, {"line_colum", 1}, {"title", "GA_2"}, {"unit", "GAPI"}, {"min", 0},{"max", 200} , {"call_back", nullptr}},
          {{"line_color", "#EEEE00FF"},    {"line_width", 3}, {"line_colum", 1}, {"title", "GA_3"}, {"unit", "GAPI"}, {"min", 0},{"max", 200} , {"call_back", nullptr}},
          {{"line_color", "#98F5FFFF"},    {"line_width", 3}, {"line_colum", 2}, {"title", "GA_4"}, {"min", 0}, {"max", 200} , {"call_back", nullptr}},
          {{"line_color", "#A020F0FF"},    {"line_width", 3}, {"line_colum", 2}, {"title", "GA_5"}, {"unit", "GAPI"}, {"min", 0},{"max", 200} , {"call_back", nullptr}},
          {{"line_color", "#7FFF00FF"},    {"line_width", 3}, {"line_colum", 2}, {"title", "GA_6"}, {"unit", "GAPI"}, {"min", 0},{"max", 200} , {"call_back", nullptr}},
          {{"line_color", "#CDCDB4FF"},    {"line_width", 3}, {"line_colum", 3}, {"title", "GA_7"}, {"unit", "GAPI"}, {"min", 0},{"max", 200} , {"call_back", nullptr}},
        })
      }},
      {"size", {
        {"width", _lineChatWidth},
        {"height", _lineChatHeight}
      }}
    }}
  };

  auto createNewLines = [](const configuru::Config &config) -> std::vector<PAINT_LINE_UNIT> {
    if (!config.is_array()) return{};
    auto arry = config.as_array();
    auto res = std::vector<PAINT_LINE_UNIT>();
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
      res.push_back(tmp);
    }
    return res;
  };

  auto cfg_local = cfg[class_obj_id.c_str()];
  cfg_local["lines"].add_callback([this, createNewLines](configuru::Config &, const configuru::Config &b)->bool {
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

  m_lines = createNewLines(cfg_local["lines"]);
  connect(this, SIGNAL(NewQtekLineChatSIG()), this, SLOT(NewQtekLineChat()));
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
}
