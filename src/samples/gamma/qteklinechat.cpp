#include "qteklinechat.h"
#include "ui_qteklinechat.h"
#include "customplottest.h"
#define PADDING 13

QtekLineChat::QtekLineChat(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::QtekLineChat) {
  ui->setupUi(this);
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
  m_pictureHead->setItemSize(this->rect().x(),this->rect().y(),this->rect().width(),this->rect().height() / 5);
  m_gs->addItem(m_pictureHead);

  this->resize(this->rect().width(), this->rect().height());
}

void QtekLineChat::resizeEvent(QResizeEvent *event) {
  ui->graphicsView->setGeometry(this->rect());
//  m_customPlot->resize(this->width(),this->height());
  m_customPlot->setGeometry(this->rect().x() - PADDING, this->rect().y() + this->rect().height() / 5  - PADDING + 3, this->rect().width() + PADDING  * 2, this->rect().height() * 4 / 5 + PADDING * 2);
  m_pictureHead->setFirstChartWidth(m_customPlot->getFirstChartWidth());
  m_pictureHead->setItemSize(this->rect().x(),this->rect().y(),this->rect().width(),this->rect().height() / 5);
}
