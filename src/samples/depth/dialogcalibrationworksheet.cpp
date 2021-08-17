#include "dialogcalibrationworksheet.h"
#include "ui_dialogcalibrationworksheet.h"
#include <QDoubleValidator>
#include <QIntValidator>

DialogCalibrationWorksheet::DialogCalibrationWorksheet(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::DialogCalibrationWorksheet)
{
  ui->setupUi(this);
  setMaximumSize(this->size());
  setMinimumSize(this->size());

  QDoubleValidator * dbVal =new QDoubleValidator(-1024, 1024, 3);
  QIntValidator* IntValidator = new QIntValidator;
  ui->lineEdit_bp1 ->setValidator(dbVal);
  ui->lineEdit_bp2 ->setValidator(dbVal);
  ui->lineEdit_bp3 ->setValidator(dbVal);
  ui->lineEdit_bp4 ->setValidator(dbVal);
  ui->lineEdit_bp5 ->setValidator(dbVal);
  ui->lineEdit_bp6 ->setValidator(dbVal);
  ui->lineEdit_c1->setValidator(IntValidator);
  ui->lineEdit_c2->setValidator(IntValidator);
  ui->lineEdit_c3->setValidator(IntValidator);
  ui->lineEdit_c4->setValidator(IntValidator);
  ui->lineEdit_c5->setValidator(IntValidator);
  ui->lineEdit_c6->setValidator(IntValidator);
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
