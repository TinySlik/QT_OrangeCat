#include "dialogactivatysettings.h"
#include "ui_dialogactivatysettings.h"

DialogActivatySettings::DialogActivatySettings(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::DialogActivatySettings)
{
  ui->setupUi(this);
}

DialogActivatySettings::~DialogActivatySettings()
{
  delete ui;
}

void DialogActivatySettings::on_pushButton_clicked()
{
    this->accept();
}

void DialogActivatySettings::on_pushButton_2_clicked()
{
    this->reject();
}
