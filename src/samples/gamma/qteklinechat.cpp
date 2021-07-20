#include "qteklinechat.h"
#include "ui_qteklinechat.h"
#include "customplottest.h"

QtekLineChat::QtekLineChat(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::QtekLineChat),
  m_beginX(0),
  m_beginY(0),
  m_width(800),
  m_height(850) {
  ui->setupUi(this);
  initGraphicsView();
}

QtekLineChat::~QtekLineChat()
{
  delete ui;
}


void QtekLineChat::initGraphicsView(){
    m_gs = new QGraphicsScene(ui->graphicsView);
    m_gs->setSceneRect(m_beginX,m_beginY,m_width,m_height);

    ui->graphicsView->setScene(m_gs);
    // 禁止滚动条
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setFrameShape(QFrame::Shape::NoFrame);

    // 默认扫描背景图
//    QImage backgroundImage(":/img/placeImg.png");
//    backgroundImage = backgroundImage.scaled(m_width,m_height,Qt::KeepAspectRatio);
    // 图片头部
    m_pictureHead = new DrawPictureHead();
    m_pictureHead->setItemSize(0,0,1006,100);
    m_gs->addItem(m_pictureHead);
//    m_pictureHead->setScanImage(backgroundImage);

    CustomPlotTest *cp = new CustomPlotTest(this);
    m_gs->addWidget(cp);
    cp->move(-4, 100);

//    cp->setVisible(false);
}
