#ifndef TOOLPARAMETERSDAO_H
#define TOOLPARAMETERSDAO_H

#include "../entity/toolparameters.h".h"
#include "../../common/mysql/SqlUtils.h"

/**
 * @brief The SQL_PAGE struct 分页查询返回结构体
 */
struct ToolParametersPage
{
  int pageNum;
  int pageSize;
  int totalPage;
  QList<QSharedPointer<ToolParameters>> dataList;
};

class ToolParametersDao
{
public:
  ToolParametersDao();
  //新增
  bool add(QSharedPointer<ToolParameters> entity);
  //修改
  bool updateById(QSharedPointer<ToolParameters> entity);
  //批量查询
  QList<QSharedPointer<ToolParameters> > findList(QVector<SqlCondition> &conditions);
  //分页查询
  ToolParametersPage findPage(QVector<SqlCondition> &conditions, const int pageSize, const int pageNum);
  //根据id查询
  QSharedPointer<ToolParameters> findById(int id);
  //根据wellInfoId and runInfoId查询
  QList<QSharedPointer<ToolParameters> > findByWellAndRun(int wellInfoId, int runInfoId);

private:
  QString m_tableName = "u_tool_parameters";

};

#endif // TOOLPARAMETERSDAO_H
