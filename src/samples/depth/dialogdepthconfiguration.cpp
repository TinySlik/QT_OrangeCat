#include "dialogdepthconfiguration.h"
#include "ui_dialogdepthconfiguration.h"

DialogDepthConfiguration::DialogDepthConfiguration(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::DialogDepthConfiguration)
{
  ui->setupUi(this);
}

DialogDepthConfiguration::~DialogDepthConfiguration()
{
  delete ui;
}

void DialogDepthConfiguration::on_pushButton_clicked()
{
    this->accept();
}

void DialogDepthConfiguration::on_pushButton_2_clicked()
{
    this->reject();
}
