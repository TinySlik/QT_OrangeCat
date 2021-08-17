#include "dialogdepthconfiguration.h"
#include "ui_dialogdepthconfiguration.h"
#include <QDragEnterEvent>
#include <QDropEvent>
#include <qmessagebox.h>
#include <qmimedata.h>
#include <QTextEdit>
#include <QDebug>
#include <QDrag>
#include "dialogdepthcardconfigration.h"

DialogDepthConfiguration::DialogDepthConfiguration(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::DialogDepthConfiguration) {
  setAcceptDrops(true);
  setMouseTracking(true);
  ui->setupUi(this);
  setMaximumSize(this->size());
  setMinimumSize(this->size());
  ui->listWidget->setDragEnabled(true);
  ui->listWidget->setMouseTracking(true);
  connect(ui->listWidget,SIGNAL(itemPressed(QListWidgetItem*)),this,SLOT(itemPressed(QListWidgetItem*)));
#define CREATE_DROP_UNIT(x,y,z) m_dropUnits.push_back(\
  {ui->label_##x->geometry().translated(ui->groupBox_##y->pos()), \
   ui->label_##x,\
   ui->radioButton_##z})
  CREATE_DROP_UNIT(2,10,7);
  CREATE_DROP_UNIT(3,10,7);
  CREATE_DROP_UNIT(4,9,10);
  CREATE_DROP_UNIT(5,9,10);
  CREATE_DROP_UNIT(6,8,12);
  CREATE_DROP_UNIT(7,8,12);
  CREATE_DROP_UNIT(8,7,14);
  CREATE_DROP_UNIT(9,7,14);
#undef CREATE_DROP_UNIT
}



DialogDepthConfiguration::~DialogDepthConfiguration() {
  delete ui;
}

void DialogDepthConfiguration::on_pushButton_clicked() {
  this->accept();
}

void DialogDepthConfiguration::on_pushButton_2_clicked() {
  this->reject();
}

void DialogDepthConfiguration::itemPressed(QListWidgetItem *item) {
  QDrag *drag = new QDrag(this);
  QMimeData *data = new QMimeData;
  data->setText(item->text());
  drag->setMimeData(data);
  drag->exec(Qt::MoveAction);
}

void DialogDepthConfiguration::dragEnterEvent(QDragEnterEvent *event) {
  event->acceptProposedAction();
}

void DialogDepthConfiguration::dragMoveEvent(QDragMoveEvent *event) {
  bool in = false;
  for (size_t i = 0; i < m_dropUnits.size(); ++i) {
    if (m_dropUnits[i].label->isEnabled() && m_dropUnits[i].rect.contains(event->pos())) {
      event->acceptProposedAction();
      QPalette label_palette;
      label_palette.setColor(QPalette::Background, QColor("green"));
      m_dropUnits[i].label->setAutoFillBackground(true);
      m_dropUnits[i].label->setPalette(label_palette);
      in = true;
    } else {
      m_dropUnits[i].label->setAutoFillBackground(false);
    }
  }
  if (!in)
    event->ignore();
}

void DialogDepthConfiguration::dragLeaveEvent(QDragLeaveEvent *event) {
//  qDebug() << __FUNCTION__;
}

void DialogDepthConfiguration::dropEvent(QDropEvent *event) {
  for (size_t i = 0; i < m_dropUnits.size(); ++i) {
    if (m_dropUnits[i].label->isEnabled() && m_dropUnits[i].rect.contains(event->pos())) {
      event->acceptProposedAction();
      if (event->mimeData()->hasText()) {
        m_dropUnits[i].label->setText(event->mimeData()->text());
        m_dropUnits[i].label->setAutoFillBackground(false);
      }
      return;
    }
  }
}

void DialogDepthConfiguration::on_pushButton_4_clicked() {
  auto dc = new DialogDepthCardConfigration();
  dc->show();
}
