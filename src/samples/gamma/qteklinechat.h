#ifndef QTEKLINECHAT_H
#define QTEKLINECHAT_H

#include <QWidget>
#include "drawImage/DrawPictureHead.h"

namespace Ui {
  class QtekLineChat;
}

class QtekLineChat : public QWidget
{
  Q_OBJECT

public:
  explicit QtekLineChat(QWidget *parent = nullptr);
  ~QtekLineChat();

private:
  void initGraphicsView();

private:

  QGraphicsScene *m_gs;//主图区场景
  double m_beginX;    //起始X轴位置
  double m_beginY;    //起始Y轴位置
  double m_width;     //图像宽度
  double m_height;    //图像高度
  //图片头部
  DrawPictureHead *m_pictureHead;//图片头部图层
private:
  Ui::QtekLineChat *ui;
};

#endif // QTEKLINECHAT_H
