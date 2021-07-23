#include "qteklinechat.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  QWidget b;
  QtekLineChat chart(&b);
//  chart.show();
  b.show();
  chart.resize(768, 512);
  return a.exec();
}
