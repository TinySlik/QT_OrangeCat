/** Copyright 2021 Tiny Oh, Ltd. All rights reserved.
 *
 */

#include "dialogdepthctrl.h"
#include "ui_dialogdepthctrl.h"
#include "abmdaolib.h"
#include "parameterserver.h"
#include "easylogging++.h"

DialogDepthCtrl::DialogDepthCtrl(QWidget *parent) :
QDialog(parent),
ui(new Ui::DialogDepthCtrl) {
  LOG(INFO) << __FUNCTION__;
  ui->setupUi(this);
  setMaximumSize(this->size());
  setMinimumSize(this->size());
  auto ctr = ParameterServer::instance()->GetCfgCtrlRoot()["Depth"];

#define NUM_DISPLAY_SPIN_INIT(x, y)  float cur_##y = static_cast<float>(ctr[x]);\
  ui->y->setValue(static_cast<double>(cur_##y));
  NUM_DISPLAY_SPIN_INIT("hole_depth", doubleSpinBox_1)
  NUM_DISPLAY_SPIN_INIT("bit_depth", doubleSpinBox_3)
  NUM_DISPLAY_SPIN_INIT("depth_on_joint", doubleSpinBox_2)
  NUM_DISPLAY_SPIN_INIT("block", doubleSpinBox_7)
  NUM_DISPLAY_SPIN_INIT("riser", doubleSpinBox_9)
  NUM_DISPLAY_SPIN_INIT("compenstr", doubleSpinBox_8)
  NUM_DISPLAY_SPIN_INIT("air_retriever", doubleSpinBox_10)
  NUM_DISPLAY_SPIN_INIT("drilling", doubleSpinBox_17)
  NUM_DISPLAY_SPIN_INIT("tripping", doubleSpinBox_19)
  NUM_DISPLAY_SPIN_INIT("block_speed_threshold", doubleSpinBox_14)
  NUM_DISPLAY_SPIN_INIT("rotary_check_threshold", doubleSpinBox_18)
  NUM_DISPLAY_SPIN_INIT("wob_check_threshold", doubleSpinBox_16)
#undef NUM_DISPLAY_SPIN_INIT

#define BOOL_DISPLAY_CKBOX_INIT(x, y)  int cur_##y = static_cast<int>(ctr[x]); \
  ui->y->setChecked(static_cast<bool>(cur_##y));
  BOOL_DISPLAY_CKBOX_INIT("enable_block_direction", checkBox_3)
  BOOL_DISPLAY_CKBOX_INIT("wob_check_enable", checkBox_2)
  BOOL_DISPLAY_CKBOX_INIT("rotary_check_enable", checkBox_1)
#undef BOOL_DISPLAY_CKBOX_INIT
  ui->doubleSpinBox_18->setEnabled(ui->checkBox_2->isChecked());
  ui->doubleSpinBox_16->setEnabled(ui->checkBox_1->isChecked());
}

DialogDepthCtrl::~DialogDepthCtrl() {
  delete ui;
}

void DialogDepthCtrl::Accept() {
  auto ctr = ParameterServer::instance()->GetCfgCtrlRoot();
  configuru::Config a = ctr["Depth"];
#define BOOL_CKBOX_SET(x, y)  a[x] = static_cast<int>(ui->y->isChecked());
  BOOL_CKBOX_SET("wob_check_enable", checkBox_2)
  BOOL_CKBOX_SET("rotary_check_enable", checkBox_1)
  BOOL_CKBOX_SET("enable_block_direction", checkBox_3)
#undef BOOL_CKBOX_SET
#define NUM_SPIN_SET(x, y, z)  a[x] = (ui->y->value());\
  ui->z->setPixmap(QPixmap(":/svg/right.svg"));
  NUM_SPIN_SET("hole_depth", doubleSpinBox_1, label_1)
  NUM_SPIN_SET("bit_depth", doubleSpinBox_3, label_8)
  NUM_SPIN_SET("depth_on_joint", doubleSpinBox_2, label_2)
  NUM_SPIN_SET("block", doubleSpinBox_7, label_3)
  NUM_SPIN_SET("riser", doubleSpinBox_9, label_4)
  NUM_SPIN_SET("compenstr", doubleSpinBox_8, label_5)
  NUM_SPIN_SET("air_retriever", doubleSpinBox_10, label_6)
  NUM_SPIN_SET("drilling", doubleSpinBox_17, label_12)
  NUM_SPIN_SET("tripping", doubleSpinBox_19, label_13)
  NUM_SPIN_SET("block_speed_threshold", doubleSpinBox_14, label_14)
  NUM_SPIN_SET("rotary_check_threshold", doubleSpinBox_18, label_7)
  NUM_SPIN_SET("wob_check_threshold", doubleSpinBox_16, label_9)
#undef NUM_SPIN_SET

  LOG(INFO) << __FUNCTION__ << __LINE__ << "Update SQL： " << a;
  auto jsonInterface = ABMDaoLib::getInstance()->getJsonInterface();
  configuru::Config updateval = {
    {"target_table", "u_well_depth_status"},
    {"update_val", a},
    {"index_val", {{"well_id", a["well_id"]}}}
  };
  jsonInterface->update(dump_string(updateval, configuru::JSON).c_str());
}

void DialogDepthCtrl::on_pushButton_2_clicked() {
  Accept();
  this->hide();
}

void DialogDepthCtrl::on_pushButton_3_clicked() {
  this->hide();
}

#define CHECK_IF_SPIN_EQUL_SQL(x, y, z)  void DialogDepthCtrl::on_##y##_valueChanged(double arg1) {\
  auto ctr = ParameterServer::instance()->GetCfgCtrlRoot()["Depth"];\
  if (ctr[x] != arg1)\
    ui->z->setPixmap(QPixmap(":/svg/wrong.svg"));\
  else\
    ui->z->setPixmap(QPixmap(":/svg/right.svg"));\
}

CHECK_IF_SPIN_EQUL_SQL("hole_depth", doubleSpinBox_1, label_1)
CHECK_IF_SPIN_EQUL_SQL("bit_depth", doubleSpinBox_3, label_8)
CHECK_IF_SPIN_EQUL_SQL("depth_on_joint", doubleSpinBox_2, label_2)
CHECK_IF_SPIN_EQUL_SQL("block", doubleSpinBox_7, label_3)
CHECK_IF_SPIN_EQUL_SQL("riser", doubleSpinBox_9, label_4)
CHECK_IF_SPIN_EQUL_SQL("compenstr", doubleSpinBox_8, label_5)
CHECK_IF_SPIN_EQUL_SQL("air_retriever", doubleSpinBox_10, label_6)
CHECK_IF_SPIN_EQUL_SQL("drilling", doubleSpinBox_17, label_12)
CHECK_IF_SPIN_EQUL_SQL("tripping", doubleSpinBox_19, label_13)
CHECK_IF_SPIN_EQUL_SQL("block_speed_threshold", doubleSpinBox_14, label_14)
CHECK_IF_SPIN_EQUL_SQL("rotary_check_threshold", doubleSpinBox_18, label_7)
CHECK_IF_SPIN_EQUL_SQL("wob_check_threshold", doubleSpinBox_16, label_9)

#undef CHECK_IF_SPIN_EQUL_SQL

void DialogDepthCtrl::on_checkBox_1_toggled(bool checked) {
  ui->doubleSpinBox_18->setEnabled(checked);
}


void DialogDepthCtrl::on_checkBox_2_toggled(bool checked) {
  ui->doubleSpinBox_16->setEnabled(checked);
}
