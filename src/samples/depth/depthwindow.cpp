/** Copyright 2021 Tiny Oh, Ltd. All rights reserved.
 *
 */

#include "depthwindow.h"
#include "ui_depthwindow.h"
#include "qpalette.h"
#include "qdebug.h"
#include "dialogdepthconfiguration.h"
#include "dialogactivatysettings.h"
#include "dialogdepthcalibration.h"
#include "parameterserver.h"
#include "dialogdepthctrl.h"
#include "abmdaolib.h"
#include "easylogging++.h"
#include <QSql>
#include <QToolBar>
#include <QTimer>
#include <string>
#include <QDateTime>

DepthWindow::DepthWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::DepthWindow),
  m_DialogActivatySettings(nullptr),
  m_DialogDepthConfiguration(nullptr),
  m_DialogDepthCalibration(nullptr),
  m_DialogDepthCtrl(nullptr) {
  ui->setupUi(this);
  CreateMainMenu();
  InitStatus();
#ifndef QT_NO_SESSIONMANAGER
  QGuiApplication::setFallbackSessionManagementEnabled(false);
#endif
  setUnifiedTitleAndToolBarOnMac(true);
  auto ctr = ParameterServer::instance()->GetCfgCtrlRoot();
  std::string well_name = "well001";
  std::string run_name = "run0100";

  bool res = ABMDaoLib::getInstance()->open(well_name.c_str(), run_name.c_str());
  if (res) LOG(INFO) << "well: " << well_name << "--run: " << run_name << " success";

  auto jsonInterface = ABMDaoLib::getInstance()->getJsonInterface();
  configuru::Config cfg_sql_table_current = {{"target_table", {
      {"name", "u_current_data"},
      {"key", "wellId"}
    }}
  };
  auto js_sql_table = jsonInterface->find(dump_string(cfg_sql_table_current, configuru::JSON).c_str());
  configuru::Config cfg_sql_table = configuru::parse_string(js_sql_table.c_str(), configuru::JSON, "null");

//  LOG(INFO) << "target well: " << cfg_sql_table["value"];
  targetTable = std::string(cfg_sql_table["value"]);
  configuru::Config cfg_sql = {{"target_table", {
      {"name", "u_well_depth_status"},
      {"wellId", cfg_sql_table["value"]}
    }}
  };

  auto js = jsonInterface->find(dump_string(cfg_sql, configuru::JSON).c_str());
  configuru::Config cfg = configuru::parse_string(js.c_str(), configuru::JSON, "null");
  LOG(INFO) << cfg;
  ctr.judge_with_create_key("Depth") = cfg;
  auto stu = ParameterServer:: instance()->GetCfgStatusRoot();
  stu += cfg;

  ctr["Depth"].add_callback([](configuru::Config &, const configuru::Config &b)->bool {
    auto jsonInterface = ABMDaoLib::getInstance()->getJsonInterface();
    configuru::Config updateval = {
      {"target_table", "u_well_depth_status"},
      {"update_val", b},
      {"index_val", {{"wellId", b["wellId"]}}}
    };
    jsonInterface->update(dump_string(updateval, configuru::JSON).c_str());
    return true;
  });

#define STR_DISPLAY_LABEL_REGISTER_WITH_INIT(x, y)  stu[x].add_callback([this](configuru::Config &, const configuru::Config &b)->bool {\
  if (!b.is_string()) return false; \
  auto s = std::string(b); \
  ui->y->setText(s.c_str()); \
  return true; \
});\
  std::string cur##y = static_cast<std::string>(stu[x]);\
  ui->y->setText(cur##y.c_str());

#define NUM_DISPLAY_LABEL_REGISTER_WITH_INIT(x, y)  stu[x].add_callback([this](configuru::Config &, const configuru::Config &b)->bool {\
  if (!b.is_float()) return false;\
  auto s = static_cast<float>(b);\
  ui->y->setText(QString::number(static_cast<double>(s)));\
  return true;\
});\
float cur_##y = static_cast<float>(stu[x]);\
ui->y->setText(QString::number(static_cast<double>(cur_##y)));

  STR_DISPLAY_LABEL_REGISTER_WITH_INIT("T_DActivity", label_internal_status)
  STR_DISPLAY_LABEL_REGISTER_WITH_INIT("bottomStatus", label_bottom_status)
  STR_DISPLAY_LABEL_REGISTER_WITH_INIT("slipSatus", label_slips_status)
  NUM_DISPLAY_LABEL_REGISTER_WITH_INIT("bitDepth", label_5)
  NUM_DISPLAY_LABEL_REGISTER_WITH_INIT("block", label_9)
  NUM_DISPLAY_LABEL_REGISTER_WITH_INIT("compenstr", label_10)
  NUM_DISPLAY_LABEL_REGISTER_WITH_INIT("depthOnJoint", label_7)
  NUM_DISPLAY_LABEL_REGISTER_WITH_INIT("factor", label_13)
  NUM_DISPLAY_LABEL_REGISTER_WITH_INIT("holeDepth", label_4)
  NUM_DISPLAY_LABEL_REGISTER_WITH_INIT("hookLoad", label_12)
  NUM_DISPLAY_LABEL_REGISTER_WITH_INIT("lagDepth", label_6)
  NUM_DISPLAY_LABEL_REGISTER_WITH_INIT("offBottomDist", label_8)
  NUM_DISPLAY_LABEL_REGISTER_WITH_INIT("riser", label_11)
#undef STR_DISPLAY_LABEL_REGISTER_WITH_INIT
#undef NUM_DISPLAY_LABEL_REGISTER_WITH_INIT

  connect(&m_timer, SIGNAL(timeout()), this, SLOT(updateFromDao()));
  m_timer.start(1000);
}

DepthWindow::~DepthWindow() {
  auto ctr = ParameterServer::instance()->GetCfgCtrlRoot();
  ctr.erase("Depth");
  delete ui;
}

void DepthWindow::updateFromDao() {
  auto jsonInterface = ABMDaoLib::getInstance()->getJsonInterface();
  auto jsonRecordInterface = ABMDaoLib::getInstance()->getRunJsonInterface();
  configuru::Config cfg = {{"target_table", {
      {"name", "u_well_depth_status"},
      {"wellId", targetTable.c_str()}
    }}
  };

  auto js = jsonInterface->find(dump_string(cfg, configuru::JSON).c_str());
  auto ctr = ParameterServer::instance()->GetCfgCtrlRoot();
  auto stu = ParameterServer::instance()->GetCfgStatusRoot();

  configuru::Config tmp = configuru::parse_string(js.c_str(), configuru::JSON, "null");
  ctr["Depth"]["holeDepth"] << tmp["blockHeight"];
  auto cur_count = static_cast<int>(tmp["count"]);
  float length = static_cast<float>(tmp["blockHeightZero"]);
  std::string hh = static_cast<std::string>(tmp["calibration"]);
  configuru::Config calibration = configuru::parse_string(hh.c_str(), configuru::JSON, "null");
  auto factor = static_cast<float>(calibration[0]["factor"]);
  int last_count = 0;
  for (size_t i = 0; i < (calibration.as_array().size() - 1); ++i) {
    if (calibration[i + 1].has_key("critical")) {
      auto tmp = static_cast<int>(calibration[i + 1]["critical"]);
      if (cur_count < tmp) {
        length += factor * (cur_count - last_count);
        break;
      } else {
        length += factor * (tmp - last_count);
      }
      last_count = tmp;
    }
    if (calibration[i + 1].has_key("factor")) {
      factor = static_cast<float>(calibration[i + 1]["factor"]);
    }
  }
  auto height = float(tmp["blockHeight"]);
  const float EPSINON = 0.01f;

  if (((height-length) < - EPSINON) || ((height-length) > EPSINON)) {
    LOG(INFO) << calibration;
    configuru::Config a = configuru::Config::object();
    a["blockHeight"] = length;

    LOG(INFO) << "update blockHeight "<< length <<" to SQL";
    configuru::Config updateval = {
      {"target_table", "u_well_depth_status"},
      {"update_val", a},
      {"index_val", {{"wellId", targetTable.c_str()}}}
    };
    jsonInterface->update(dump_string(updateval, configuru::JSON).c_str());
  }

//  QDateTime QDateTime::fromString(const QString& string, const QString& format) [static]
//  time = QDateTime::fromString(dateContent, “yyyy-MM-dd hh:mm:ss”);
  static int count = 0;
  if (count ++ > 3) {
    configuru::Config insertval = {
      {"btmstatus",          tmp["bottomStatus"]},
      {"depth",              height},
      {"t_d_activitystatus", tmp["T_DActivity"]},
      {"time",               std::string(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz").toLatin1().data()).c_str()}
    };

    configuru::Config insertvalrecord = {
      {"target_table", "u_run_depth_record"},
      {"insert_val", insertval}
    };
    jsonRecordInterface->add(dump_string(insertvalrecord, configuru::JSON).c_str());
    count = 0;
  }
  stu << tmp;
}

void DepthWindow::DepthCtrlUpdate() {
  if (m_DialogDepthCtrl)
    m_DialogDepthCtrl->Accept();
}

void DepthWindow::CreateActivatyDialog() {
  if (!m_DialogActivatySettings)
    m_DialogActivatySettings = new DialogActivatySettings(this);
  m_DialogActivatySettings->show();
}

void DepthWindow::CreateDepthConfigDialog() {
  if (!m_DialogDepthConfiguration)
    m_DialogDepthConfiguration = new DialogDepthConfiguration(this);
  m_DialogDepthConfiguration->show();
}

void DepthWindow::CreateDepthCalibrationDialog() {
  if (!m_DialogDepthCalibration)
    m_DialogDepthCalibration = new DialogDepthCalibration(this);
  m_DialogDepthCalibration->show();
}

void DepthWindow::CreateDepthCtrlDialog() {
  if (!m_DialogDepthCtrl) {
    m_DialogDepthCtrl = new DialogDepthCtrl(this);
  }
  m_DialogDepthCtrl->show();
}

void DepthWindow::CreateMainMenu() {
  QMenu *fileMenu = ui->menubar->addMenu(tr("File"));
//  fileMenu->addSeparator();
  QAction *exitAct = fileMenu->addAction(tr("Exit"), this, &QWidget::close);
  exitAct->setShortcuts(QKeySequence::Quit);
  exitAct->setStatusTip(tr("Exit the application"));

  QMenu *depthMenu = ui->menubar->addMenu(tr("Depth"));
//  QToolBar *editToolBar = addToolBar(tr("Edit"));

//  const QIcon configuration = QIcon::fromTheme("configration");
  QAction *configurationAct = new QAction(tr("Configuration..."), this);
  configurationAct->setStatusTip(tr("Config the inputs to the depth system"));
  connect(configurationAct, &QAction::triggered, this, &DepthWindow::CreateDepthConfigDialog);
//  connect(cutAct, &QAction::triggered, textEdit, &QPlainTextEdit::cut);
  depthMenu->addAction(configurationAct);
//  editToolBar->addAction(cutAct);

  QAction *calibrationAct = new QAction(tr("Calibration..."), this);
  connect(calibrationAct, &QAction::triggered, this, &DepthWindow::CreateDepthCalibrationDialog);
  calibrationAct->setStatusTip(tr("Calibrate the depth system"));
//  connect(copyAct, &QAction::triggered, textEdit, &QPlainTextEdit::copy);
  depthMenu->addAction(calibrationAct);
//  editToolBar->addAction(copyAct);

  QAction *ctrlAct = new QAction(tr("Control"), this);
  connect(ctrlAct, &QAction::triggered, this, &DepthWindow::CreateDepthCtrlDialog);
  ctrlAct->setStatusTip(tr("Control the depth system"));
//  connect(pasteAct, &QAction::triggered, textEdit, &QPlainTextEdit::paste);
  depthMenu->addAction(ctrlAct);
//  editToolBar->addAction(pasteAct);
  depthMenu->addSeparator();

  QAction *FOBAct = new QAction(tr("Force On Bottom"), this);
  FOBAct->setStatusTip(tr("Force the bit on bottom"));
  FOBAct->setCheckable(true);
  depthMenu->addAction(FOBAct);

  QAction *LOBAct = new QAction(tr("Lock Off Bottom"), this);
  LOBAct->setCheckable(true);
  LOBAct->setStatusTip(tr("Lock the bit off bottom"));
  depthMenu->addAction(LOBAct);

  QAction *AOBAct = new QAction(tr("Auto On/Off Bottom"), this);
  AOBAct->setCheckable(true);
  AOBAct->setChecked(true);
  AOBAct->setStatusTip(tr("Relase any On/Off bottom locks"));
  depthMenu->addAction(AOBAct);
  depthMenu->addSeparator();

  QAction *LISAct = new QAction(tr("Lock In Slips"), this);
  LISAct->setCheckable(true);
  LISAct->setStatusTip(tr("Lock in slip status"));
  depthMenu->addAction(LISAct);

  QAction *LOSAct = new QAction(tr("Lock Out of Slips"), this);
  LOSAct->setCheckable(true);
  LOSAct->setStatusTip(tr("Lock out slip status"));
  depthMenu->addAction(LOSAct);

  QAction *AISAct = new QAction(tr("Auto In/Out Slips"), this);
  AISAct->setCheckable(true);
  AISAct->setChecked(true);
  AISAct->setStatusTip(tr("Relase any In/Out slip locks"));
  depthMenu->addAction(AISAct);
  ui->menubar->addSeparator();

  QMenu *modeMenu = ui->menubar->addMenu(tr("Mode"));
//  QToolBar *editToolBar = addToolBar(tr("Edit"));

//  const QIcon m1Icon = QIcon::fromTheme("edit-cut");
  QAction *ASAct = new QAction(tr("Activity Settings..."), this);
  connect(ASAct, &QAction::triggered, this, &DepthWindow::CreateActivatyDialog);
  ASAct->setStatusTip(tr("Cut the current selection's contents to the "
                          "clipboard"));
//  connect(cutAct, &QAction::triggered, textEdit, &QPlainTextEdit::cut);
  modeMenu->addAction(ASAct);
  ui->menubar->addSeparator();

  QMenu *helpMenu = ui->menubar->addMenu(tr("Help"));
//  QAction *aboutAct = helpMenu->addAction(tr("&About"), this, &MainWindow::about);
//  aboutAct->setStatusTip(tr("Show the application's About box"));

  QAction *aboutQtAct = helpMenu->addAction(tr("About Depth Monitor"), qApp, &QApplication::aboutQt);
  aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
}

void DepthWindow::InitStatus(const SLIP_STATUS slip, const BOTTOM_STATUS bottom, INTERNAL_STATUS activity) {
  auto slip_status = ui->label_slips_status;
  auto bottom_status = ui->label_bottom_status;
  auto activity_status = ui->label_internal_status;
  QPalette label_palette;
// label_palette.setColor(QPalette::Background, QColor(0, 0, 0));
// label_palette.setColor(QPalette::Background,Qt::black);
  label_palette.setColor(QPalette::Background, QColor("green"));
  slip_status->setAutoFillBackground(true);
  slip_status->setPalette(label_palette);

  bottom_status->setAutoFillBackground(true);
  bottom_status->setPalette(label_palette);

  activity_status->setAutoFillBackground(true);
  activity_status->setPalette(label_palette);
}


