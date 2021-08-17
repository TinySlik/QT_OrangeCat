#ifndef WELLINFOGENERALDAO_H
#define WELLINFOGENERALDAO_H

#include "../entity/wellinfogeneral.h"
#include "../../common/mysql/SqlUtils.h"

/**
 * @brief The SQL_PAGE struct 分页查询返回结构体
 */
struct WellInfoGeneralPage
{
  int pageNum;
  int pageSize;
  int totalPage;
  QList<QSharedPointer<WellInfoGeneral>> dataList;
};

class WellInfoGeneralDao
{
public:

  WellInfoGeneralDao();
  //新增井信息General信息
  bool add(QSharedPointer<WellInfoGeneral> entity);
  //修改井信息General信息
  bool updateById(QSharedPointer<WellInfoGeneral> entity);
  //批量查询井信息General集合
  QList<QSharedPointer<WellInfoGeneral> > findList(QVector<SqlCondition> &conditions);
  //分页查询井信息General集合
  WellInfoGeneralPage findPage(QVector<SqlCondition> &conditions, const int pageSize, const int pageNum);
  //根据id查询
  QSharedPointer<WellInfoGeneral> findById(int id);
  //根据wellId查询
  QSharedPointer<WellInfoGeneral> findByWellId(QString wellId);

private:
  QString m_tableName = "u_well_info";
};

#endif // WELLINFOGENERALDAO_H
