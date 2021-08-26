/** Copyright 2021 Tiny Oh, Ltd. All rights reserved.
 *
 */

#ifndef SRC_SAMPLES_DEPTH_DIALOGACTIVATYSETTINGS_H_
#define SRC_SAMPLES_DEPTH_DIALOGACTIVATYSETTINGS_H_

#include <QDialog>

namespace Ui {
class DialogActivatySettings;
}

class DialogActivatySettings : public QDialog {
  Q_OBJECT

 public:
  explicit DialogActivatySettings(QWidget *parent = nullptr);
  ~DialogActivatySettings();

 private slots:
  void on_pushButton_clicked();

  void on_pushButton_2_clicked();

 private:
  Ui::DialogActivatySettings *ui;
};

#endif  // SRC_SAMPLES_DEPTH_DIALOGACTIVATYSETTINGS_H_
