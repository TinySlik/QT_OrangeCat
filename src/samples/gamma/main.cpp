#include "mainwindow.h"
#include "drawImage/DrawImageWidget.h"
#include "qteklinechat.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  QtekLineChat chart;
  chart.show();
  chart.resize(768, 512);
  return a.exec();
}
