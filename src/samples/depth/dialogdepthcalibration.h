#ifndef DIALOGDEPTHCALIBRATION_H
#define DIALOGDEPTHCALIBRATION_H

#include <QDialog>

namespace Ui {
  class DialogDepthCalibration;
}

class DialogDepthCalibration : public QDialog
{
  Q_OBJECT

public:
  explicit DialogDepthCalibration(QWidget *parent = nullptr);
  ~DialogDepthCalibration();

private slots:
  void on_pushButton_4_clicked();
  void on_pushButton_clicked();
  void on_pushButton_2_clicked();
  void on_radioButton_2_toggled(bool checked);

public Q_SLOTS:
  void CreatSetupDrawworksDialog();

private:
  Ui::DialogDepthCalibration *ui;
};

#endif // DIALOGDEPTHCALIBRATION_H
