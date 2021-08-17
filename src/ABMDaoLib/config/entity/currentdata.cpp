#include "currentdata.h"

CurrentData::CurrentData()
{

}

QString CurrentData::getModel() const
{
  return model;
}

void CurrentData::setModel(const QString &value)
{
  model = value;
}

QString CurrentData::getKey() const
{
  return key;
}

void CurrentData::setKey(const QString &value)
{
  key = value;
}

QString CurrentData::getValue() const
{
  return value;
}

void CurrentData::setValue(const QString &value)
{
  this->value = value;
}

QString CurrentData::getRemark() const
{
  return remark;
}

void CurrentData::setRemark(const QString &value)
{
  remark = value;
}

