#ifndef BASEENTITY_H
#define BASEENTITY_H

#include <QDateTime>
#include <QSharedPointer>

#include "basecommon.h"

class BaseEntity : public BaseCommon
{
  Q_OBJECT
  Q_PROPERTY( QDateTime created_time READ getCreatedTime WRITE setCreatedTime)
  Q_PROPERTY( QDateTime updated_time READ getUpdatedTime WRITE setUpdatedTime)
  Q_PROPERTY( int is_del READ getIsDel WRITE setIsDel)
public:
  BaseEntity();

  QDateTime getCreatedTime() const;
  void setCreatedTime(const QDateTime &value);

  QDateTime getUpdatedTime() const;
  void setUpdatedTime(const QDateTime &value);

  int getIsDel() const;
  void setIsDel(int value);

protected:
  //创建时间
  QDateTime createdTime;
  //最后修改时间
  QDateTime updatedTime;
  //是否删除
  int isDel = 0;
};

#endif // BASEENTITY_H
