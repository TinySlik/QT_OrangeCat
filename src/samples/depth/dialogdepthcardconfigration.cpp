#include "dialogdepthcardconfigration.h"
#include "ui_dialogdepthcardconfigration.h"

DialogDepthCardConfigration::DialogDepthCardConfigration(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::DialogDepthCardConfigration)
{
  ui->setupUi(this);
  this->setMaximumSize(this->size());
  this->setMinimumSize(this->size());
}

DialogDepthCardConfigration::~DialogDepthCardConfigration()
{
  delete ui;
}

void DialogDepthCardConfigration::on_pushButton_clicked()
{
    this->accept();
}

void DialogDepthCardConfigration::on_pushButton_2_clicked()
{
    this->reject();
}

void DialogDepthCardConfigration::on_checkBox_toggled(bool checked)
{
    ui->label_read1_1->setEnabled(checked);
    ui->label_read1_2->setEnabled(checked);
    ui->label_read1_3->setEnabled(checked);
    ui->label_read1_4->setEnabled(checked);
    ui->label_read1_5->setEnabled(checked);
    ui->label_read1_6->setEnabled(checked);
    ui->doubleSpinBox_1->setEnabled(checked);
    ui->doubleSpinBox_2->setEnabled(checked);
    ui->doubleSpinBox_3->setEnabled(checked);
    ui->doubleSpinBox_4->setEnabled(checked);
}
