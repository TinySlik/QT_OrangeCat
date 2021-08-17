#ifndef RUNINFOMUDSTATSDAO_H
#define RUNINFOMUDSTATSDAO_H

#include "../entity/runinfomudstats.h"
#include "../../common/mysql/SqlUtils.h"

/**
 * @brief The SQL_PAGE struct 分页查询返回结构体
 */
struct RunInfoMudStatsPage
{
  int pageNum;
  int pageSize;
  int totalPage;
  QList<QSharedPointer<RunInfoMudStats>> dataList;
};

class RunInfoMudStatsDao
{
public:
  RunInfoMudStatsDao();
  //新增运行号信息 MudStats 信息
  bool add(QSharedPointer<RunInfoMudStats> entity);
  //修改运行号信息 MudStats 信息
  bool updateById(QSharedPointer<RunInfoMudStats> entity);
  //批量查询运行号信息 MudStats 集合
  QList<QSharedPointer<RunInfoMudStats> > findList(QVector<SqlCondition> &conditions);
  //分页查询运行号信息 MudStats 集合
  RunInfoMudStatsPage findPage(QVector<SqlCondition> &conditions, const int pageSize, const int pageNum);
  //根据id查询
  QSharedPointer<RunInfoMudStats> findById(int id);
  //根据runInfoId查询
  QSharedPointer<RunInfoMudStats> findByRunInfoId(int runInfoId);

private:
  QString m_tableName = "u_run_mud_stats";
};

#endif // RUNINFOMUDSTATSDAO_H
