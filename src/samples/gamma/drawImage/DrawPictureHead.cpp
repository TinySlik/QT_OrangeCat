#include "DrawPictureHead.h"
#include <QDebug>
#pragma execution_character_set("utf-8")

DrawPictureHead::DrawPictureHead() : BaseItem()
{
  m_drawLineInfo1 = new DrawLineInfo();
  m_drawLineInfo1->setParentItem(this);
  m_drawLineInfo1->setItemSize(0,0,350,50);
  QPen pen1;
  pen1.setColor(QColor(0, 0, 0,255));
  pen1.setWidth(1);
  m_drawLineInfo1->setLineInfo(pen1,QObject::tr("平均伽玛"),QObject::tr("API"),0,300);

  m_drawLineInfo2 = new DrawLineInfo();
  m_drawLineInfo2->setParentItem(this);
  m_drawLineInfo2->setItemSize(450,0,350,50);
  QPen pen2;
  pen2.setColor(QColor(255, 0, 0,255));
  pen2.setWidth(1);
  m_drawLineInfo2->setLineInfo(pen2,QObject::tr("近钻头上伽玛"),QObject::tr("API"),0,300);

  m_drawLineInfo3 = new DrawLineInfo();
  m_drawLineInfo3->setParentItem(this);
  m_drawLineInfo3->setItemSize(450,50,350,50);
  QPen pen3;
  pen3.setColor(QColor(0, 0, 255,255));
  pen3.setWidth(1);
  m_drawLineInfo3->setLineInfo(pen3,QObject::tr("近钻头下伽玛"),QObject::tr("API"),0,300);

  m_drawLineInfo4 = new DrawLineInfo();
  m_drawLineInfo4->setParentItem(this);
  m_drawLineInfo4->setItemSize(349,0,102,100);
  m_drawLineInfo4->setIsDrawLine(false);
  QPen pen4;
  pen4.setColor(QColor(0, 0, 0,255));
  pen4.setWidth(1);
  m_drawLineInfo4->setLineInfo(pen4,QObject::tr("井深"),QObject::tr("m"),0,300);
}

void DrawPictureHead::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  Q_UNUSED(option)
  Q_UNUSED(widget)


  QPen pen;
  pen.setColor(QColor(0, 0, 0,255));
  pen.setWidth(1);
  painter->setPen(pen);
  // 画线
  painter->drawLine(mItemX,mItemY,mItemX + mItemWidth,mItemY);
  painter->drawLine(mItemX + mItemWidth - 1,mItemY,mItemX + mItemWidth - 1,mItemY + mItemHeight);
  painter->drawLine(mItemX,mItemY + mItemHeight,mItemX + mItemWidth,mItemY + mItemHeight);
  painter->drawLine(mItemX,mItemY,mItemX,mItemY + mItemHeight);

}
