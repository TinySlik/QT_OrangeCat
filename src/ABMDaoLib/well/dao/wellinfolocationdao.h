#ifndef WELLINFOLOCATIONDAO_H
#define WELLINFOLOCATIONDAO_H

#include "../entity/wellinfolocation.h"
#include "../../common/mysql/SqlUtils.h"

/**
 * @brief The SQL_PAGE struct 分页查询返回结构体
 */
struct WellInfoLocationPage
{
  int pageNum;
  int pageSize;
  int totalPage;
  QList<QSharedPointer<WellInfoLocation>> dataList;
};

class WellInfoLocationDao
{
public:
  WellInfoLocationDao();
  //新增井信息 Location 信息
  bool add(QSharedPointer<WellInfoLocation> entity);
  //修改井信息 Location 信息
  bool updateById(QSharedPointer<WellInfoLocation> entity);
  //批量查询井信息 Location 集合
  QList<QSharedPointer<WellInfoLocation> > findList(QVector<SqlCondition> &conditions);
  //分页查询井信息 Location 集合
  WellInfoLocationPage findPage(QVector<SqlCondition> &conditions, const int pageSize, const int pageNum);
  //根据id查询
  QSharedPointer<WellInfoLocation> findById(int id);
  //根据wellInfoId查询
  QSharedPointer<WellInfoLocation> findByWellInfoId(int wellInfoId);

private:
  QString m_tableName = "u_well_location";
};

#endif // WELLINFOLOCATIONDAO_H
