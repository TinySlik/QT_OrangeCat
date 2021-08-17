#ifndef WELLINFOMATCHEDSYSTEMSTRACKINGDAO_H
#define WELLINFOMATCHEDSYSTEMSTRACKINGDAO_H

#include "../entity/wellinfomatchedsystemstracking.h"
#include "../../common/mysql/SqlUtils.h"

/**
 * @brief The SQL_PAGE struct 分页查询返回结构体
 */
struct WellInfoMatchedSystemsTrackingPage
{
  int pageNum;
  int pageSize;
  int totalPage;
  QList<QSharedPointer<WellInfoMatchedSystemsTracking>> dataList;
};

class WellInfoMatchedSystemsTrackingDao
{
public:
  WellInfoMatchedSystemsTrackingDao();
  //新增井信息 MatchedSystemsTracking 信息
  bool add(QSharedPointer<WellInfoMatchedSystemsTracking> entity);
  //修改井信息 MatchedSystemsTracking 信息
  bool updateById(QSharedPointer<WellInfoMatchedSystemsTracking> entity);
  //批量查询井信息 MatchedSystemsTracking 集合
  QList<QSharedPointer<WellInfoMatchedSystemsTracking> > findList(QVector<SqlCondition> &conditions);
  //分页查询井信息 MatchedSystemsTracking 集合
  WellInfoMatchedSystemsTrackingPage findPage(QVector<SqlCondition> &conditions, const int pageSize, const int pageNum);
  //根据id查询
  QSharedPointer<WellInfoMatchedSystemsTracking> findById(int id);
  //根据wellInfoId查询
  QSharedPointer<WellInfoMatchedSystemsTracking> findByWellInfoId(int wellInfoId);

private:
  QString m_tableName = "u_well_matched_systems_tracking";
};

#endif // WELLINFOMATCHEDSYSTEMSTRACKINGDAO_H
