#ifndef DRAWPICTUREHEAD_H
#define DRAWPICTUREHEAD_H

#include <QGraphicsItem>

#include  "BaseItem.h"
#include "DrawLineInfo.h"
#include "../type.h"
#include <vector>

class DrawPictureHead : public BaseItem {
 public:
  DrawPictureHead();
  void addLine(size_t colum, QPen pen, QString lineName = QObject::tr("empty"),QString lineUnit = QObject::tr("API"),
               double min = 0,double max = 300);
  void setFirstChartWidth(int width) {firstChartWidth = width;}
  void refresh(std::vector<PAINT_LINE_UNIT> &in);
 protected:
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

 private:
  DrawLineInfo *m_drawLineInfoRule;//井深
  std::vector<std::vector<DrawLineInfo *>> units;
  void refreashSize();
  int firstChartWidth;
  std::vector<PAINT_LINE_UNIT> lines;
};

#endif // DRAWPICTUREHEAD_H
