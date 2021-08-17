#ifndef RUNINFODESDAO_H
#define RUNINFODESDAO_H

#include "../entity/runinfodes.h"
#include "../../common/mysql/SqlUtils.h"

/**
 * @brief The SQL_PAGE struct 分页查询返回结构体
 */
struct RunInfoDesPage
{
  int pageNum;
  int pageSize;
  int totalPage;
  QList<QSharedPointer<RunInfoDes>> dataList;
};

class RunInfoDesDao
{
public:
  RunInfoDesDao();
  //新增运行号信息 Des 信息
  bool add(QSharedPointer<RunInfoDes> entity);
  //修改运行号信息 Des 信息
  bool updateById(QSharedPointer<RunInfoDes> entity);
  //批量查询运行号信息 Des 集合
  QList<QSharedPointer<RunInfoDes> > findList(QVector<SqlCondition> &conditions);
  //分页查询运行号信息 Des 集合
  RunInfoDesPage findPage(QVector<SqlCondition> &conditions, const int pageSize, const int pageNum);
  //根据id查询
  QSharedPointer<RunInfoDes> findById(int id);
  //根据runInfoId查询
  QSharedPointer<RunInfoDes> findByRunInfoId(int runInfoId);

private:
  QString m_tableName = "u_run_des";
};

#endif // RUNINFODESDAO_H
