#ifndef RUNINFORELIABILITYDAO_H
#define RUNINFORELIABILITYDAO_H

#include "../entity/runinforeliability.h"
#include "../../common/mysql/SqlUtils.h"

/**
 * @brief The SQL_PAGE struct 分页查询返回结构体
 */
struct RunInfoReliabilityPage
{
  int pageNum;
  int pageSize;
  int totalPage;
  QList<QSharedPointer<RunInfoReliability>> dataList;
};

class RunInfoReliabilityDao
{
public:
  RunInfoReliabilityDao();
  //新增运行号信息 Reliability 信息
  bool add(QSharedPointer<RunInfoReliability> entity);
  //修改运行号信息 Reliability 信息
  bool updateById(QSharedPointer<RunInfoReliability> entity);
  //批量查询运行号信息 Reliability 集合
  QList<QSharedPointer<RunInfoReliability> > findList(QVector<SqlCondition> &conditions);
  //分页查询运行号信息 Reliability 集合
  RunInfoReliabilityPage findPage(QVector<SqlCondition> &conditions, const int pageSize, const int pageNum);
  //根据id查询
  QSharedPointer<RunInfoReliability> findById(int id);
  //根据runInfoId查询
  QSharedPointer<RunInfoReliability> findByRunInfoId(int runInfoId);

private:
  QString m_tableName = "u_run_reliability";
};

#endif // RUNINFORELIABILITYDAO_H
