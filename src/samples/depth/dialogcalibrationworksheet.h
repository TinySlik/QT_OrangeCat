/** Copyright 2021 Tiny Oh, Ltd. All rights reserved.
 *
 */

#ifndef SRC_SAMPLES_DEPTH_DIALOGCALIBRATIONWORKSHEET_H_
#define SRC_SAMPLES_DEPTH_DIALOGCALIBRATIONWORKSHEET_H_

#include <QDialog>
#include <QTimer>
#include <string>

namespace Ui {
class DialogCalibrationWorksheet;
}

class DialogCalibrationWorksheet : public QDialog {
  Q_OBJECT

 public:
  explicit DialogCalibrationWorksheet(QWidget *parent = nullptr);
  ~DialogCalibrationWorksheet();

 private slots:
  void on_pushButton_clicked();
  void on_pushButton_2_clicked();
  void updateFromDao();

  void on_pushButton_4_clicked();
  void on_pushButton_5_clicked();
  void on_pushButton_6_clicked();
  void on_pushButton_7_clicked();
  void on_pushButton_8_clicked();
  void on_pushButton_9_clicked();

  void on_pushButton_3_clicked();

 private:
  Ui::DialogCalibrationWorksheet *ui;
  std::string m_targetTable;
  QTimer m_timer;
};

#endif  // SRC_SAMPLES_DEPTH_DIALOGCALIBRATIONWORKSHEET_H_
