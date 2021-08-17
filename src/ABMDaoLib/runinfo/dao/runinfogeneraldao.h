#ifndef RUNINFOGENERALDAO_H
#define RUNINFOGENERALDAO_H

#include "../entity/runinfogeneral.h"
#include "../../common/mysql/SqlUtils.h"

/**
 * @brief The SQL_PAGE struct 分页查询返回结构体
 */
struct RunInfoGeneralPage
{
  int pageNum;
  int pageSize;
  int totalPage;
  QList<QSharedPointer<RunInfoGeneral>> dataList;
};

class RunInfoGeneralDao
{
public:
  RunInfoGeneralDao();
  //新增运行号信息 General 信息
  bool add(QSharedPointer<RunInfoGeneral> entity);
  //修改运行号信息 General 信息
  bool updateById(QSharedPointer<RunInfoGeneral> entity);
  //批量查询运行号信息 General 集合
  QList<QSharedPointer<RunInfoGeneral> > findList(QVector<SqlCondition> &conditions);
  //分页查询运行号信息 General 集合
  RunInfoGeneralPage findPage(QVector<SqlCondition> &conditions, const int pageSize, const int pageNum);
  //根据id查询
  QSharedPointer<RunInfoGeneral> findById(int id);
  //根据wellInfoId查询
  QList<QSharedPointer<RunInfoGeneral>> findByWellInfoId(int wellInfoId);
  //根据运行号查询
  QSharedPointer<RunInfoGeneral> findByRun(int wellInfoId,QString run);

private:
  QString m_tableName = "u_run_info";
};

#endif // RUNINFOGENERALDAO_H
