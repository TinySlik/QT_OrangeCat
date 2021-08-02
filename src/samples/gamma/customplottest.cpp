#include "customplottest.h"
#include "ui_CustomPlotTest.h"
#include "drawImage/DrawPictureHead.h"

CustomPlotTest::CustomPlotTest(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::CustomPlotTest)
{
  ui->setupUi(this);
  initChart();
  initChartData();
  updateChartData();
}

CustomPlotTest::~CustomPlotTest()
{
  delete ui;
}

void CustomPlotTest::initChart() {
  QCustomPlot *customPlot = ui->widget_cus;

  customPlot->plotLayout()->clear();
  customPlot->plotLayout()->insertRow(0);

  wideAxisRectLeft  = new QCPAxisRect(customPlot,false);
  wideAxisRectRight = new QCPAxisRect(customPlot,false);

  ticker = QSharedPointer<QCPAxisTicker>(new QCPAxisTicker());
  logTicker = QSharedPointer<QCPAxisTickerLog>(new QCPAxisTickerLog());

  //网格线颜色
  QPen gridPenX;
  gridPenX.setColor(QColor(0,255,0,150));
  QPen gridPenY;
  gridPenY.setColor(QColor(0,0,0,150));
  QPen axia;
  axia.setColor(QColor(0,0,0,255));
  axia.setWidthF(2.4);

  ////////左图显示 上和右坐标轴////////////////
  wideAxisRectLeft->addAxes(QCPAxis::atTop | QCPAxis::atRight | QCPAxis::atLeft | QCPAxis::atBottom);
  QCPAxis *leftAxisX = wideAxisRectLeft->axis(QCPAxis::atRight);
  leftAxisX->setLabelPadding(20);
  QCPAxis *leftAxisX_ = wideAxisRectLeft->axis(QCPAxis::atLeft);
  QCPAxis *leftAxisY = wideAxisRectLeft->axis(QCPAxis::atBottom);
  QCPAxis *leftAxisY_ = wideAxisRectLeft->axis(QCPAxis::atTop);

  leftAxisY_->setPadding(2);
  leftAxisY_->setBasePen(axia);
  leftAxisY_->setTickLabels(false);

  leftAxisX->setBasePen(axia);
  leftAxisY->setBasePen(axia);
  leftAxisX_->setBasePen(axia);

  //X轴倒显示
  leftAxisX->setRangeReversed(true);
  leftAxisX_->setRangeReversed(true);

  leftAxisX->setTickLabels(false);

  //网格线
  leftAxisY->grid()->setPen(gridPenY);
  leftAxisX->grid()->setPen(gridPenX);
  leftAxisY->grid()->setVisible(true);
  leftAxisX->grid()->setVisible(true);
  leftAxisX_->grid()->setVisible(false);
  leftAxisY->grid()->setSubGridVisible(true);
  leftAxisX_->grid()->setSubGridVisible(false);
  leftAxisX_->setTickLabels(false);
  leftAxisY->setTicker(ticker);
  leftAxisY->setTickLabels(false);
  leftAxisX->setPadding(46);

  customPlot->plotLayout()->addElement(0, 0, wideAxisRectLeft);
  wideAxisRectLeft->setMinimumMargins(QMargins(0, 0, 0, 0));


  m_paint_units.push_back({{}, wideAxisRectLeft, {}});

  ////////右图显示 上和左坐标轴，并隐藏左坐标显示//////
  wideAxisRectRight->addAxes(QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atBottom | QCPAxis::atRight);

  QCPAxis *rightAxisX = wideAxisRectRight->axis(QCPAxis::atLeft);
  QCPAxis *rightAxisX_ = wideAxisRectRight->axis(QCPAxis::atRight);
  QCPAxis *rightAxisY = wideAxisRectRight->axis(QCPAxis::atTop);
  QCPAxis *rightAxisY_ = wideAxisRectRight->axis(QCPAxis::atBottom);

  rightAxisY_->setBasePen(axia);
  rightAxisY_->setTickLabels(false);

  //X轴倒显示
  rightAxisX->setRangeReversed(true);
  rightAxisX_->setRangeReversed(true);

  //网格线
  rightAxisY->grid()->setPen(gridPenY);
  rightAxisX->grid()->setPen(gridPenX);
  rightAxisX_->grid()->setPen(gridPenX);
  rightAxisY->grid()->setVisible(true);
  rightAxisX->grid()->setVisible(true);
  rightAxisX_->grid()->setVisible(true);
  rightAxisY->grid()->setSubGridVisible(true);
  rightAxisX->setTickLabels(false);
//  rightAxisX->setTickLabelPadding(10);
  rightAxisX_->setTickLabels(false);
  rightAxisY->setTickLabels(false);

  rightAxisY->setTicker(ticker);

  rightAxisX->setBasePen(axia);
  rightAxisX_->setBasePen(axia);
  rightAxisX_->setPadding(0);
  rightAxisY->setBasePen(axia);
  rightAxisY->setPadding(2);
  customPlot->plotLayout()->addElement(0, 1, wideAxisRectRight);
  wideAxisRectRight->setMinimumMargins(QMargins(0, 0, 0, 0));
  m_paint_units.push_back({{}, wideAxisRectRight, {}});

  customPlot->plotLayout()->setColumnSpacing(0);
  customPlot->plotLayout()->setColumnStretchFactor(1, 1.03);
}

void CustomPlotTest::addColum(const PAINT_LINE_UNIT &unit) {
  while (unit.colum >= m_paint_units.size()) {
    //网格线颜色
    QPen gridPenX;
    gridPenX.setColor(QColor(0,255,0,150));
    QPen gridPenY;
    gridPenY.setColor(QColor(0,0,0,150));
    QPen axia;
    axia.setColor(QColor(0,0,0,255));
    axia.setWidthF(2.4);
    QCustomPlot *customPlot = ui->widget_cus;
    QCPAxisRect *wideAxisRectNew  = new QCPAxisRect(customPlot,false);
    wideAxisRectNew->addAxes(QCPAxis::atTop | QCPAxis::atLeft | QCPAxis::atRight | QCPAxis::atBottom);
    QCPAxis *otherAxisY = wideAxisRectNew->axis(QCPAxis::atBottom);
    QCPAxis *otherAxisX = wideAxisRectNew->axis(QCPAxis::atLeft);
    QCPAxis *otherAxisX_ = wideAxisRectNew->axis(QCPAxis::atRight);
    QCPAxis *otherAxisY_ = wideAxisRectNew->axis(QCPAxis::atTop);

    otherAxisY_->setPadding(2);
    otherAxisY_->setBasePen(axia);
    otherAxisY_->setTickLabels(false);
    //网格线
    otherAxisY->grid()->setPen(gridPenY);
    otherAxisX->grid()->setPen(gridPenX);
    otherAxisY->grid()->setVisible(true);
    otherAxisX->grid()->setVisible(true);
    otherAxisX_->grid()->setVisible(false);
    otherAxisY->grid()->setSubGridVisible(true);
    otherAxisX->setTickLabels(false);
    otherAxisX_->setTickLabels(false);
    otherAxisX_->setPadding(0);
    otherAxisY->setTicker(ticker);
    otherAxisY->setTickLabels(false);

    otherAxisY->setBasePen(axia);

    otherAxisX->setTickLength(0,0);
    otherAxisX->setTicks(false);
    otherAxisX->setPadding(0);
    otherAxisX->setBasePen(axia);
    otherAxisX_->setBasePen(axia);

    otherAxisX->setRangeReversed(true);
    otherAxisX_->setRangeReversed(true);

    m_paint_units.push_back({{}, wideAxisRectNew, {}});

    customPlot->plotLayout()->addElement(0, m_paint_units.size() - 1, wideAxisRectNew);
    wideAxisRectNew->setMinimumMargins(QMargins(0, 0, 0, 0));
  }
  (m_paint_units[unit.colum].base).push_back(unit);
}

void CustomPlotTest::scroll(int index) {
  QCPAxis *leftAxisX = wideAxisRectLeft->axis(QCPAxis::atRight);
  QCPAxis *leftAxisX_ = wideAxisRectLeft->axis(QCPAxis::atLeft);
  leftAxisX->setRange(index * 100 , (index +1) * 100);
  double rangeMin = index * 10.0;
  double rangeMax = (index + 10) * 10.0;
  for (size_t i = 0; i< m_paint_units.size(); ++i) {
    auto a = m_paint_units[i].object->axis(QCPAxis::atRight);
    auto b = m_paint_units[i].object->axis(QCPAxis::atLeft);
    a->setRange(rangeMin, rangeMax);
    b->setRange(rangeMin, rangeMax);
  }
  QCustomPlot *customPlot = ui->widget_cus;
  customPlot->replot();
}

void CustomPlotTest::initChartData()
{
  vecIndex.resize(VEC_TEST_SIZE*2);

  for (int i = 0; i < VEC_TEST_SIZE; ++i) {
    vecIndex[i] = i;
    vecIndex[i+VEC_TEST_SIZE] = i;
  }

  connect(&timer,&QTimer::timeout,this,&CustomPlotTest::updateIndex);
}

void CustomPlotTest::appendIndexData(const int value)
{
  vecIndex[vecHead] = value;
  vecIndex[vecHead+VEC_TEST_SIZE] = value;

  ++vecHead;
  if(vecHead == VEC_TEST_SIZE){
    vecHead = 0;
  }
}

void CustomPlotTest::updateChartData()
{
  vecKey.clear();
  vecValue.clear();
  vecValueSin.clear();
  dataLog.clear();

  for(int i = 0; i < VEC_TEST_SIZE; ++i){
    vecKey.append(vecIndex[i+vecHead]);
    vecValue.append( vecIndex[i+vecHead] % 250);
    vecValueSin.append(sin(vecIndex[i+vecHead]));

    //模拟对数坐标系数据
    double tempValue = vecIndex[i+vecHead] % 250;
    int onceCount = 0;
    while(tempValue / LOG_MAX > 1){
      tempValue /= LOG_MAX;
      onceCount++;
    }

    static int count = 0;
    if(count != onceCount || dataLog.isEmpty()) {
      count = onceCount;

      dataLog.append(QPair<QVector<QCPGraphData>,int>(QVector<QCPGraphData>(),count));
    }

    QCPGraphData onceValue(vecIndex[i+vecHead],tempValue);
    dataLog.last().first.append(onceValue);
  }

  plotChart(0, PlotNormal);
  plotChart(1, PlotLog);
  for (int i = 2 ; i< m_paint_units.size(); i++) {
     plotChart(i, PlotNormal);
  }
}

void CustomPlotTest::plotChart(const int &index, const PlotType type) {
  QCustomPlot *customPlot = ui->widget_cus;

  QCPAxis *axisX;
  QCPAxis *axisY;
  QCPAxis *otherAxisX;
  QList<QCPGraph *> *graphList;
  auto target = m_paint_units[index].object;
  axisX = target->axis(QCPAxis::atLeft);
  axisY = target->axis(QCPAxis::atTop);
  graphList = &m_paint_units[index].list;

  otherAxisX = wideAxisRectLeft->axis(QCPAxis::atRight);

  foreach (QCPGraph * var, *graphList) {
    customPlot->removeGraph(var);
  }
  graphList->clear();

  switch (type) {
    case PlotNormal:{
      axisY->setScaleType(QCPAxis::stLinear);
      axisY->setTicker(ticker);
      for (size_t i = 0; i < m_paint_units[index].base.size(); ++i) {
        QCPGraph *subGraph = customPlot->addGraph(axisX, axisY);
        subGraph->setData(vecKey,vecValue,true);
        subGraph->setLineStyle(QCPGraph::lsLine);
        subGraph->setPen(QPen(m_paint_units[index].base[i].color, m_paint_units[index].base[i].width));
//        subGraph->rescaleAxes();
        graphList->append(subGraph);
      }
      break;
    }
    case PlotSin: {
      axisY->setScaleType(QCPAxis::stLinear);
      axisY->setTicker(ticker);
      for (size_t i = 0; i < m_paint_units[index].base.size(); ++i) {
        QCPGraph *subGraph = customPlot->addGraph(axisX, axisY);
        subGraph->setData(vecKey,vecValue,true);
        subGraph->setLineStyle(QCPGraph::lsLine);
        subGraph->setPen(QPen(m_paint_units[index].base[i].color, m_paint_units[index].base[i].width));
//        subGraph->rescaleAxes();
        graphList->append(subGraph);
      }
      break;
    }
    case PlotLog:{
      axisY->setScaleType(QCPAxis::stLogarithmic);
      axisY->setTicker(logTicker);

      for (int i = 0; i < dataLog.size(); ++i) {
        for (size_t i = 0; i < m_paint_units[index].base.size(); ++i) {
          QCPGraph *subGraph = customPlot->addGraph(axisX, axisY);
          subGraph->setData(vecKey,vecValue,true);
          subGraph->setLineStyle(QCPGraph::lsLine);
          subGraph->setPen(QPen(m_paint_units[index].base[i].color, m_paint_units[index].base[i].width));
          graphList->append(subGraph);
        }
      }

      axisY->setRange(1,300);
      //    axisX->setRange((vecKey.first()+vecKey.last())/2 ,vecKey.last() - vecKey.first(),Qt::AlignCenter);
      break;
    }
  }
  double rangMin = qMax(vecKey.first(),otherAxisX->range().lower);
  double rangMax = qMax(vecKey.last(),otherAxisX->range().upper);
//  axisX->setRange(rangMin,rangMax);

  //  qDebug() << "left:" << left << "vecKey:" << vecKey.first() << vecKey.last()
  //           << "other:" << otherAxisX->range().lower << otherAxisX->range().upper
  //           << "result:" << rangMin << rangMax;

  customPlot->replot();
}

void CustomPlotTest::refresh(std::vector<PAINT_LINE_UNIT> &in) {
  for (int i = 0; i < in.size(); ++i) {
//    auto cfg = in[i];
    addBaseUnit(in[i]);
  }
  updateChartData();
}

void CustomPlotTest::addBaseUnit(PAINT_LINE_UNIT unit) {
  addColum(unit);
}

void CustomPlotTest::updateIndex()
{
  int value = vecIndex[vecHead+VEC_TEST_SIZE-1];
  value += 1;

  appendIndexData(value);
  updateChartData();

  static int count = 0;
}

