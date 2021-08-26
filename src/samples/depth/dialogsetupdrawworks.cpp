/** Copyright 2021 Tiny Oh, Ltd. All rights reserved.
 *
 */

#include "dialogsetupdrawworks.h"
#include "ui_dialogsetupdrawworks.h"
#include "dialogcalibrationworksheet.h"
#include <QDoubleValidator>
#include <QIntValidator>
#include "parameterserver.h"
#include "abmdaolib.h"
#include <string>

DialogSetupDrawworks::DialogSetupDrawworks(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::DialogSetupDrawworks) {
  ui->setupUi(this);
  setMaximumSize(this->size());
  setMinimumSize(this->size());
  QDoubleValidator * dbVal = new QDoubleValidator(-1024, 1024, 3);
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

  auto ctr = ParameterServer::instance()->GetCfgCtrlRoot();
  auto jsonInterface = ABMDaoLib::getInstance()->getJsonInterface();
  configuru::Config cfg_sql_table_current = {{"target_table", {
      {"name", "u_current_data"},
      {"key", "wellId"}
    }}
  };
  auto js_sql_table = jsonInterface->find(dump_string(cfg_sql_table_current, configuru::JSON).c_str());
  configuru::Config cfg_sql_table = configuru::parse_string(js_sql_table.c_str(), configuru::JSON, "null");

//  LOG(INFO) << "target well: " << cfg_sql_table["value"];
  m_targetTable = static_cast<std::string>(cfg_sql_table["value"]);
  connect(&m_timer, SIGNAL(timeout()), this, SLOT(updateFromDao()));
  m_timer.start(1000);
}

void DialogSetupDrawworks::updateFromDao() {
  auto jsonInterface = ABMDaoLib::getInstance()->getJsonInterface();
  configuru::Config cfg_sql = {{"target_table", {
      {"name", "u_well_depth_status"},
      {"wellId", m_targetTable}
    }}
  };

  auto js = jsonInterface->find(dump_string(cfg_sql, configuru::JSON).c_str());
  configuru::Config cfg = configuru::parse_string(js.c_str(), configuru::JSON, "null");
  ui->label_14->setText(QString::number(static_cast<int>(cfg["count"])));
  ui->label_15->setText(QString::number(static_cast<float>(cfg["blockHeight"])));
}

DialogSetupDrawworks::~DialogSetupDrawworks() {
  delete ui;
}

void DialogSetupDrawworks::on_pushButton_3_clicked() {
  auto dg = new DialogCalibrationWorksheet(this);
  dg->show();
}

void DialogSetupDrawworks::on_pushButton_clicked() {
    this->accept();
}

void DialogSetupDrawworks::on_pushButton_2_clicked() {
    this->reject();
}
