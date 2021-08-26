/** Copyright 2021 Tiny Oh, Ltd. All rights reserved.
 *
 */

#include "dialogcalibrationworksheet.h"
#include "ui_dialogcalibrationworksheet.h"
#include <QDoubleValidator>
#include <QIntValidator>
#include "abmdaolib.h"
#include "parameterserver.h"
#include "easylogging++.h"
#include <string>

DialogCalibrationWorksheet::DialogCalibrationWorksheet(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::DialogCalibrationWorksheet) {
  ui->setupUi(this);
  setMaximumSize(this->size());
  setMinimumSize(this->size());

  QDoubleValidator * dbVal = new QDoubleValidator(-1024, 1024, 3);
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

  auto jsonInterface = ABMDaoLib::getInstance()->getJsonInterface();
  configuru::Config cfg_sql_table_current = {{"target_table", {
      {"name", "u_current_data"},
      {"key", "wellId"}
    }}
  };
  auto js_sql_table = jsonInterface->find(dump_string(cfg_sql_table_current, configuru::JSON).c_str());
  configuru::Config cfg_sql_table = configuru::parse_string(js_sql_table.c_str(), configuru::JSON, "null");

//  LOG(INFO) << "target well: " << cfg_sql_table["value"];
  m_targetTable = std::string(cfg_sql_table["value"]);

  connect(&m_timer, SIGNAL(timeout()), this, SLOT(updateFromDao()));
  m_timer.start(1000);
}

void DialogCalibrationWorksheet::updateFromDao() {
  auto jsonInterface = ABMDaoLib::getInstance()->getJsonInterface();
  configuru::Config cfg_sql = {{"target_table", {
      {"name", "u_well_depth_status"},
      {"wellId", m_targetTable}
    }}
  };

  auto js = jsonInterface->find(dump_string(cfg_sql, configuru::JSON).c_str());
  configuru::Config cfg = configuru::parse_string(js.c_str(), configuru::JSON, "null");

  ui->lineEdit_13->setText(QString::number(static_cast<int>(cfg["count"])));
}

DialogCalibrationWorksheet::~DialogCalibrationWorksheet() {
  delete ui;
}

void DialogCalibrationWorksheet::on_pushButton_clicked() {
  configuru::Config res = configuru::Config::array();
  float bp1 = ui->lineEdit_bp1->text().toFloat();
  float bp2 = ui->lineEdit_bp2->text().toFloat();
  float bp3 = ui->lineEdit_bp3->text().toFloat();
  float bp4 = ui->lineEdit_bp4->text().toFloat();
  float bp5 = ui->lineEdit_bp5->text().toFloat();
  float bp6 = ui->lineEdit_bp6->text().toFloat();
  float bp[6] = {bp1, bp2, bp3, bp4, bp5, bp6};
  int c1 = ui->lineEdit_c1->text().toInt();
  int c2 = ui->lineEdit_c2->text().toInt();
  int c3 = ui->lineEdit_c3->text().toInt();
  int c4 = ui->lineEdit_c4->text().toInt();
  int c5 = ui->lineEdit_c5->text().toInt();
  int c6 = ui->lineEdit_c6->text().toInt();
  int c[6] = {c1, c2, c3, c4, c5, c6};
  int i = 0;
  for (; i < 5; ++i) {
    if (c[i+1] - c[i] == 0) {
      break;
    }
    res.push_back({
      {"factor", (bp[i + 1] - bp[i]) / (c[i+1] - c[i])},
      {"critical", c[i]},
    });
  }
  if (i == 5)
      res.push_back({
        {"critical", c6},
      });

  auto jsonInterface = ABMDaoLib::getInstance()->getJsonInterface();

  configuru::Config a = configuru::Config::object();
  a["calibration"] = dump_string(res, configuru::JSON).c_str();

  LOG(INFO) << "write calib res to SQL:" << a;

  configuru::Config updateval = {
    {"target_table", "u_well_depth_status"},
    {"update_val", a},
    {"index_val", {{"wellId", m_targetTable.c_str()}}}
  };
  jsonInterface->update(dump_string(updateval, configuru::JSON).c_str());

  this->accept();
}

void DialogCalibrationWorksheet::on_pushButton_2_clicked() {
  this->reject();
}

#define PUSHBTN_BIND(x, y) void DialogCalibrationWorksheet::on_##x##_clicked() {\
  ui->y->setText(ui->lineEdit_13->text());\
}

PUSHBTN_BIND(pushButton_4, lineEdit_c1)
PUSHBTN_BIND(pushButton_5, lineEdit_c2)
PUSHBTN_BIND(pushButton_6, lineEdit_c3)
PUSHBTN_BIND(pushButton_7, lineEdit_c4)
PUSHBTN_BIND(pushButton_8, lineEdit_c5)
PUSHBTN_BIND(pushButton_9, lineEdit_c6)

#undef PUSHBTN_BIND

void DialogCalibrationWorksheet::on_pushButton_3_clicked() {
  ui->lineEdit_bp1 ->setText("0.0");
  ui->lineEdit_bp2 ->setText("0.0");
  ui->lineEdit_bp3 ->setText("0.0");
  ui->lineEdit_bp4 ->setText("0.0");
  ui->lineEdit_bp5 ->setText("0.0");
  ui->lineEdit_bp6 ->setText("0.0");
  ui->lineEdit_c1->setText(QString::number(0));
  ui->lineEdit_c2->setText(QString::number(0));
  ui->lineEdit_c3->setText(QString::number(0));
  ui->lineEdit_c4->setText(QString::number(0));
  ui->lineEdit_c5->setText(QString::number(0));
  ui->lineEdit_c6->setText(QString::number(0));
}
