#include "dialogsetupdrawworks.h"
#include "ui_dialogsetupdrawworks.h"
#include "dialogcalibrationworksheet.h"

DialogSetupDrawworks::DialogSetupDrawworks(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::DialogSetupDrawworks)
{
  ui->setupUi(this);
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
