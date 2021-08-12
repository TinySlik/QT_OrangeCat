#include "dialogdepthcalibration.h"
#include "ui_dialogdepthcalibration.h"
#include "dialogsetupdrawworks.h"

DialogDepthCalibration::DialogDepthCalibration(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::DialogDepthCalibration)
{
  ui->setupUi(this);
}

DialogDepthCalibration::~DialogDepthCalibration()
{
  delete ui;
}

void DialogDepthCalibration::on_pushButton_4_clicked()
{
    CreatSetupDrawworksDialog();
}

void DialogDepthCalibration::CreatSetupDrawworksDialog() {
  auto dg = new DialogSetupDrawworks(this);
  dg->show();
}
