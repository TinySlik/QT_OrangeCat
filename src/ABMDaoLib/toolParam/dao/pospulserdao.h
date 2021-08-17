#ifndef POSPULSERDAO_H
#define POSPULSERDAO_H

#include "../entity/pospulser.h"
#include "../../common/mysql/SqlUtils.h"

/**
 * @brief The SQL_PAGE struct 分页查询返回结构体
 */
struct PosPulserPage
{
  int pageNum;
  int pageSize;
  int totalPage;
  QList<QSharedPointer<PosPulser>> dataList;
};

class PosPulserDao
{
public:
  PosPulserDao();
  //新增
  bool add(QSharedPointer<PosPulser> entity);
  //修改
  bool updateById(QSharedPointer<PosPulser> entity);
  //批量查询
  QList<QSharedPointer<PosPulser> > findList(QVector<SqlCondition> &conditions);
  //分页查询
  PosPulserPage findPage(QVector<SqlCondition> &conditions, const int pageSize, const int pageNum);
  //根据id查询
  QSharedPointer<PosPulser> findById(int id);
  //根据wellInfoId and runInfoId查询
  QSharedPointer<PosPulser> findByWellInfoId(int wellInfoId, int runInfoId);

private:
  QString m_tableName = "u_pos_pulser";

};

#endif // POSPULSERDAO_H
