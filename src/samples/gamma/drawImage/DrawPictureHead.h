#ifndef DRAWPICTUREHEAD_H
#define DRAWPICTUREHEAD_H

#include <QGraphicsItem>

#include  "BaseItem.h"
#include "DrawLineInfo.h"

class DrawPictureHead : public BaseItem
{  
public:
  DrawPictureHead();

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
    DrawLineInfo *m_drawLineInfo1;//平均伽马
    DrawLineInfo *m_drawLineInfo2;//上伽马
    DrawLineInfo *m_drawLineInfo3;//下伽马
    DrawLineInfo *m_drawLineInfo4;//井深
};

#endif // DRAWPICTUREHEAD_H
