#include "dialogcalibrationworksheet.h"
#include "ui_dialogcalibrationworksheet.h"

DialogCalibrationWorksheet::DialogCalibrationWorksheet(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::DialogCalibrationWorksheet)
{
  ui->setupUi(this);
  setMaximumSize(this->size());
  setMinimumSize(this->size());
}

DialogCalibrationWorksheet::~DialogCalibrationWorksheet()
{
  delete ui;
}

void DialogCalibrationWorksheet::on_pushButton_clicked()
{
    this->accept();
}

void DialogCalibrationWorksheet::on_pushButton_2_clicked()
{
    this->reject();
}
