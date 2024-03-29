/** Copyright 2021 Tiny Oh, Ltd. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#define CONFIGURU_IMPLEMENTATION 1
//#include "browser.h"
//#include "browserwindow.h"
//#include "tabwidget.h"
#include "parameterserver.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QSurfaceFormat>
#include <QCommandLineParser>
#include <QCommandLineOption>

#include "mainwindow.h"
#include <QApplication>
//#include <QWebEngineProfile>
//#include <QWebEngineSettings>

#include <QGuiApplication>
#include "easylogging++.h"
#include <QFile>

INITIALIZE_EASYLOGGINGPP
/**
QUrl commandLineUrlArgument() {
  const QStringList args = QCoreApplication::arguments();
  for (const QString &arg : args.mid(1)) {
      if (!arg.startsWith(QLatin1Char('-')))
          return QUrl::fromUserInput(arg);
  }
  return QUrl(QStringLiteral("http://localhost:8099"));
}
*/
int main(int argc, char **argv) {

  QCoreApplication::setOrganizationName("QtExamples");
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
  QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);

  QApplication app(argc, argv);
////    app.setWindowIcon(QIcon(QStringLiteral(":AppLogoColor.png")));

  //QWebEngineSettings::defaultSettings()->setAttribute(QWebEngineSettings::PluginsEnabled, true);
  //QWebEngineSettings::defaultSettings()->setAttribute(QWebEngineSettings::DnsPrefetchEnabled, true);
//  QWebEngineProfile::defaultProfile()->setUseForGlobalCertificateVerification();

  QCoreApplication::setApplicationName("Oil paint demo.");
  QCoreApplication::setOrganizationName("Citek");
  QCoreApplication::setApplicationVersion(QT_VERSION_STR);
  QCommandLineParser parser;
  parser.setApplicationDescription(QCoreApplication::applicationName());
  parser.addHelpOption();
  parser.addVersionOption();
  QCommandLineOption multipleSampleOption("multisample", "Multisampling");
  parser.addOption(multipleSampleOption);
  QCommandLineOption coreProfileOption("coreprofile", "Use core profile");
  parser.addOption(coreProfileOption);
  QCommandLineOption transparentOption("transparent", "Transparent window");
  parser.addOption(transparentOption);

  parser.process(app);

  QSurfaceFormat fmt;
  fmt.setDepthBufferSize(24);
  if (parser.isSet(multipleSampleOption))
      fmt.setSamples(4);
  if (parser.isSet(coreProfileOption)) {
    fmt.setVersion(3, 2);
    fmt.setProfile(QSurfaceFormat::CoreProfile);
  }
  QSurfaceFormat::setDefaultFormat(fmt);

  MainWindow mainWindow;

//  GLWidget::setTransparent(parser.isSet(transparentOption));
//  if (GLWidget::isTransparent()) {
//    mainWindow.setAttribute(Qt::WA_TranslucentBackground);
//    mainWindow.setAttribute(Qt::WA_NoSystemBackground, false);
//  }
  mainWindow.resize(mainWindow.sizeHint());
  int desktopArea = QApplication::desktop()->width() *
                    QApplication::desktop()->height();
  int widgetArea = mainWindow.width() * mainWindow.height();
  if (((float)widgetArea / (float)desktopArea) < 0.75f)
      mainWindow.show();
  else
      mainWindow.showMaximized();

  auto cfg = ParameterServer::instance()->GetCfgCtrlRoot();
  cfg["hiden"] = false;
  cfg["hiden"].add_callback([&mainWindow](configuru::Config &a, const configuru::Config &b)->bool {
    if (!b.is_bool()) return false;
    bool rk = bool(b);
    bool rk_ = bool(a);
    if (rk == rk_) return false;
    if (rk) {
      mainWindow.hide();
    } else {
      mainWindow.show();
    }
    return true;
  });
//#define TEST_QTWEB
#ifdef TEST_QTWEB
  QUrl url = commandLineUrlArgument();

  Browser browser;
  BrowserWindow *window = browser.createWindow();
  window->show();
  window->tabWidget()->setUrl(url);
#endif
  QFile file_testcase("D:/develop/OIL/res/test/testcase.json");
  if (file_testcase.exists()) {
    auto jsonconfig = configuru::make_json_options();
    jsonconfig.single_line_comments     = true;
    jsonconfig.block_comments           = true;
    jsonconfig.nesting_block_comments   = true;
    auto cfg_ = configuru::parse_file("D:/develop/OIL/res/test/testcase.json", jsonconfig)["test_msg_decoder"];
    if (cfg_.has_key("hiden")) {
      auto kkk = ParameterServer::instance()->GetCfgCtrlRoot();
      kkk["hiden"] << cfg_["hiden"];
    }
  }
  return app.exec();
}
