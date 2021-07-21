#include "DrawPictureHead.h"
#include <QDebug>
#include <iostream>
#pragma execution_character_set("utf-8")

DrawPictureHead::DrawPictureHead() : BaseItem()
{
  struct default_config_unit {
    QColor color;
    int    width;
    size_t colum;
    QString name;
    QString unit;
    double min;
    double max;
  };

  struct default_config_unit config[] = {
    {QColor(155, 155, 155,255), 3, 0, QObject::tr("GA_1"),      QObject::tr("API"),0,200 },
    {QColor(255, 0, 0,255),     1, 1, QObject::tr("GA_U_1"),    QObject::tr("API"),0,200 },
    {QColor(255, 0, 0,255),     1, 1, QObject::tr("GA_D_1"),    QObject::tr("API"),0,200 },
    {QColor(0, 255, 255,255),   2, 2, QObject::tr("GA_O_1"),    QObject::tr("API"),0,200 },
    {QColor(255, 0, 255,255),   2, 2, QObject::tr("GA_O_2"),    QObject::tr("API"),0,200 },
    {QColor(255, 100, 255,255), 2, 2, QObject::tr("GA_O_3"),    QObject::tr("API"),0,400 },
  };

  QPen pen;
  for (size_t i = 0; i< sizeof(config) / sizeof (struct default_config_unit) ; ++i) {
    pen.setColor(config[i].color);
    pen.setWidth(config[i].width);
    addLine(config[i].colum, pen, config[i].name, config[i].unit,config[i].min,config[i].max);
  }

  m_drawLineInfoRule = new DrawLineInfo();
  m_drawLineInfoRule->setParentItem(this);
  m_drawLineInfoRule->setIsDrawLine(false);
  pen.setColor(QColor(0, 0, 0,255));
  pen.setWidth(1);
  m_drawLineInfoRule->setLineInfo(pen,QObject::tr("DEPTH"),QObject::tr("m"),0,200);

  refreashSize();
}

void DrawPictureHead::addLine(size_t colum, QPen pen, QString lineName, QString lineUnit,
                              double min, double max) {
  while (colum >= units.size()) {
    units.push_back({});
  }
  auto line = new DrawLineInfo();
  line -> setParentItem(this);
  line -> setLineInfo(pen, lineName, lineUnit, min, max);
  units[colum].push_back(line);
}

void DrawPictureHead::refreashSize() {
  auto columSize = units.size();
  if (mItemWidth < 36 || columSize < 2) {
    return;
  }
  size_t max_row = 0;
  for (size_t i = 0; i < columSize; i++) {
    auto col = units[i];
    if (units[i].size() > max_row) {
      max_row = units[i].size();
    }
  }
  size_t unitWidth = 0;
  size_t unitHeight = 0;
  if (columSize)
      unitWidth = (mItemWidth - 36) / columSize;
  if (max_row)
      unitHeight = mItemHeight / max_row;
  for (size_t i = 0; i < columSize; i++) {
    for (size_t j = 0; j < max_row; j++) {
      if (j >= units[i].size()) {
        // todo
      } else {
          int res_w = unitWidth * i;
          if (i > 0) {
            res_w += 36;
          }
        units[i][j]->setItemSize(res_w, mItemHeight - ((j+1) * unitHeight),  unitWidth + 1, unitHeight);
      }
    }
  }
  m_drawLineInfoRule->setItemSize(unitWidth, 0, 36 + 1 ,mItemHeight);
}

void DrawPictureHead::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  Q_UNUSED(option)
  Q_UNUSED(widget)

  refreashSize();

  QPen pen;
  pen.setColor(QColor(0, 0, 0,255));
  pen.setWidth(2);
  painter->setPen(pen);
  // 画线
  painter->drawLine(mItemX,mItemY + 1,mItemX + mItemWidth,mItemY + 1);
  painter->drawLine(mItemX + mItemWidth - 2,mItemY,mItemX + mItemWidth - 2,mItemY + mItemHeight);
  painter->drawLine(mItemX,mItemY + mItemHeight,mItemX + mItemWidth,mItemY + mItemHeight);
  painter->drawLine(mItemX + 1,mItemY,mItemX + 1,mItemY + mItemHeight);
}
