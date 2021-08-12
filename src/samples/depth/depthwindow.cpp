#include "depthwindow.h"
#include "ui_depthwindow.h"
#include "qpalette.h"
#include "qdebug.h"
#include "dialogdepthconfiguration.h"
#include "dialogactivatysettings.h"
#include <QToolBar>

DepthWindow::DepthWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::DepthWindow)
{
  ui->setupUi(this);
  CreateMainMenu();
  InitStatus();
#ifndef QT_NO_SESSIONMANAGER
    QGuiApplication::setFallbackSessionManagementEnabled(false);
#endif
  setUnifiedTitleAndToolBarOnMac(true);
}

void DepthWindow::CreateActivatyDialog() {
  auto dg = new DialogActivatySettings(this);
  dg->show();
}

void DepthWindow::CreateDepthConfigDialog() {
  auto dg = new DialogDepthConfiguration(this);
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
  calibrationAct->setStatusTip(tr("Calibrate the depth system"));
//  connect(copyAct, &QAction::triggered, textEdit, &QPlainTextEdit::copy);
  depthMenu->addAction(calibrationAct);
//  editToolBar->addAction(copyAct);

  QAction *ctrlAct = new QAction(tr("Control"), this);
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
  label_palette.setColor(QPalette::Background, QColor("blue"));
  slip_status->setAutoFillBackground(true);
  slip_status->setPalette(label_palette);

  bottom_status->setAutoFillBackground(true);
  bottom_status->setPalette(label_palette);

  activity_status->setAutoFillBackground(true);
  activity_status->setPalette(label_palette);
}

DepthWindow::~DepthWindow()
{
  delete ui;
}
