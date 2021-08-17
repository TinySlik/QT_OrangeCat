#ifndef ABIDAO_H
#define ABIDAO_H

#include "../entity/abi.h"
#include "../../common/mysql/SqlUtils.h"

/**
 * @brief The SQL_PAGE struct 分页查询返回结构体
 */
struct ABIPage
{
  int pageNum;
  int pageSize;
  int totalPage;
  QList<QSharedPointer<ABI>> dataList;
};

class ABIDao
{
public:
  ABIDao();
  //新增
  bool add(QSharedPointer<ABI> entity);
  //修改
  bool updateById(QSharedPointer<ABI> entity);
  //批量查询
  QList<QSharedPointer<ABI> > findList(QVector<SqlCondition> &conditions);
  //分页查询
  ABIPage findPage(QVector<SqlCondition> &conditions, const int pageSize, const int pageNum);
  //根据id查询
  QSharedPointer<ABI> findById(int id);
  //根据wellInfoId and runInfoId查询
  QSharedPointer<ABI> findByWellInfoId(int wellInfoId, int runInfoId);

private:
  QString m_tableName = "u_abi";

};
#endif // ABIDAO_H
