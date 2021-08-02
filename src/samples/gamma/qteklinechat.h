#ifndef QTEKLINECHAT_H
#define QTEKLINECHAT_H

#include <QWidget>
#include "drawImage/DrawPictureHead.h"
#include "customplottest.h"
#include "type.h"

namespace Ui {
  class QtekLineChat;
}

class QtekLineChat : public QWidget
{
  Q_OBJECT
public:
  explicit QtekLineChat(std::vector<PAINT_LINE_UNIT> &lines, QWidget *parent = nullptr);
  ~QtekLineChat() override;
  void addLine(PAINT_LINE_UNIT);
  void clearLine();
  void activeLines();
  QRect getSnapRect();
  void capture();
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
  std::vector<PAINT_LINE_UNIT> lines;
private:
  Ui::QtekLineChat *ui;
  int bar_width;
  int head_height;
};

#endif // QTEKLINECHAT_H
