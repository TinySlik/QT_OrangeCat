#include "DrawPictureHead.h"
#include <QDebug>
#include <iostream>
#pragma execution_character_set("utf-8")
#include "../type.h"
#include "easylogging++.h"

DrawPictureHead::DrawPictureHead() : BaseItem(), firstChartWidth(0), axialSpread(36)
{
  QPen pen;
  units.push_back({});
  units.push_back({});

  m_drawLineInfoRule = new DrawLineInfo();
  m_drawLineInfoRule->setParentItem(this);
  m_drawLineInfoRule->setIsDrawLine(false);
  pen.setColor(QColor(0, 0, 0,255));
  pen.setWidth(1);
  m_drawLineInfoRule->setAxialLineInfo(pen,QObject::tr("TIME"),QObject::tr("min"),1,1);

  refreashSize();
}

void DrawPictureHead::refresh(std::vector<PAINT_LINE_UNIT> &in) {
  for (size_t i = 0;i < units.size() ; ++i) {
    for (size_t j = 0;j < units[i].size() ; ++j) {
      units[i][j]->setParentItem(nullptr);
      delete units[i][j];
    }
  }
  units.clear();
  lines.clear();
  lines = in;
  QPen pen;
  for (size_t i = 0; i< lines.size() ; ++i) {
    pen.setColor(lines[i].color);
    pen.setWidth(lines[i].width);
    addLine(lines[i].colum, pen, lines[i].name, lines[i].unit,lines[i].min,lines[i].max);
  }
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
  if (mItemWidth < axialSpread || columSize < 2) {
    return;
  }
  size_t max_row = 0;
  for (size_t i = 0; i < columSize; i++) {
    auto col = units[i];
    if (units[i].size() > max_row) {
      max_row = units[i].size();
    }
  }
  size_t unitHeight = 0;
  if (max_row)
      unitHeight = mItemHeight / max_row;
  for (size_t i = 0; i < columSize; i++) {
    for (size_t j = 0; j < max_row; j++) {
      if (j >= units[i].size()) {
        // todo
      } else {
        if (i == 0) {
          units[i][j]->setItemSize(0, mItemHeight - ((j+1) * unitHeight),  firstChartWidth + 1, unitHeight);
        } else {
          int resetUnitWidth = ( mItemWidth - (firstChartWidth) - axialSpread) / (columSize - 1);
          units[i][j]->setItemSize(firstChartWidth + (i-1) * resetUnitWidth + axialSpread, mItemHeight - ((j+1) * unitHeight),  resetUnitWidth + 1, unitHeight);
        }
      }
    }
  }
  m_drawLineInfoRule->setItemSize(firstChartWidth, 0, axialSpread + 1, mItemHeight);
}

void DrawPictureHead::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  Q_UNUSED(option)
  Q_UNUSED(widget)

  refreashSize();

  QPen pen;
  pen.setColor(QColor(0, 0, 0,255));
  pen.setWidth(4);
  painter->setPen(pen);
  // 画线
  painter->drawLine(mItemX,mItemY + 1,mItemX + mItemWidth,mItemY + 1);
  painter->drawLine(mItemX + mItemWidth - 2,mItemY,mItemX + mItemWidth - 2,mItemY + mItemHeight);
  painter->drawLine(mItemX,mItemY + mItemHeight,mItemX + mItemWidth,mItemY + mItemHeight);
  painter->drawLine(mItemX + 1,mItemY,mItemX + 1,mItemY + mItemHeight);

  auto columSize = units.size();
  int resetUnitWidth = ( mItemWidth - (firstChartWidth) - axialSpread) / (columSize - 1);
  for (size_t i = 0; i < columSize; i++) {
    painter->drawLine(firstChartWidth + (i-1) * resetUnitWidth + axialSpread + 1, mItemY,firstChartWidth + (i-1) * resetUnitWidth + axialSpread + 1,mItemY + mItemHeight);
  }
  static int a = 0;
  a++;
}
