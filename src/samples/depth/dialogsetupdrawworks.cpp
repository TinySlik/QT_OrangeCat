#include "dialogsetupdrawworks.h"
#include "ui_dialogsetupdrawworks.h"
#include "dialogcalibrationworksheet.h"
#include <QDoubleValidator>
#include <QIntValidator>

DialogSetupDrawworks::DialogSetupDrawworks(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::DialogSetupDrawworks)
{
  ui->setupUi(this);
  setMaximumSize(this->size());
  setMinimumSize(this->size());
  QDoubleValidator * dbVal =new QDoubleValidator(-1024, 1024, 3);
  ui->lineEdit_f1 ->setValidator(dbVal);
  ui->lineEdit_f2 ->setValidator(dbVal);
  ui->lineEdit_f3 ->setValidator(dbVal);
  ui->lineEdit_f4 ->setValidator(dbVal);
  ui->lineEdit_f5 ->setValidator(dbVal);
  ui->lineEdit_f6 ->setValidator(dbVal);

  ui->lineEdit_zero_height ->setValidator(dbVal);

  QIntValidator* IntValidator = new QIntValidator;
  ui->lineEdit_c1 -> setValidator(IntValidator);
  ui->lineEdit_c2 -> setValidator(IntValidator);
  ui->lineEdit_c3 -> setValidator(IntValidator);
  ui->lineEdit_c4 -> setValidator(IntValidator);
  ui->lineEdit_c5 -> setValidator(IntValidator);
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
