#include "qteklinechat.h"
#include "ui_qteklinechat.h"
#include "customplottest.h"
#include "parameterserver.h"
#include "easylogging++.h"
#include "renderutil.h"
#define PADDING 14

QtekLineChat::QtekLineChat(std::vector<PAINT_LINE_UNIT> &lines_,QWidget *parent) :
  QWidget(parent),
  ui(new Ui::QtekLineChat) {
  ui->setupUi(this);
  lines = lines_;
  initGraphicsView();
}

QtekLineChat::~QtekLineChat()
{
  delete ui;
}

void QtekLineChat::initGraphicsView(){
  m_gs = new QGraphicsScene(ui->graphicsView);
  m_gs->setSceneRect(this->rect());

  ui->graphicsView->setScene(m_gs);
  // 禁止滚动条
  ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  ui->graphicsView->setFrameShape(QFrame::Shape::NoFrame);
  ui->graphicsView->setFrameStyle(0);
  ui->graphicsView->setAlignment(Qt::AlignLeft | Qt::AlignTop);

  m_customPlot = new CustomPlotTest(this);
  m_gs->addWidget(m_customPlot);

  m_pictureHead = new DrawPictureHead();
  m_pictureHead->setFirstChartWidth(m_customPlot->getFirstChartWidth());
  m_pictureHead->setAxialSpread(50);
  m_gs->addItem(m_pictureHead);

  this->resize(this->rect().width(), this->rect().height());

  activeLines();
  connect(ui->QTekVerticalScrollBar, SIGNAL(valueChanged(int)), m_customPlot, SLOT(scroll(int)));
}

void QtekLineChat::addLine(PAINT_LINE_UNIT unit) {
  lines.push_back(unit);
}
void QtekLineChat::clearLine() {
  lines.clear();
}
void QtekLineChat::activeLines() {
  m_pictureHead->refresh(lines);
//  LOG(INFO) << __FUNCTION__ << __LINE__;
  m_customPlot->refresh(lines);
}

void QtekLineChat::resizeEvent(QResizeEvent *) {
  int bar_width = 20;
  int head_height = 140;
  auto targetRect = QRect(this->rect().x(), this->rect().y(), this->rect().width()- bar_width, this->rect().height());
  auto targetRectBar = QRect(this->rect().width() - bar_width + 1, targetRect.y() + head_height, bar_width - 1, targetRect.height() - head_height);
  ui->graphicsView->setGeometry(this->rect());
  ui->QTekVerticalScrollBar->setGeometry(targetRectBar);
  ui->comboBox ->setGeometry(QRect(this->rect().width() - bar_width + 1, targetRect.y(), bar_width - 1, head_height));
//  m_customPlot->resize(this->width(),this->height());
  m_customPlot->stackUnder(ui->QTekVerticalScrollBar);
  m_customPlot->setGeometry(targetRect.x() - PADDING, targetRect.y() + head_height  - PADDING + 3, targetRect.width() + PADDING * 2 - 3, targetRect.height() - head_height + PADDING * 2);
  m_pictureHead->setFirstChartWidth(m_customPlot->getFirstChartWidth());
  m_pictureHead->setItemSize(targetRect.x(),targetRect.y(),targetRect.width() + 2, head_height);
}
