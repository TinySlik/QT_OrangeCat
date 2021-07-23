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
  m_gs->addItem(m_pictureHead);

  this->resize(this->rect().width(), this->rect().height());

  lines = {
    {QColor(155, 155, 155,255), 3, 0, QObject::tr("GA_1"),      QObject::tr("API"),0,200 , nullptr},
    {QColor(255, 0, 0,255),     1, 1, QObject::tr("GA_U_1"),    QObject::tr("API"),0,200 , nullptr},
    {QColor(255, 0, 0,255),     1, 1, QObject::tr("GA_D_1"),    QObject::tr("API"),0,200 , nullptr},
    {QColor(0, 255, 255,255),   2, 2, QObject::tr("GA_O_1"),    QObject::tr("API"),0,200 , nullptr},
    {QColor(255, 0, 255,255),   2, 2, QObject::tr("GA_O_2"),    QObject::tr("API"),0,200 , nullptr},
    {QColor(255, 100, 255,255), 2, 2, QObject::tr("GA_O_3"),    QObject::tr("API"),0,400 , nullptr},
    {QColor(255, 100, 255,255), 2, 3, QObject::tr("GA_O_3"),    QObject::tr("API"),0,400 , nullptr},
  };

  activeLines();
}

void QtekLineChat::addLine(PAINT_LINE_UNIT unit) {
  lines.push_back(unit);
}
void QtekLineChat::clearLine() {
  lines.clear();
}
void QtekLineChat::activeLines() {
  m_pictureHead->refresh(lines);
  m_customPlot->refresh(lines);
}

void QtekLineChat::resizeEvent(QResizeEvent *event) {
  ui->graphicsView->setGeometry(this->rect());
//  m_customPlot->resize(this->width(),this->height());
  m_customPlot->setGeometry(this->rect().x() - PADDING, this->rect().y() + this->rect().height() / 5  - PADDING + 3, this->rect().width() + PADDING  * 2, this->rect().height() * 4 / 5 + PADDING * 2);
  m_pictureHead->setFirstChartWidth(m_customPlot->getFirstChartWidth());
  m_pictureHead->setItemSize(this->rect().x(),this->rect().y(),this->rect().width(),this->rect().height() / 5);
}
