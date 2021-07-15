/** Copyright 2021 Tini Oh, Ltd. All rights reserved.
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

#include <utility>
#include "window.h"
#include "mainwindow.h"
#include "displaywidget.h"
#include <QSlider>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QPushButton>
#include <QDesktopWidget>
#include <QApplication>
#include <QMessageBox>

Window::Window(MainWindow *mw)
  : mainWindow(mw) {
  glWidget = new DisplayWidget(this);

  QVBoxLayout *mainLayout = new QVBoxLayout;
  QHBoxLayout *container = new QHBoxLayout;
  container->addWidget(glWidget);

  QWidget *w = new QWidget;
  w->setLayout(container);
  mainLayout->addWidget(w);

  setLayout(mainLayout);

  std::string class_obj_id = typeid(*glWidget).name();
  class_obj_id += std::to_string(long(glWidget));
  setWindowTitle(QString(class_obj_id.c_str()));
}

QSlider *Window::createSlider() {
  QSlider *slider = new QSlider(Qt::Vertical);
  slider->setRange(0, 360 * 16);
  slider->setSingleStep(16);
  slider->setPageStep(15 * 16);
  slider->setTickInterval(15 * 16);
  slider->setTickPosition(QSlider::TicksRight);
  return slider;
}

void Window::keyPressEvent(QKeyEvent *e) {
  if (e->key() == Qt::Key_Escape)
      close();
  else
      QWidget::keyPressEvent(e);
}
