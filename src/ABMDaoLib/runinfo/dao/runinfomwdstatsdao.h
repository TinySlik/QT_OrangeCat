#ifndef RUNINFOMWDSTATSDAO_H
#define RUNINFOMWDSTATSDAO_H

#include "../entity/runinfomwdstats.h"
#include "../../common/mysql/SqlUtils.h"

/**
 * @brief The SQL_PAGE struct 分页查询返回结构体
 */
struct RunInfoMwdStatsPage
{
  int pageNum;
  int pageSize;
  int totalPage;
  QList<QSharedPointer<RunInfoMwdStats>> dataList;
};

class RunInfoMWDStatsDao
{
public:
  RunInfoMWDStatsDao();
  //新增运行号信息 MWDStats 信息
  bool add(QSharedPointer<RunInfoMwdStats> entity);
  //修改运行号信息 MWDStats 信息
  bool updateById(QSharedPointer<RunInfoMwdStats> entity);
  //批量查询运行号信息 MWDStats 集合
  QList<QSharedPointer<RunInfoMwdStats> > findList(QVector<SqlCondition> &conditions);
  //分页查询运行号信息 MWDStats 集合
  RunInfoMwdStatsPage findPage(QVector<SqlCondition> &conditions, const int pageSize, const int pageNum);
  //根据id查询
  QSharedPointer<RunInfoMwdStats> findById(int id);
  //根据runInfoId查询
  QSharedPointer<RunInfoMwdStats> findByRunInfoId(int runInfoId);

private:
  QString m_tableName = "u_run_mwd_stats";
};

#endif // RUNINFOMWDSTATSDAO_H
