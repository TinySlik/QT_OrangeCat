#ifndef BASEITEM_H
#define BASEITEM_H

#include <QGraphicsItem>
#include <QPainter>
#include <QPixmap>
#include <QPixmapCache>

class BaseItem : public QGraphicsItem
{
public:
  explicit BaseItem();
  /**
   * @brief setItemSize 设置模块的大小
   * @param x x坐标
   * @param y y坐标
   * @param width  宽度
   * @param height 高度
   */
  void setItemSize(int x,int y,int width,int height);

protected:
  QRectF boundingRect() const override;

protected:
  int mItemX = 0;
  int mItemY = 0;
  int mItemWidth = 300;
  int mItemHeight = 200;
};

#endif // BASEITEM_H
