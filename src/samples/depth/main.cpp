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
#include "parameterserver.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QSurfaceFormat>
#include <QCommandLineParser>
#include <QCommandLineOption>

#include "mainwindow.h"
#include <QApplication>
#include <QGuiApplication>
#include "easylogging++.h"
#include "depthwindow.h"

INITIALIZE_EASYLOGGINGPP

int main(int argc, char **argv) {
  ParameterServer::instance()->CreateNewRoot("base", {
                                                  {"dev_ctrl", {
                                                  }},
                                                  {"dev_status", {
                                                  }}
                                                });
  ParameterServer::instance()->SetCurrentRoot("base");

  QCoreApplication::setOrganizationName("QtExamples");
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
  QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);

  QApplication app(argc, argv);
////    app.setWindowIcon(QIcon(QStringLiteral(":AppLogoColor.png")));

  QCoreApplication::setApplicationName("Oil depth demo.");
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

//  MainWindow mainWindow;
  DepthWindow mainWindow;
  mainWindow.setMaximumSize(QSize(442, 414));
  mainWindow.setMinimumSize(QSize(442, 414));

//  mainWindow.resize(mainWindow.sizeHint());
  mainWindow.resize(412,312);
  int desktopArea = QApplication::desktop()->width() *
                    QApplication::desktop()->height();
  int widgetArea = mainWindow.width() * mainWindow.height();
  if (((float)widgetArea / (float)desktopArea) < 0.75f)
      mainWindow.show();
  else
      mainWindow.showMaximized();
  return app.exec();
}
