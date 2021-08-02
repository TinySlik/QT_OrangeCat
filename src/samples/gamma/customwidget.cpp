#include "customwidget.h"
#include "parameterserver.h"
#include "renderutil.h"

#include <QMetaType>

CustomWidget::CustomWidget(QWidget *parent) : QWidget(parent)
{
  qRegisterMetaType<std::shared_ptr<std::vector<PAINT_LINE_UNIT>>>("paint_units");
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
      }}
    }}
  };

  auto cfg_local = cfg[class_obj_id.c_str()];
  cfg_local["lines"].add_callback([this](configuru::Config &, const configuru::Config &b)->bool {
//    Q_DECLARE_METATYPE(std::shared_ptr<std::vector<PAINT_LINE_UNIT>>);
    qRegisterMetaType<std::shared_ptr<std::vector<PAINT_LINE_UNIT>>>("paint_units");
    if (!b.is_array()) return false;
    auto arry = ((configuru::Config) b).as_array();
    m_lines.clear();
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
      m_lines.push_back(tmp);
    }
//    auto kk = bW.childAt(0,0);
//    kk->deleteLater();

//    auto chart_n = new QtekLineChat(lines, nullptr);
//    chart_n->show();
    emit NewQtekLineChatSIG();
    return true;
  });
  connect(this, SIGNAL(NewQtekLineChatSIG()), this, SLOT(NewQtekLineChat()));

}

void CustomWidget::NewQtekLineChat(std::vector<PAINT_LINE_UNIT> lines) {
  chart = new QtekLineChat(lines, this);
  chart->show();
}

void CustomWidget::NewQtekLineChat() {
  chart->deleteLater();
  chart = new QtekLineChat(m_lines, this);
  chart->show();
  chart->resize(this->width(), this->height());
}
