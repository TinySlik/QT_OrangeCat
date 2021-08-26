/** Copyright 2021 Tiny Oh, Ltd. All rights reserved.
 *
 */

#ifndef SRC_SAMPLES_DEPTH_DIALOGDEPTHCALIBRATION_H_
#define SRC_SAMPLES_DEPTH_DIALOGDEPTHCALIBRATION_H_

#include <QDialog>
#include <QTimer>
#include <string>

namespace Ui {
class DialogDepthCalibration;
}

class DialogDepthCalibration : public QDialog {
Q_OBJECT
 public:
  explicit DialogDepthCalibration(QWidget *parent = nullptr);
  ~DialogDepthCalibration();

private Q_SLOTS:
  void on_pushButton_4_clicked();
  void on_pushButton_clicked();
  void on_pushButton_2_clicked();
  void on_radioButton_2_toggled(bool checked);

public Q_SLOTS:
  void CreatSetupDrawworksDialog();

 private:
  Ui::DialogDepthCalibration *ui;
  std::string m_targetTable;
  QTimer m_timer;
};

#endif  // SRC_SAMPLES_DEPTH_DIALOGDEPTHCALIBRATION_H_
