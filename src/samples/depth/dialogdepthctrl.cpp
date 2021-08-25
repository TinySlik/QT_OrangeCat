#include "dialogdepthctrl.h"
#include "ui_dialogdepthctrl.h"
#include "abmdaolib.h"
#include "parameterserver.h"
#include "easylogging++.h"

DialogDepthCtrl::DialogDepthCtrl(QWidget *parent) :
QDialog(parent),
ui(new Ui::DialogDepthCtrl) {
  ui->setupUi(this);
  setMaximumSize(this->size());
  setMinimumSize(this->size());
  auto ctr = ParameterServer::instance()->GetCfgCtrlRoot()["Depth"];

#define NUM_DISPLAY_SPIN_INIT(x, y)  float cur_##y = float(ctr[x]); \
  ui->y->setValue(static_cast<double>(cur_##y));
  NUM_DISPLAY_SPIN_INIT("holeDepth", doubleSpinBox_1)
  NUM_DISPLAY_SPIN_INIT("bitDepth", doubleSpinBox_3)
  NUM_DISPLAY_SPIN_INIT("depthOnJoint", doubleSpinBox_2)
  NUM_DISPLAY_SPIN_INIT("block", doubleSpinBox_7)
  NUM_DISPLAY_SPIN_INIT("riser", doubleSpinBox_9)
  NUM_DISPLAY_SPIN_INIT("compenstr", doubleSpinBox_8)
  NUM_DISPLAY_SPIN_INIT("airRetriever", doubleSpinBox_10)
  NUM_DISPLAY_SPIN_INIT("drilling", doubleSpinBox_17)
  NUM_DISPLAY_SPIN_INIT("tripping", doubleSpinBox_19)
  NUM_DISPLAY_SPIN_INIT("blockSpeedThreshold", doubleSpinBox_14)
  NUM_DISPLAY_SPIN_INIT("rotaryCheckThreshold", doubleSpinBox_18)
  NUM_DISPLAY_SPIN_INIT("wobCheckThreshold", doubleSpinBox_16)
#undef NUM_DISPLAY_SPIN_INIT

#define BOOL_DISPLAY_CKBOX_INIT(x, y)  int cur_##y = int(ctr[x]); \
  ui->y->setChecked(static_cast<bool>(cur_##y));
  BOOL_DISPLAY_CKBOX_INIT("enableBlockDirection", checkBox_3)
  BOOL_DISPLAY_CKBOX_INIT("wobCheckEnable", checkBox_2)
  BOOL_DISPLAY_CKBOX_INIT("rotaryCheckEnable", checkBox_1)
#undef BOOL_DISPLAY_CKBOX_INIT
}

DialogDepthCtrl::~DialogDepthCtrl() {
  delete ui;
}
void DialogDepthCtrl::Accept() {
  auto ctr = ParameterServer::instance()->GetCfgCtrlRoot();
  configuru::Config a = ctr["Depth"];
#define NUM_SPIN_SET(x, y)  a[x] = (ui->y->value());
  NUM_SPIN_SET("holeDepth", doubleSpinBox_1)
  NUM_SPIN_SET("bitDepth", doubleSpinBox_3)
  NUM_SPIN_SET("depthOnJoint", doubleSpinBox_2)
  NUM_SPIN_SET("block", doubleSpinBox_7)
  NUM_SPIN_SET("riser", doubleSpinBox_9)
  NUM_SPIN_SET("compenstr", doubleSpinBox_8)
  NUM_SPIN_SET("airRetriever", doubleSpinBox_10)
  NUM_SPIN_SET("drilling", doubleSpinBox_17)
  NUM_SPIN_SET("tripping", doubleSpinBox_19)
  NUM_SPIN_SET("blockSpeedThreshold", doubleSpinBox_14)
  NUM_SPIN_SET("rotaryCheckThreshold", doubleSpinBox_18)
  NUM_SPIN_SET("wobCheckThreshold", doubleSpinBox_16)
#undef NUM_SPIN_SET
#define BOOL_CKBOX_SET(x, y)  a[x] = int(ui->y->isChecked());
  BOOL_CKBOX_SET("wobCheckEnable", checkBox_2)
  BOOL_CKBOX_SET("rotaryCheckEnable", checkBox_1)
  BOOL_CKBOX_SET("enableBlockDirection", checkBox_3)
#undef BOOL_CKBOX_SET
  LOG(INFO) << __FUNCTION__ << __LINE__ << "Update SQL： " << a;
  auto jsonInterface = ABMDaoLib::getInstance()->getJsonInterface();
  configuru::Config updateval = {
    {"target_table", "u_well_depth_status"},
    {"update_val", a},
    {"index_val", {{"wellId", a["wellId"]}}}
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
