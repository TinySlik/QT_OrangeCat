#ifndef CUSTOMWIDGET_H
#define CUSTOMWIDGET_H

#include "qteklinechat.h"
#include "type.h"
#include <memory>
#include <QObject>
#include <QWidget>

class CustomWidget : public QWidget
{
  Q_OBJECT
public:
  explicit CustomWidget(QWidget *parent = nullptr);
  ~CustomWidget(){}
signals:
  void NewQtekLineChatSIG();
public slots:
  void NewQtekLineChat();
public:
 void NewQtekLineChat(std::vector<PAINT_LINE_UNIT> lines);
 QtekLineChat * chart;
 std::vector<PAINT_LINE_UNIT> m_lines;
};

#endif // CUSTOMWIDGET_H
