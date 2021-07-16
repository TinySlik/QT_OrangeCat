#include "DrawImageWidget.h"
#include "ui_drawimagewidget.h"

DrawImageWidget::DrawImageWidget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::DrawImageWidget),
  m_beginX(0),
  m_beginY(0),
  m_width(800),
  m_height(850)
{
  ui->setupUi(this);
  //初始化图层
  this->initGraphicsView();
}

DrawImageWidget::~DrawImageWidget()
{
  delete ui;
}


void DrawImageWidget::initGraphicsView(){
    m_gs = new QGraphicsScene(ui->imageView);
    m_gs->setSceneRect(m_beginX,m_beginY,m_width,m_height);

    ui->imageView->setScene(m_gs);
    // 禁止滚动条
    ui->imageView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->imageView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->imageView->setFrameShape(QFrame::Shape::NoFrame);

    // 默认扫描背景图
//    QImage backgroundImage(":/img/placeImg.png");
//    backgroundImage = backgroundImage.scaled(m_width,m_height,Qt::KeepAspectRatio);
    // 图片头部
    m_pictureHead = new DrawPictureHead();
    m_pictureHead->setItemSize(0,0,m_width,100);
    m_gs->addItem(m_pictureHead);
//    m_pictureHead->setScanImage(backgroundImage);
}
