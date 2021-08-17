#ifndef DGRDAO_H
#define DGRDAO_H

#include "../entity/dgr.h"
#include "../../common/mysql/SqlUtils.h"

/**
 * @brief The SQL_PAGE struct 分页查询返回结构体
 */
struct DGRPage
{
  int pageNum;
  int pageSize;
  int totalPage;
  QList<QSharedPointer<DGR>> dataList;
};

class DGRDao
{
public:
  DGRDao();
  //新增
  bool add(QSharedPointer<DGR> entity);
  //修改
  bool updateById(QSharedPointer<DGR> entity);
  //批量查询
  QList<QSharedPointer<DGR> > findList(QVector<SqlCondition> &conditions);
  //分页查询
  DGRPage findPage(QVector<SqlCondition> &conditions, const int pageSize, const int pageNum);
  //根据id查询
  QSharedPointer<DGR> findById(int id);
  //根据wellInfoId and runInfoId查询
  QSharedPointer<DGR> findByWellInfoId(int wellInfoId, int runInfoId);

private:
  QString m_tableName = "u_dgr";

};

#endif // DGRDAO_H
