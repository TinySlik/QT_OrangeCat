#include "mainwindow.h"
//#include "drawImage/DrawImageWidget.h"
#include "qteklinechat.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
//  MainWindow w;
//  w.show();
//  DrawImageWidget image;
//  image.show();
  QtekLineChat chart;
  chart.show();
  return a.exec();
}
