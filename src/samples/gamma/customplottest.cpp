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
  plotChart(true,PlotNormal);
  plotChart(false,PlotLog);
}

CustomPlotTest::~CustomPlotTest()
{
  delete ui;
}

void CustomPlotTest::initChart() {
  QTableWidget *tableWidget= ui->tableWidget;
  QCustomPlot *customPlot = new QCustomPlot(tableWidget);

  ui->tableWidget->verticalHeader()->setVisible(false);
  ui->tableWidget->horizontalHeader()->setVisible(false);
  ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
//  QLineEdit *lineEdit = new QLineEdit(ui->tableWidget);
//  lineEdit->setText("test");
  QLineEdit *lineEdit2 = new QLineEdit(ui->tableWidget);
  lineEdit2->setText("test");

  QGraphicsView *gra = new QGraphicsView();
  gra->setGeometry(0,0,200,300);
  QGraphicsScene *scene = new QGraphicsScene(gra);
  gra->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  gra->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  gra->setFrameShape(QFrame::Shape::NoFrame);
  auto head = new DrawPictureHead();
  head->setItemSize(0,0,256,100);
  scene->addItem(head);

  ui->tableWidget->setRowCount(3);
  ui->tableWidget->setColumnCount(1);
  ui->tableWidget->setCellWidget(0, 0, gra);
  ui->tableWidget->setCellWidget(1,0,customPlot);
  ui->tableWidget->setRowHeight(0, 768);
  ui->tableWidget->setRowHeight(1, 768);

  ui->tableWidget->setCellWidget(2,0,lineEdit2);

  customPlot->plotLayout()->clear();
  customPlot->plotLayout()->insertRow(0);
//  customPlot->plotLayout()->insertRow(1);

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
  wideAxisRectLeft->addAxes(QCPAxis::atTop | QCPAxis::atRight);
  QCPAxis *leftAxisX = wideAxisRectLeft->axis(QCPAxis::atRight);
  QCPAxis *leftAxisY = wideAxisRectLeft->axis(QCPAxis::atTop);

  leftAxisX->setBasePen(axia);
  leftAxisY->setBasePen(axia);

  //X轴倒显示
  leftAxisX->setRangeReversed(true);
  //网格线
  leftAxisY->grid()->setPen(gridPenY);
  leftAxisX->grid()->setPen(gridPenX);
  leftAxisY->grid()->setVisible(true);
  leftAxisX->grid()->setVisible(true);
  leftAxisY->grid()->setSubGridVisible(true);
  leftAxisY->setTicker(ticker);
  leftAxisY->setTickLabels(false);

  ////////右图显示 上和左坐标轴，并隐藏左坐标显示//////
  wideAxisRectRight->addAxes(QCPAxis::atTop | QCPAxis::atLeft);
  QCPAxis *rightAxisX = wideAxisRectRight->axis(QCPAxis::atLeft);
  QCPAxis *rightAxisY = wideAxisRectRight->axis(QCPAxis::atTop);
  //X轴倒显示
  rightAxisX->setRangeReversed(true);

  //网格线
  rightAxisY->grid()->setPen(gridPenY);
  rightAxisX->grid()->setPen(gridPenX);
  rightAxisY->grid()->setVisible(true);
  rightAxisX->grid()->setVisible(true);
  rightAxisY->grid()->setSubGridVisible(true);
    rightAxisX->setTickLabels(false);
  rightAxisY->setTickLabels(false);

  rightAxisY->setTicker(ticker);

  rightAxisX->setBasePen(axia);
  rightAxisY->setBasePen(axia);

//  QCPAxisRect *wideAxisRectHead  = new QCPAxisRect(customPlot,false);


//  wideAxisRectHead->addAxes(QCPAxis::atTop | QCPAxis::atLeft);
//  QCPAxis *headAxisY = wideAxisRectHead->axis(QCPAxis::atTop);
//  QCPAxis *headAxisX = wideAxisRectHead->axis(QCPAxis::atLeft);
//  //网格线
//  headAxisY->grid()->setPen(gridPenY);
//  headAxisX->grid()->setPen(gridPenX);
//  headAxisY->grid()->setVisible(true);
//  headAxisX->grid()->setVisible(false);
//  headAxisY->grid()->setSubGridVisible(true);
//  headAxisX->setTickLabels(false);
//  headAxisY->setTicker(ticker);


//  headAxisY->setBasePen(axia);

//  wideAxisRectHead->setMinimumMargins(QMargins(0, 0, 0, 0));

  ///测试第二个绘图右边再加个绘图
  QCPAxisRect *wideAxisRectOther  = new QCPAxisRect(customPlot,false);

  wideAxisRectOther->addAxes(QCPAxis::atTop | QCPAxis::atLeft);
  QCPAxis *otherAxisY = wideAxisRectOther->axis(QCPAxis::atTop);
  QCPAxis *otherAxisX = wideAxisRectOther->axis(QCPAxis::atLeft);
  //网格线
  otherAxisY->grid()->setPen(gridPenY);
  otherAxisX->grid()->setPen(gridPenX);
  otherAxisY->grid()->setVisible(true);
  otherAxisX->grid()->setVisible(false);
  otherAxisY->grid()->setSubGridVisible(true);
  otherAxisX->setTickLabels(false);
  otherAxisY->setTicker(ticker);
  otherAxisY->setTickLabels(false);

  otherAxisY->setBasePen(axia);

  otherAxisX->setTickLength(0,0);
  otherAxisX->setTickLabels(false);
  otherAxisX->setTicks(false);
  otherAxisX->setPadding(0);
  otherAxisX->setBasePen(axia);

//  customPlot->plotLayout()->setRowStretchFactor(0, 0.2);

  customPlot->plotLayout()->addElement(0, 0, wideAxisRectLeft);
  customPlot->plotLayout()->addElement(0, 1, wideAxisRectRight);
  customPlot->plotLayout()->addElement(0, 2, wideAxisRectOther);
//  customPlot->plotLayout()->addElementWholeRow(0, wideAxisRectHead);

  wideAxisRectLeft->setMinimumMargins(QMargins(0, 0, 0, 0));
  wideAxisRectRight->setMinimumMargins(QMargins(0, 0, 0, 0));
  wideAxisRectOther->setMinimumMargins(QMargins(0, 0, 0, 0));

  customPlot->plotLayout()->setColumnSpacing(0);
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
}

void CustomPlotTest::plotChart(const bool left, const PlotType type)
{
  QTableWidget *table = ui->tableWidget;
  auto customPlot= (QCustomPlot *)(table->cellWidget(1, 0));

  QCPAxis *axisX;
  QCPAxis *axisY;
  QCPAxis *otherAxisX;
  QList<QCPGraph *> *graphList;

  if(left) {
    axisX = wideAxisRectLeft->axis(QCPAxis::atRight);
    axisY = wideAxisRectLeft->axis(QCPAxis::atTop);
    graphList = &graphLeft;

    otherAxisX = wideAxisRectRight->axis(QCPAxis::atLeft);
  } else {
    axisX = wideAxisRectRight->axis(QCPAxis::atLeft);
    axisY = wideAxisRectRight->axis(QCPAxis::atTop);
    graphList = &graphRight;

    otherAxisX = wideAxisRectLeft->axis(QCPAxis::atRight);
  }

  foreach (QCPGraph * var, *graphList) {
    customPlot->removeGraph(var);
  }
  graphList->clear();

  switch (type) {
    case PlotNormal:{
      axisY->setScaleType(QCPAxis::stLinear);
      axisY->setTicker(ticker);

      QCPGraph *subGraph = customPlot->addGraph(axisX, axisY);
      subGraph->setData(vecKey,vecValue,true);
      subGraph->setLineStyle(QCPGraph::lsLine);
      subGraph->setPen(QPen(QColor("#FFA100"), 1.5));
      subGraph->rescaleAxes();

      graphList->append(subGraph);

      break;
    }
    case PlotSin: {
      axisY->setScaleType(QCPAxis::stLinear);
      axisY->setTicker(ticker);

      QCPGraph *subGraph = customPlot->addGraph(axisX, axisY);
      subGraph->setData(vecKey,vecValueSin,true);
      subGraph->setLineStyle(QCPGraph::lsLine);
      subGraph->setPen(QPen(QColor("#FFA100"), 1.5));
      subGraph->rescaleAxes();

      graphList->append(subGraph);
      break;
    }
    case PlotLog:{
      axisY->setScaleType(QCPAxis::stLogarithmic);
      axisY->setTicker(logTicker);

      for (int i = 0; i < dataLog.size(); ++i) {
        QCPGraph *subGraph = customPlot->addGraph(axisX, axisY);
        subGraph->data()->set(dataLog[i].first,true);
        subGraph->setLineStyle(QCPGraph::lsLine);
        subGraph->setPen(QPen(QColor("#FFA100"), (dataLog[i].second+1)*1.5));

        graphList->append(subGraph);
      }

      axisY->setRange(1,300);
      //    axisX->setRange((vecKey.first()+vecKey.last())/2 ,vecKey.last() - vecKey.first(),Qt::AlignCenter);

      break;
    }
  }


  double rangMin = qMax(vecKey.first(),otherAxisX->range().lower);
  double rangMax = qMax(vecKey.last(),otherAxisX->range().upper);
  axisX->setRange(rangMin,rangMax);


  //  qDebug() << "left:" << left << "vecKey:" << vecKey.first() << vecKey.last()
  //           << "other:" << otherAxisX->range().lower << otherAxisX->range().upper
  //           << "result:" << rangMin << rangMax;

  customPlot->replot();
}

void CustomPlotTest::updateIndex()
{
  int value = vecIndex[vecHead+VEC_TEST_SIZE-1];
  value += 1;

  appendIndexData(value);
  updateChartData();

  static int count = 0;

  if(++count >= 10){
    count = 0;

    plotChart(true,static_cast<PlotType>(ui->comboBox_left->currentIndex()));
    plotChart(false,static_cast<PlotType>(ui->comboBox_right->currentIndex()));
  }
}

void CustomPlotTest::on_comboBox_left_currentIndexChanged(int index)
{
  plotChart(true,static_cast<PlotType>(index));
}

void CustomPlotTest::on_comboBox_right_currentIndexChanged(int index)
{
  plotChart(false,static_cast<PlotType>(index));
}

void CustomPlotTest::on_checkBox_stateChanged(int arg1)
{
  if(arg1){
    timer.start(100);
  } else {
    timer.stop();
  }
}
