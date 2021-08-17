#ifndef RUNINFODRILLSTATSDAO_H
#define RUNINFODRILLSTATSDAO_H

#include "../entity/runinfodrillstats.h"
#include "../../common/mysql/SqlUtils.h"

/**
 * @brief The SQL_PAGE struct 分页查询返回结构体
 */
struct RunInfoDrillStatsPage
{
  int pageNum;
  int pageSize;
  int totalPage;
  QList<QSharedPointer<RunInfoDrillStats>> dataList;
};

class RunInfoDrillStatsDao
{
public:
  RunInfoDrillStatsDao();
  //新增运行号信息 DrillStats 信息
  bool add(QSharedPointer<RunInfoDrillStats> entity);
  //修改运行号信息 DrillStats 信息
  bool updateById(QSharedPointer<RunInfoDrillStats> entity);
  //批量查询运行号信息 DrillStats 集合
  QList<QSharedPointer<RunInfoDrillStats> > findList(QVector<SqlCondition> &conditions);
  //分页查询运行号信息 DrillStats 集合
  RunInfoDrillStatsPage findPage(QVector<SqlCondition> &conditions, const int pageSize, const int pageNum);
  //根据id查询
  QSharedPointer<RunInfoDrillStats> findById(int id);
  //根据runInfoId查询
  QSharedPointer<RunInfoDrillStats> findByRunInfoId(int runInfoId);

private:
  QString m_tableName = "u_run_drill_stats";
};

#endif // RUNINFODRILLSTATSDAO_H
