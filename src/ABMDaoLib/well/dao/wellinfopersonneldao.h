#ifndef WELLINFOPERSONNELDAO_H
#define WELLINFOPERSONNELDAO_H

#include "../entity/wellinfopersonnel.h"
#include "../../common/mysql/SqlUtils.h"

/**
 * @brief The SQL_PAGE struct 分页查询返回结构体
 */
struct WellInfoPersonnelPage
{
  int pageNum;
  int pageSize;
  int totalPage;
  QList<QSharedPointer<WellInfoPersonnel>> dataList;
};
class WellInfoPersonnelDao
{
public:
  WellInfoPersonnelDao();
  //新增井信息 personnel 信息
  bool add(QSharedPointer<WellInfoPersonnel> entity);
  //修改井信息 personnel 信息
  bool updateById(QSharedPointer<WellInfoPersonnel> entity);
  //批量查询井信息 personnel 集合
  QList<QSharedPointer<WellInfoPersonnel> > findList(QVector<SqlCondition> &conditions);
  //分页查询井信息 personnel 集合
  WellInfoPersonnelPage findPage(QVector<SqlCondition> &conditions, const int pageSize, const int pageNum);
  //根据id查询
  QSharedPointer<WellInfoPersonnel> findById(int id);
  //根据wellInfoId查询
  QSharedPointer<WellInfoPersonnel> findByWellInfoId(int wellInfoId);

private:
  QString m_tableName = "u_well_personnel";
};

#endif // WELLINFOPERSONNELDAO_H
