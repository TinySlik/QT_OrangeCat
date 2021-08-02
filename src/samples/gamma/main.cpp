#include "qteklinechat.h"
#include <QApplication>
#define CONFIGURU_IMPLEMENTATION 1
#include "parameterserver.h"

#include "easylogging++.h"
#include "type.h"
#include "renderutil.h"
#include "customwidget.h"

INITIALIZE_EASYLOGGINGPP

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  ParameterServer::instance()->CreateNewRoot("base", {
                                                  {"dev_ctrl", {
                                                  }},
                                                  {"dev_status", {
                                                  }}
                                                });
  ParameterServer::instance()->SetCurrentRoot("base");

  CustomWidget bW;
  std::vector<PAINT_LINE_UNIT> lines = {
    {QColor(254, 67, 101,255),    3, 0, QObject::tr("GA_1"),      QObject::tr("GAPI"),0,200 , nullptr},
    {QColor(244, 208, 0,255),     1, 1, QObject::tr("GA_U_1"),    QObject::tr("GAPI"),0,200 , nullptr},
    {QColor(255, 0, 0,255),       1, 1, QObject::tr("GA_D_1"),    QObject::tr("GAPI"),0,200 , nullptr},
    {QColor(220, 87, 18,255),     2, 2, QObject::tr("GA_O_1"),    QObject::tr("GAPI"),0,200 , nullptr},
    {QColor(229, 131, 8,255),     1, 2, QObject::tr("GA_O_2"),    QObject::tr("GAPI"),0,200 , nullptr},
    {QColor(244, 208, 0,255),     1, 2, QObject::tr("GA_O_3"),    QObject::tr("GAPI"),0,400 , nullptr},
    {QColor(20, 68, 106,255),     2, 3, QObject::tr("GA_O_3"),    QObject::tr("GAPI"),0,400 , nullptr},
  };

  bW.NewQtekLineChat(lines);
  bW.show();
  bW.chart->resize(756, 1024);
  return a.exec();
}
