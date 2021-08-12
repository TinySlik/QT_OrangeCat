#ifndef DIALOGCALIBRATIONWORKSHEET_H
#define DIALOGCALIBRATIONWORKSHEET_H

#include <QDialog>

namespace Ui {
  class DialogCalibrationWorksheet;
}

class DialogCalibrationWorksheet : public QDialog
{
  Q_OBJECT

public:
  explicit DialogCalibrationWorksheet(QWidget *parent = nullptr);
  ~DialogCalibrationWorksheet();

private:
  Ui::DialogCalibrationWorksheet *ui;
};

#endif // DIALOGCALIBRATIONWORKSHEET_H
