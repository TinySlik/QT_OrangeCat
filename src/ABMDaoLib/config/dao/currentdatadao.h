#ifndef CURRENTDATADAO_H
#define CURRENTDATADAO_H

#include "../entity/currentdata.h"
#include "../../common/mysql/SqlUtils.h"

class CurrentDataDao
{
public:
  CurrentDataDao();
  //新增
  bool add(QSharedPointer<CurrentData> entity);
  //修改
  bool updateByKey(QSharedPointer<CurrentData> entity);
  //批量查询
  QList<QSharedPointer<CurrentData> > findList(QVector<SqlCondition> &conditions);
  //根据key查询
  QSharedPointer<CurrentData> findByKey(QString key);
  //根据model查询
  QList<QSharedPointer<CurrentData>> findByModel(QString model);

private:
  QString m_tableName = "u_current_data";

};
//初始化sql语句
//INSERT INTO `abm100`.`u_current_data`(`key`, `model`, `value`, `remark`) VALUES ('runInfoId', 'system', '0000', NULL);
//INSERT INTO `abm100`.`u_current_data`(`key`, `model`, `value`, `remark`) VALUES ('wellInfoId', 'system', '000', NULL);


#endif // CURRENTDATADAO_H
