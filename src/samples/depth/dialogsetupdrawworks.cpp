#include "dialogsetupdrawworks.h"
#include "ui_dialogsetupdrawworks.h"
#include "dialogcalibrationworksheet.h"

DialogSetupDrawworks::DialogSetupDrawworks(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::DialogSetupDrawworks)
{
  ui->setupUi(this);
  setMaximumSize(this->size());
  setMinimumSize(this->size());
}

DialogSetupDrawworks::~DialogSetupDrawworks()
{
  delete ui;
}

void DialogSetupDrawworks::on_pushButton_3_clicked()
{
  auto dg = new DialogCalibrationWorksheet(this);
  dg->show();
}

void DialogSetupDrawworks::on_pushButton_clicked()
{
    this->accept();
}

void DialogSetupDrawworks::on_pushButton_2_clicked()
{
    this->reject();
}
