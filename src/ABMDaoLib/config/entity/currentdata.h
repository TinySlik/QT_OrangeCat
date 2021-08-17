#ifndef CURRENTDATA_H
#define CURRENTDATA_H

#include "../../common/base/basecommon.h"

class CurrentData : public BaseCommon
{
  Q_OBJECT
  Q_PROPERTY(QString model READ getModel WRITE setModel)
  Q_PROPERTY(QString key READ getKey WRITE setKey)
  Q_PROPERTY(QString value READ getValue WRITE setValue)
  Q_PROPERTY(QString remark READ getRemark WRITE setRemark)

public:
  CurrentData();

  QString getModel() const;
  void setModel(const QString &value);

  QString getKey() const;
  void setKey(const QString &value);

  QString getValue() const;
  void setValue(const QString &value);

  QString getRemark() const;
  void setRemark(const QString &value);

private:
  QString model;
  QString key;
  QString value;
  QString remark;
};

#endif // CURRENTDATA_H
