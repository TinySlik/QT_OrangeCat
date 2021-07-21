#include "qteklinechat.h"
#include "ui_qteklinechat.h"
#include "customplottest.h"

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

    // 默认扫描背景图
//    QImage backgroundImage(":/img/placeImg.png");
//    backgroundImage = backgroundImage.scaled(m_width,m_height,Qt::KeepAspectRatio);
    // 图片头部
    m_pictureHead = new DrawPictureHead();
    m_pictureHead->setItemSize(this->rect().x(),this->rect().y(),this->rect().width(),this->rect().height() / 5);
    m_gs->addItem(m_pictureHead);
//    m_pictureHead->setScanImage(backgroundImage);

//    m_customPlot = new CustomPlotTest(this);
//    m_gs->addWidget(m_customPlot);
//    m_customPlot->move(0, 100);

//    cp->setVisible(false);
}

void QtekLineChat::resizeEvent(QResizeEvent *event) {
  ui->graphicsView->setGeometry(this->rect());
  m_pictureHead->setItemSize(this->rect().x(),this->rect().y(),this->rect().width(),this->rect().height() / 5);
}
