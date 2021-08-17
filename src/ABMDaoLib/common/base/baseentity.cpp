#include "baseentity.h"

BaseEntity::BaseEntity()
{

}

QDateTime BaseEntity::getCreatedTime() const
{
  return createdTime;
}

void BaseEntity::setCreatedTime(const QDateTime &value)
{
  createdTime = value;
}

QDateTime BaseEntity::getUpdatedTime() const
{
  return updatedTime;
}

void BaseEntity::setUpdatedTime(const QDateTime &value)
{
  updatedTime = value;
}

int BaseEntity::getIsDel() const
{
  return isDel;
}

void BaseEntity::setIsDel(int value)
{
  isDel = value;
}


