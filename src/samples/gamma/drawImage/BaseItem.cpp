#include "BaseItem.h"


BaseItem::BaseItem() : QGraphicsItem()
{

}

void BaseItem::setItemSize(int x, int y, int width, int height)
{
  mItemX = x;
  mItemY = y;
  mItemWidth = width;
  mItemHeight = height;
  prepareGeometryChange();
}

QRectF BaseItem::boundingRect() const
{
  return QRectF(mItemX,mItemY,mItemWidth,mItemHeight);
}
