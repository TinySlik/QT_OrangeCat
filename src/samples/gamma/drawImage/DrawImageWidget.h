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
  double m_beginX;    //起始X轴位置
  double m_beginY;    //起始Y轴位置
  double m_width;     //图像宽度
  double m_height;    //图像高度
  //图片头部
  DrawPictureHead *m_pictureHead;//图片头部图层


};

#endif // DRAWIMAGEWIDGET_H
