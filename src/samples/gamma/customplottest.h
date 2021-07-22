#ifndef CUSTOMPLOTTEST_H
#define CUSTOMPLOTTEST_H

#include <QWidget>

#include "qcustomplot/qcustomplot.h"

#define LOG_MAX 100
#define VEC_TEST_SIZE 500

enum PlotType{
  PlotNormal,
  PlotLog,
  PlotSin
};

namespace Ui {
class CustomPlotTest;
}

class CustomPlotTest : public QWidget
{
  Q_OBJECT

public:
  typedef struct paint_unit {
    QCPAxisRect *object;
//    std::vector<>
  } PAINT_UNIT;

  explicit CustomPlotTest(QWidget *parent = nullptr);
  ~CustomPlotTest();

  void initChart();
  void initChartData();

  //根据index数据,生成模拟其他数据
  void appendIndexData(const int value);
  void updateChartData();
  void plotChart(const bool left, const PlotType type);

  int getFirstChartWidth() {if (wideAxisRectLeft) return wideAxisRectLeft->rect().width(); else return -1;}

private slots:
  void updateIndex();
  void on_comboBox_left_currentIndexChanged(int index);
  void on_comboBox_right_currentIndexChanged(int index);
  void on_checkBox_stateChanged(int arg1);

private:
  Ui::CustomPlotTest *ui;

  QCPAxisRect *wideAxisRectLeft;
  QCPAxisRect *wideAxisRectMid;
  QCPAxisRect *wideAxisRectRight;

  QSharedPointer<QCPAxisTicker> ticker;
  QSharedPointer<QCPAxisTickerLog> logTicker;

  QList<QCPGraph *> graphLeft;
  QList<QCPGraph *> graphRight;

  //数据  500*2
  QVector<int> vecIndex;
  int vecHead = 0;

  QVector<double> vecKey;
  QVector<double> vecValue;
  QVector<double> vecValueSin;
  QVector< QPair<QVector<QCPGraphData>,int>> dataLog;

  std::vector<PAINT_UNIT> m_paint_units;

  QTimer timer;
};

#endif // CUSTOMPLOTTEST_H
