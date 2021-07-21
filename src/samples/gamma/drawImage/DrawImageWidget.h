#ifndef DRAWIMAGEWIDGET_H
#define DRAWIMAGEWIDGET_H

#include <QWidget>

#include "DrawPictureHead.h"

namespace Ui {
class DrawImageWidget;
}

class DrawImageWidget : public QWidget
{
  Q_OBJECT

public:
  explicit DrawImageWidget(QWidget *parent = nullptr);
  ~DrawImageWidget();

private:
  void initGraphicsView();

private:
  Ui::DrawImageWidget *ui;

  QGraphicsScene *m_gs;//主图区场景
  //图片头部
  DrawPictureHead *m_pictureHead;//图片头部图层
};

#endif // DRAWIMAGEWIDGET_H
