#define CONFIGURU_IMPLEMENTATION 1
#include "qteklinechat.h"
#include <QApplication>

#include "parameterserver.h"

#include "easylogging++.h"
#include "type.h"
#include "renderutil.h"
#include "customwidget.h"

INITIALIZE_EASYLOGGINGPP

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  CustomWidget bW;
  bW.NewQtekLineChat();
  bW.show();
  bW.resize(512, 756);
  return a.exec();
}
