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
#include "glwidget.h"
#include "window.h"
#include "mainwindow.h"
#include "dataprocesswidget.h"
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
  glWidget = new DataProcessWidget(this);

  xSlider = createSlider();
  ySlider = createSlider();
  zSlider = createSlider();

//  connect(xSlider, &QSlider::valueChanged, glWidget, &GLWidget::setXRotation);
//  connect(glWidget, &GLWidget::xRotationChanged, xSlider, &QSlider::setValue);
//  connect(ySlider, &QSlider::valueChanged, glWidget, &GLWidget::setYRotation);
//  connect(glWidget, &GLWidget::yRotationChanged, ySlider, &QSlider::setValue);
//  connect(zSlider, &QSlider::valueChanged, glWidget, &GLWidget::setZRotation);
//  connect(glWidget, &GLWidget::zRotationChanged, zSlider, &QSlider::setValue);

  QVBoxLayout *mainLayout = new QVBoxLayout;
  QHBoxLayout *container = new QHBoxLayout;
  container->addWidget(glWidget);
  container->addWidget(xSlider);
  container->addWidget(ySlider);
  container->addWidget(zSlider);

  QWidget *w = new QWidget;
  w->setLayout(container);
  mainLayout->addWidget(w);
  dockBtn = new QPushButton(tr("Undock"), this);
  connect(dockBtn, &QPushButton::clicked, this, &Window::dockUndock);
  mainLayout->addWidget(dockBtn);

  setLayout(mainLayout);

//  xSlider->setValue(15 * 16);
//  ySlider->setValue(345 * 16);
//  zSlider->setValue(0 * 16);

  std::string class_obj_id = typeid(*glWidget).name();
  class_obj_id += std::to_string(int(glWidget));
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

void Window::dockUndock() {
  if (parent()) {
      setParent(nullptr);
      setAttribute(Qt::WA_DeleteOnClose);
      move(QApplication::desktop()->width() / 2 - width() / 2,
           QApplication::desktop()->height() / 2 - height() / 2);
      dockBtn->setText(tr("Dock"));
      show();
  } else {
    if (!mainWindow->centralWidget()) {
      if (mainWindow->isVisible()) {
        setAttribute(Qt::WA_DeleteOnClose, false);
        dockBtn->setText(tr("Undock"));
        mainWindow->setCentralWidget(this);
      } else {
        QMessageBox::information(nullptr, tr("Cannot dock"), tr("Main window already closed"));
      }
    } else {
      QMessageBox::information(nullptr, tr("Cannot dock"), tr("Main window already occupied"));
    }
  }
}
