/** Copyright 2021 Tiny Oh, Ltd. All rights reserved.
 *
 */

#ifndef SRC_SAMPLES_DEPTH_DIALOGSETUPDRAWWORKS_H_
#define SRC_SAMPLES_DEPTH_DIALOGSETUPDRAWWORKS_H_

#include <QDialog>
#include <QTimer>
#include <string>

namespace Ui {
class DialogSetupDrawworks;
}

class DialogSetupDrawworks : public QDialog {
  Q_OBJECT

 public:
  explicit DialogSetupDrawworks(QWidget *parent = nullptr);
  ~DialogSetupDrawworks();

 private slots:
  void on_pushButton_3_clicked();

  void on_pushButton_clicked();

  void on_pushButton_2_clicked();
  void updateFromDao();

 private:
  Ui::DialogSetupDrawworks *ui;
  QTimer m_timer;
  std::string m_targetTable;
};

#endif  // SRC_SAMPLES_DEPTH_DIALOGSETUPDRAWWORKS_H_
