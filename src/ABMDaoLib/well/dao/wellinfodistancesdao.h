#ifndef WELLINFODISTANCESDAO_H
#define WELLINFODISTANCESDAO_H

#include "../entity/wellinfodistances.h"
#include "../../common/mysql/SqlUtils.h"

/**
 * @brief The SQL_PAGE struct 分页查询返回结构体
 */
struct WellInfoDistancesPage
{
  int pageNum;
  int pageSize;
  int totalPage;
  QList<QSharedPointer<WellInfoDistances>> dataList;
};

class WellInfoDistancesDao
{
public:
  WellInfoDistancesDao();
  //新增井信息 Distance 信息
  bool add(QSharedPointer<WellInfoDistances> entity);
  //修改井信息 Distance 信息
  bool updateById(QSharedPointer<WellInfoDistances> entity);
  //批量查询井信息 Distance 集合
  QList<QSharedPointer<WellInfoDistances> > findList(QVector<SqlCondition> &conditions);
  //分页查询井信息 Distance 集合
  WellInfoDistancesPage findPage(QVector<SqlCondition> &conditions, const int pageSize, const int pageNum);
  //根据id查询
  QSharedPointer<WellInfoDistances> findById(int id);
  //根据wellInfoId查询
  QSharedPointer<WellInfoDistances> findByWellInfoId(int wellInfoId);

private:
  QString m_tableName = "u_well_distances";
};

#endif // WELLINFODISTANCESDAO_H
