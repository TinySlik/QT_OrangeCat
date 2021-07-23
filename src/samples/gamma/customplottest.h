#ifndef CUSTOMPLOTTEST_H
#define CUSTOMPLOTTEST_H

#include <QWidget>
#include "type.h"

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
    std::vector<PAINT_LINE_UNIT> base;
    QCPAxisRect *object;
    QList<QCPGraph *> list;
  } PAINT_UNIT;

  explicit CustomPlotTest(QWidget *parent = nullptr);
  ~CustomPlotTest();

  void initChart();
  void initChartData();
  void refresh(std::vector<PAINT_LINE_UNIT> &in);

  //根据index数据,生成模拟其他数据
  void appendIndexData(const int value);
  void updateChartData();
  void plotChart(const bool left, const PlotType type);
  void plotChart(const int &index, const PlotType type);

  int getFirstChartWidth() {if (wideAxisRectLeft) return wideAxisRectLeft->rect().width(); else return -1;}
  void addColum(const PAINT_LINE_UNIT & unit);

private slots:
  void updateIndex();

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
  void addBaseUnit(PAINT_LINE_UNIT);

  QTimer timer;
};

#endif // CUSTOMPLOTTEST_H
