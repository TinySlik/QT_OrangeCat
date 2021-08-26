/** Copyright 2021 Tiny Oh, Ltd. All rights reserved.
 *
 */

#include "dialogdepthcalibration.h"
#include "ui_dialogdepthcalibration.h"
#include "dialogsetupdrawworks.h"
#include "qdebug.h"
#include "parameterserver.h"
#include "abmdaolib.h"

DialogDepthCalibration::DialogDepthCalibration(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::DialogDepthCalibration) {
  ui->setupUi(this);
  setMaximumSize(this->size());
  setMinimumSize(this->size());
}

DialogDepthCalibration::~DialogDepthCalibration() {
  delete ui;
}

void DialogDepthCalibration::on_pushButton_4_clicked() {
    CreatSetupDrawworksDialog();
}

void DialogDepthCalibration::CreatSetupDrawworksDialog() {
  auto dg = new DialogSetupDrawworks(this);
  dg->show();
}

void DialogDepthCalibration::on_pushButton_clicked() {
    this->accept();
}

void DialogDepthCalibration::on_pushButton_2_clicked() {
    this->reject();
}

void DialogDepthCalibration::on_radioButton_2_toggled(bool checked) {
    this->ui->label->setEnabled(checked);
    this->ui->label_read1_6->setEnabled(checked);
    this->ui->doubleSpinBox_2->setEnabled(checked);
    this->ui->pushButton_4->setEnabled(!checked);
}
