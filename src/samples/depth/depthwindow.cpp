#include "depthwindow.h"
#include "ui_depthwindow.h"
#include "qpalette.h"
#include "qdebug.h"
#include "dialogdepthconfiguration.h"
#include "dialogactivatysettings.h"
#include "dialogdepthcalibration.h"
#include "dialogdepthctrl.h"
#include "abmdaolib.h"
#include "parameterserver.h"
#include "easylogging++.h"
#include <QSql>
#include <QToolBar>
#include <QTimer>
#include "parameterserver.h"

DepthWindow::DepthWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::DepthWindow) {
  // todo
  ui->setupUi(this);
  CreateMainMenu();
  InitStatus();
#ifndef QT_NO_SESSIONMANAGER
  QGuiApplication::setFallbackSessionManagementEnabled(false);
#endif
  setUnifiedTitleAndToolBarOnMac(true);
  auto ctr = ParameterServer::instance()->GetCfgCtrlRoot();
  configuru::Config cfg = {
    {"T_DActivaty",          ui->label_internal_status->text().toLatin1().data()},
    {"bitDepth",             ui->label_5->text().toFloat()},
    {"block",                ui->label_9->text().toFloat()},
    {"blockHeight",          0.0f},
    {"blockHeightZero",      0.0f},
    {"blockSpeedThreshold",  0.0f},
    {"bottomStatus",         ui->label_bottom_status->text().toLatin1().data()},
    {"calibration",          "empty"},
    {"compenstr",            ui->label_10->text().toFloat()},
    {"depthOnJoint",         ui->label_7->text().toFloat()},
    {"depthSensorCount",     0},
    {"drilling",             2.0f},
    {"factor",               ui->label_13->text().toFloat()},
    {"holeDepth",            ui->label_4->text().toFloat()},
    {"hookLoad",             ui->label_12->text().toFloat()},
    {"id",                   1},
    {"ignoreIn_OutSlipTag",  0},
    {"lagDepth",             ui->label_6->text().toFloat()},
    {"offBottomDist",        ui->label_8->text().toFloat()},
    {"riser",                ui->label_11->text().toFloat()},
    {"rop",                  0.0f},
    {"rotaryCheckEnable",    0},
    {"rotaryCheckThreshold", 0.0f},
    {"slipSatus",            ui->label_slips_status->text().toLatin1().data()},
    {"tripping",             0.0f},
    {"wellId",               "001"},
    {"wobCheckEnable",       0},
    {"wobCheckThreshold",    0.0f}
  };

  ctr.judge_with_create_key("Depth") = cfg;
  auto stu = ParameterServer::instance()->GetCfgStatusRoot();
  stu += cfg;

#define STR_LABEL_REGISTER(x, y)  stu[x].add_callback([this](configuru::Config &, const configuru::Config &b)->bool {\
  if (!b.is_string()) return false; \
  auto s = std::string(b); \
  ui->y->setText(s.c_str()); \
  return true; \
});

#define NUM_LABEL_REGISTER(x, y)  stu[x].add_callback([this](configuru::Config &, const configuru::Config &b)->bool { \
  if (!b.is_float()) return false; \
  auto s = float(b); \
  ui->y->setText(QString::number(static_cast<double>(s))); \
  return true; \
});
  STR_LABEL_REGISTER("T_DActivaty", label_internal_status)
  STR_LABEL_REGISTER("bottomStatus", label_bottom_status)
  STR_LABEL_REGISTER("slipSatus", label_slips_status)
  NUM_LABEL_REGISTER("bitDepth", label_5)
  NUM_LABEL_REGISTER("block", label_9)
  NUM_LABEL_REGISTER("compenstr", label_10)
  NUM_LABEL_REGISTER("depthOnJoint", label_7)
  NUM_LABEL_REGISTER("factor", label_13)
  NUM_LABEL_REGISTER("holeDepth", label_4)
  NUM_LABEL_REGISTER("hookLoad", label_12)
  NUM_LABEL_REGISTER("lagDepth", label_6)
  NUM_LABEL_REGISTER("offBottomDist", label_8)
  NUM_LABEL_REGISTER("riser", label_11)
#undef STR_LABEL_REGISTER
#undef NUM_LABEL_REGISTER
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
  configuru::Config cfg = {{"target_table", {
      {"name", "u_well_depth_status"},
      {"wellId", "001"}
    }}
  };
  auto js = jsonInterface->find(dump_string(cfg, configuru::JSON).c_str());
  auto ctr = ParameterServer::instance()->GetCfgCtrlRoot();
  auto stu = ParameterServer::instance()->GetCfgStatusRoot();
  stu << configuru::parse_string(js.c_str(), configuru::JSON, "null");
}

void DepthWindow::CreateActivatyDialog() {
  auto dg = new DialogActivatySettings(this);
  dg->show();
}

void DepthWindow::CreateDepthConfigDialog() {
  auto dg = new DialogDepthConfiguration(this);
  dg->show();
}

void DepthWindow::CreateDepthCalibrationDialog() {
  auto dg = new DialogDepthCalibration(this);
  dg->show();
}

void DepthWindow::CreateDepthCtrlDialog() {
  auto dg = new DialogDepthCtrl(this);
  dg->show();
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
  depthMenu->addAction(FOBAct);

  QAction *LOBAct = new QAction(tr("Lock Off Bottom"), this);
  LOBAct->setStatusTip(tr("Lock the bit off bottom"));
  depthMenu->addAction(LOBAct);

  QAction *AOBAct = new QAction(tr("Auto On/Off Bottom"), this);
  AOBAct->setStatusTip(tr("Relase any On/Off bottom locks"));
  depthMenu->addAction(AOBAct);

  depthMenu->addSeparator();

  QAction *LISAct = new QAction(tr("Lock In Slips"), this);
  LISAct->setCheckable(true);
  LISAct->setChecked(true);
  LISAct->setStatusTip(tr("Lock in slip status"));
  depthMenu->addAction(LISAct);

  QAction *LOSAct = new QAction(tr("Lock Out of Slips"), this);
  LOSAct->setStatusTip(tr("Lock out slip status"));
  depthMenu->addAction(LOSAct);

  QAction *AISAct = new QAction(tr("Auto In/Out Slips"), this);
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
  //label_palette.setColor(QPalette::Background, QColor(0, 0, 0));
  //label_palette.setColor(QPalette::Background,Qt::black);
  label_palette.setColor(QPalette::Background, QColor("green"));
  slip_status->setAutoFillBackground(true);
  slip_status->setPalette(label_palette);

  bottom_status->setAutoFillBackground(true);
  bottom_status->setPalette(label_palette);

  activity_status->setAutoFillBackground(true);
  activity_status->setPalette(label_palette);
}


