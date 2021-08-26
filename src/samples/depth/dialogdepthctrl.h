/** Copyright 2021 Tiny Oh, Ltd. All rights reserved.
 *
 */

#ifndef SRC_SAMPLES_DEPTH_DIALOGDEPTHCTRL_H_
#define SRC_SAMPLES_DEPTH_DIALOGDEPTHCTRL_H_

#include <QDialog>
#include "depthwindow.h"

namespace Ui {
class DialogDepthCtrl;
}

class DialogDepthCtrl : public QDialog {
  Q_OBJECT

 public:
  explicit DialogDepthCtrl(QWidget *parent = nullptr);
  ~DialogDepthCtrl();
  void Accept();

 signals:
  void acceptSig();

 private slots:
  void on_pushButton_2_clicked();
  void on_pushButton_3_clicked();
  void on_doubleSpinBox_1_valueChanged(double arg1);
  void on_doubleSpinBox_3_valueChanged(double arg1);
  void on_doubleSpinBox_2_valueChanged(double arg1);
  void on_doubleSpinBox_7_valueChanged(double arg1);
  void on_doubleSpinBox_9_valueChanged(double arg1);
  void on_doubleSpinBox_8_valueChanged(double arg1);
  void on_doubleSpinBox_10_valueChanged(double arg1);
  void on_doubleSpinBox_17_valueChanged(double arg1);
  void on_doubleSpinBox_19_valueChanged(double arg1);
  void on_doubleSpinBox_14_valueChanged(double arg1);
  void on_doubleSpinBox_18_valueChanged(double arg1);
  void on_doubleSpinBox_16_valueChanged(double arg1);
  void on_checkBox_1_toggled(bool checked);
  void on_checkBox_2_toggled(bool checked);

 private:
  Ui::DialogDepthCtrl *ui;
  friend DepthWindow;
};

#endif  // SRC_SAMPLES_DEPTH_DIALOGDEPTHCTRL_H_
