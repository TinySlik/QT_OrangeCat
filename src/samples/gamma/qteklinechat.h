#ifndef QTEKLINECHAT_H
#define QTEKLINECHAT_H

#include <QWidget>
#include "drawImage/DrawPictureHead.h"
#include "customplottest.h"

namespace Ui {
  class QtekLineChat;
}

class QtekLineChat : public QWidget
{
  Q_OBJECT
public:
  explicit QtekLineChat(QWidget *parent = nullptr);
  ~QtekLineChat();
protected:
  virtual void resizeEvent(QResizeEvent *event) override;

private:
  void initGraphicsView();

  QGraphicsScene *m_gs;//主图区场景
  double m_beginX;    //起始X轴位置
  double m_beginY;    //起始Y轴位置
  double m_width;     //图像宽度
  double m_height;    //图像高度
  //图片头部
  DrawPictureHead *m_pictureHead;//图片头部图层
  CustomPlotTest *m_customPlot;
private:
  Ui::QtekLineChat *ui;
};

#endif // QTEKLINECHAT_H
