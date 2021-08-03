#include "DrawLineInfo.h"
#include <QDebug>
#pragma execution_character_set("utf-8")

DrawLineInfo::DrawLineInfo() : BaseItem(), m_isAxial(false)
{
  m_linePen.setColor(QColor(0, 0, 0,255));
  m_linePen.setWidth(1);
  m_lineName = QObject::tr("empty");
  m_lineUnit = QObject::tr("API");
  m_lineMin = 0;
  m_lineMax = 300;
  m_isDrawLine = true;
}

void DrawLineInfo::setLineInfo(QPen pen, QString lineName, QString lineUnit, double min, double max)
{
  m_linePen = pen;
  m_lineName = lineName;
  m_lineUnit = lineUnit;
  m_lineMin = min;
  m_lineMax = max;
}

void DrawLineInfo::setAxialLineInfo(QPen pen, QString lineName, QString lineUnit, double min, double max) {
  m_linePen = pen;
  m_lineName = lineName;
  m_lineUnit = lineUnit;
  m_lineMin = min;
  m_lineMax = max;
  m_isAxial = true;
}

void DrawLineInfo::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  Q_UNUSED(option)
  Q_UNUSED(widget)
//  painter->save();

  QPen pen;
  pen.setColor(QColor(0, 0, 0,255));
  pen.setWidthF(3.0);

  if ( m_lineName == "empty") {
    painter->setPen(pen);
    painter->drawLine(mItemX + mItemWidth - 1,mItemY,mItemX + mItemWidth - 1,mItemY + mItemHeight);
    painter->drawLine(mItemX,mItemY,mItemX,mItemY + mItemHeight);
    return;
  }

  QFont fontRange;
  fontRange.setPointSize(7);
  fontRange.setFamily("Arial");

  QFont fontName;
  fontName.setPointSize(9);
  fontName.setFamily("Arial");

  if(m_isDrawLine){
  //画左右范围
    painter->setPen(m_linePen);
    painter->setFont(fontRange);
    painter->drawText(mItemX + 5,mItemY + 15, QString::number(m_lineMin));
    painter->drawText(mItemX + mItemWidth - 20, mItemY + 15, QString::number(m_lineMax));

    //画线
    painter->setPen(m_linePen);
    painter->drawLine(mItemX, mItemY + mItemHeight * 0.55, mItemX + mItemWidth - 1, mItemY + mItemHeight * 0.55);
//    painter->drawLine(mItemX + 10, mItemY + mItemHeight * 0.55 - 3, mItemX + 10, mItemY + mItemHeight * 0.55 + 3);
//    painter->drawLine(mItemX + mItemWidth - 1 - 10, mItemY + mItemHeight * 0.55 - 3, mItemX + mItemWidth - 1 - 10, mItemY + mItemHeight * 0.55 + 3);
  }

  //画单位和线名
  painter->setPen(m_linePen);
  painter->setFont(fontName);
  int nameWidth = mItemX + mItemWidth/2 - m_lineName.size() * 4.2;
  painter->drawText(nameWidth,mItemY + mItemHeight/2 - 1,m_lineName);

  int unitWidth = mItemX + mItemWidth/2 - (m_lineUnit.size() + 1) * 4.2;

  if (m_isAxial) {
    QFont font;
    font.setPointSize(8);
    font.setFamily("Arial");
    painter->setFont(font);
    unitWidth = mItemX + mItemWidth/2 - (m_lineUnit.size() + 1) * 2.0;
    painter->drawText(unitWidth,mItemY + mItemHeight/2 + 25, QString("%1").arg(m_lineUnit));
    auto bilichi = QString::number(m_lineMin) + ":" + QString::number(m_lineMax);
    auto bilichiunitWidth = mItemX + mItemWidth/2 - (bilichi.size() + 1) * 2.0;
    painter->drawText(bilichiunitWidth,mItemY + mItemHeight/2 + 45, bilichi);
  }
  else {
    QFont font;
    font.setPointSize(8);
    font.setFamily("Arial");
    painter->setFont(font);
    painter->drawText(unitWidth * 1.01,mItemY + mItemHeight/2 + 15,QString("(%1)").arg(m_lineUnit));
  }

  //画左右边框
  painter->setPen(pen);
  painter->drawLine(mItemX + mItemWidth - 1,mItemY,mItemX + mItemWidth - 1, mItemY + mItemHeight);
  painter->drawLine(mItemX, mItemY, mItemX, mItemY + mItemHeight);
  painter->endNativePainting();

//  painter->end();
}


QPen DrawLineInfo::linePen() const
{
  return m_linePen;
}

void DrawLineInfo::setLinePen(const QPen &linePen)
{
  m_linePen = linePen;
}

QString DrawLineInfo::lineName() const
{
  return m_lineName;
}

void DrawLineInfo::setLineName(const QString &lineName)
{
  m_lineName = lineName;
}

QString DrawLineInfo::lineUnit() const
{
  return m_lineUnit;
}

void DrawLineInfo::setLineUnit(const QString &lineUnit)
{
  m_lineUnit = lineUnit;
}

double DrawLineInfo::lineMin() const
{
  return m_lineMin;
}

void DrawLineInfo::setLineMin(double lineMin)
{
  m_lineMin = lineMin;
}

double DrawLineInfo::lineMax() const
{
  return m_lineMax;
}

void DrawLineInfo::setLineMax(double lineMax)
{
  m_lineMax = lineMax;
}

bool DrawLineInfo::isDrawLine() const
{
  return m_isDrawLine;
}

void DrawLineInfo::setIsDrawLine(bool isDrawLine)
{
  m_isDrawLine = isDrawLine;
}
