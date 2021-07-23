#ifndef TYPE_H
#define TYPE_H
#include <QColor>
#include <QString>
#include <functional>
#include <memory>

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

#endif // TYPE_H
