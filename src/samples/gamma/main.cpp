#include "qteklinechat.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
//  QWidget b;
//  QtekLineChat chart(&b);
////  chart.show();
//  b.show();
  QtekLineChat chart;
  chart.show();
  chart.resize(756, 1024);
  return a.exec();
}
