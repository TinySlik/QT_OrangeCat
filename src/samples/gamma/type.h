#ifndef TYPE_H
#define TYPE_H
#include <QColor>
#include <QString>
#include <functional>
#include <memory>
#include "parameterserver.h"
#include "QWidget"

typedef struct default_config_unit {
  QColor color;
  int    width;
  size_t colum;
  QString name;
  QString unit;
  double min;
  double max;
  std::function<void(std::shared_ptr<std::vector<unsigned char>>)> data_func;
} PAINT_LINE_UNIT;

typedef struct special_unit {
  QWidget * object;
  int colum;
  configuru::Config &config;
} SPEC_UNIT;

#endif // TYPE_H
