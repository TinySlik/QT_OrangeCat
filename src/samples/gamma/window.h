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

#ifndef OIL_SRC_WINDOW_H_
#define OIL_SRC_WINDOW_H_

#include <QWidget>

QT_BEGIN_NAMESPACE
class QSlider;
class QPushButton;
QT_END_NAMESPACE

class DisplayWidget;
class MainWindow;

class Window : public QWidget {
  Q_OBJECT

 public:
  explicit Window(MainWindow *mw);

 protected:
  void keyPressEvent(QKeyEvent *event) override;

 private slots:
 private:
  QSlider *createSlider();

  DisplayWidget *glWidget;
  QPushButton *dockBtn;
  MainWindow *mainWindow;
};

#endif  // OIL_SRC_WINDOW_H_
