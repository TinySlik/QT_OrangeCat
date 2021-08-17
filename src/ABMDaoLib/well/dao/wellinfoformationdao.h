#ifndef WELLINFOFORMATIONDAO_H
#define WELLINFOFORMATIONDAO_H

#include "../entity/wellinfoformation.h"
#include "../../common/mysql/SqlUtils.h"

/**
 * @brief The SQL_PAGE struct 分页查询返回结构体
 */
struct WellInfoFormationPage
{
  int pageNum;
  int pageSize;
  int totalPage;
  QList<QSharedPointer<WellInfoFormation>> dataList;
};

class WellInfoFormationDao
{
public:
  WellInfoFormationDao();
  //新增井信息 Distance 信息
  bool add(QSharedPointer<WellInfoFormation> entity);
  //修改井信息 Distance 信息
  bool updateById(QSharedPointer<WellInfoFormation> entity);
  //批量查询井信息 Distance 集合
  QList<QSharedPointer<WellInfoFormation> > findList(QVector<SqlCondition> &conditions);
  //分页查询井信息 Distance 集合
  WellInfoFormationPage findPage(QVector<SqlCondition> &conditions, const int pageSize, const int pageNum);
  //根据id查询
  QSharedPointer<WellInfoFormation> findById(int id);
  //根据wellInfoId查询
  QList<QSharedPointer<WellInfoFormation> > findByWellInfoId(int wellInfoId);

private:
  QString m_tableName = "u_well_formation";

};

#endif // WELLINFOFORMATIONDAO_H
