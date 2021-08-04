#ifndef CUSTOMWIDGET_H
#define CUSTOMWIDGET_H

#include "qteklinechat.h"
#include "type.h"
#include <memory>
#include <QObject>
#include <QWidget>
#include "glchartwidget.h"

class CustomWidget : public QWidget
{
  typedef struct special_unit {
    QWidget * object;
    int colum;
  } SPEC_UNIT;
  Q_OBJECT
public:
  explicit CustomWidget(QWidget *parent = nullptr);
  ~CustomWidget();
signals:
  void NewQtekLineChatSIG();
  void CaptureSIG();
public slots:
  void NewQtekLineChat();
  void Capture();
protected:
  virtual void resizeEvent(QResizeEvent *event) override;
public:
  void NewQtekLineChat(std::vector<PAINT_LINE_UNIT> lines);
  QtekLineChat * chart;
  std::vector<PAINT_LINE_UNIT> m_lines;
  int _lineChatWidth;
  int _lineChatHeight;
  void slotGrabWidgetScreen();
 private:
  std::vector<SPEC_UNIT> m_special_widget;
};

#endif // CUSTOMWIDGET_H
