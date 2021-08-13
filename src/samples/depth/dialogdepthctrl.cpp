#include "dialogdepthctrl.h"
#include "ui_dialogdepthctrl.h"

DialogDepthCtrl::DialogDepthCtrl(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::DialogDepthCtrl)
{
  ui->setupUi(this);
  setMaximumSize(this->size());
  setMinimumSize(this->size());
}

DialogDepthCtrl::~DialogDepthCtrl()
{
  delete ui;
}
