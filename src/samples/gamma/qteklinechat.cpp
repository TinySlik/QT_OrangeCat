#include "qteklinechat.h"
#include "ui_qteklinechat.h"
#include "customplottest.h"
#include "parameterserver.h"
#include "easylogging++.h"
#include "renderutil.h"
#include "rangeslider.h"
#define PADDING 14

QtekLineChat::QtekLineChat(std::vector<PAINT_LINE_UNIT> &lines_,QWidget *parent) :
  QWidget(parent),
  ui(new Ui::QtekLineChat),
  bar_width(20),
  head_height(140) {
  ui->setupUi(this);
  lines = lines_;
  initGraphicsView();
}

QtekLineChat::~QtekLineChat() {
  disconnect(slider, SIGNAL(lowerValueChanged(int)), m_customPlot, SLOT(onRangeChangedLow(int)));
  disconnect(slider, SIGNAL(upperValueChanged(int)), m_customPlot, SLOT(onRangeChangedUpper(int)));
  delete ui;
}

QRect QtekLineChat::getSnapRect() {
  return QRect(this->rect().x(), this->rect().y(), this->rect().width()- bar_width, this->rect().height());
}

void QtekLineChat::initGraphicsView(){
  m_gs = new QGraphicsScene(ui->graphicsView);
  m_gs->setSceneRect(this->rect());

  ui->graphicsView->setScene(m_gs);
  // 禁止滚动条
  ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  ui->graphicsView->setFrameShape(QFrame::Shape::NoFrame);
  ui->graphicsView->setFrameStyle(0);
  ui->graphicsView->setAlignment(Qt::AlignLeft | Qt::AlignTop);

  m_customPlot = new CustomPlotTest(this);
  m_gs->addWidget(m_customPlot);

  m_pictureHead = new DrawPictureHead();
  m_pictureHead->setFirstChartWidth(m_customPlot->getFirstChartWidth());
  m_pictureHead->setAxialSpread(50);
  m_gs->addItem(m_pictureHead);

  this->resize(this->rect().width(), this->rect().height());

  activeLines();
  slider = new RangeSlider(Qt::Vertical, RangeSlider::Option::DoubleHandles, this);
  slider->SetRange(0, 1000);
  m_customPlot->setSlider(slider);
  connect(slider, SIGNAL(lowerValueChanged(int)), m_customPlot, SLOT(onRangeChangedLow(int)));
  connect(slider, SIGNAL(upperValueChanged(int)), m_customPlot, SLOT(onRangeChangedUpper(int)));
  slider->update();
  slider->setLowerValue(0);
  slider->setUpperValue(200);
}

void QtekLineChat::addLine(PAINT_LINE_UNIT unit) {
  lines.push_back(unit);
}

void QtekLineChat::clearLine() {
  lines.clear();
}

void QtekLineChat::activeLines() {
  m_pictureHead->refresh(lines);
  m_customPlot->refresh(lines);
}

void QtekLineChat::resizeEvent(QResizeEvent *) {
  auto targetRect = QRect(this->rect().x(), this->rect().y(), this->rect().width()- bar_width, this->rect().height());
  auto targetRectBar = QRect(this->rect().width() - bar_width + 1, targetRect.y() + head_height, bar_width - 1, targetRect.height() - head_height);
  ui->graphicsView->setGeometry(this->rect());
  slider->setGeometry(targetRectBar);
  ui->comboBox ->setGeometry(QRect(this->rect().width() - bar_width + 1, targetRect.y(), bar_width - 1, head_height));
  m_customPlot->stackUnder(slider);
  m_customPlot->setGeometry(targetRect.x() - PADDING, targetRect.y() + head_height  - PADDING + 3, targetRect.width() + PADDING * 2 - 3, targetRect.height() - head_height + PADDING * 2);
  m_pictureHead->setFirstChartWidth(m_customPlot->getFirstChartWidth());
  m_pictureHead->setItemSize(targetRect.x(),targetRect.y(),targetRect.width() + 2, head_height);
}

void QtekLineChat::capture() {
  QRect rect = getSnapRect();
  QRect rect_raw = QRect(rect.x(), rect.y() + head_height, rect.width(), rect.height() - head_height);

  std::vector<QPixmap> array;
  QPixmap total_pixmap(QSize(rect.width(), rect_raw.height() * 10 + head_height));
  QPainter painter(&total_pixmap);
  for (size_t i =0; i < 10; ++i) {
    slider->SetLowerValue(i * 100);
    slider->SetUpperValue(i * 100 + 100);
    if (i == 0) {
      QPixmap p = this->grab(rect);
      array.push_back(p);
      painter.drawPixmap(rect, p);
    } else {
      QPixmap p = this->grab(rect_raw);
      array.push_back(p);
      painter.drawPixmap(QRect(rect_raw.x(), rect_raw.height() * i + head_height, rect.width(), rect_raw.height()), p);
    }
  }

  QString filePathName = "Snap";
  filePathName += QDateTime::currentDateTime().toString("yyyy-MM-dd hh-mm-ss-zzz");
  filePathName += ".png";
  if(!total_pixmap.save(filePathName,"png")) {
    LOG(INFO) <<"save widget screen failed";
  } else {
    LOG(INFO) << filePathName.toLatin1().data() << " saved.";
  }
}
