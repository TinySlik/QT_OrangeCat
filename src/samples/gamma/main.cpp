#include "mainwindow.h"
#include "drawImage/DrawImageWidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
//  MainWindow w;
//  w.show();
  DrawImageWidget image;
  image.show();
  return a.exec();
}
