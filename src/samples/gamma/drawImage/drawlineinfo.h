#ifndef DRAWLINEINFO_H
#define DRAWLINEINFO_H

#include <QGraphicsItem>

#include "BaseItem.h"

class DrawLineInfo : public BaseItem
{
public:
  DrawLineInfo();

  void setLineInfo(QPen pen,QString lineName = QObject::tr("empty"),QString lineUnit = QObject::tr("API"),
                   double min = 0,double max = 300);

  QPen linePen() const;
  void setLinePen(const QPen &linePen);

  QString lineName() const;
  void setLineName(const QString &lineName);

  QString lineUnit() const;
  void setLineUnit(const QString &lineUnit);

  double lineMin() const;
  void setLineMin(double lineMin);

  double lineMax() const;
  void setLineMax(double lineMax);

  bool isDrawLine() const;
  void setIsDrawLine(bool isDrawLine);

protected:
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
  QPen m_linePen;//线型
  QString m_lineName;//线名
  QString m_lineUnit;//单位
  double m_lineMin;//最小值
  double m_lineMax;//最大值

  bool m_isDrawLine;//是否画线和范围
};

#endif // DRAWLINEINFO_H
