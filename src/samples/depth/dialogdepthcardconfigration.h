/** Copyright 2021 Tiny Oh, Ltd. All rights reserved.
 *
 */

#ifndef SRC_SAMPLES_DEPTH_DIALOGDEPTHCARDCONFIGRATION_H_
#define SRC_SAMPLES_DEPTH_DIALOGDEPTHCARDCONFIGRATION_H_

#include <QDialog>

namespace Ui {
class DialogDepthCardConfigration;
}

class DialogDepthCardConfigration : public QDialog {
  Q_OBJECT

 public:
  explicit DialogDepthCardConfigration(QWidget *parent = nullptr);
  ~DialogDepthCardConfigration();

 private slots:
  void on_pushButton_clicked();
  void on_pushButton_2_clicked();
  void on_checkBox_toggled(bool checked);

 private:
  Ui::DialogDepthCardConfigration *ui;
};

#endif  // SRC_SAMPLES_DEPTH_DIALOGDEPTHCARDCONFIGRATION_H_
