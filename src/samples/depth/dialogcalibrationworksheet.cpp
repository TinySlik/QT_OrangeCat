#include "dialogcalibrationworksheet.h"
#include "ui_dialogcalibrationworksheet.h"

DialogCalibrationWorksheet::DialogCalibrationWorksheet(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::DialogCalibrationWorksheet)
{
  ui->setupUi(this);
}

DialogCalibrationWorksheet::~DialogCalibrationWorksheet()
{
  delete ui;
}
