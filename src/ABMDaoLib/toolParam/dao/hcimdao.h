#ifndef HCIMDAO_H
#define HCIMDAO_H

#include "../entity/hcim.h"
#include "../../common/mysql/SqlUtils.h"

///**
// * @brief The SQL_PAGE struct 分页查询返回结构体
// */
//struct HCIMPage
//{
//  int pageNum;
//  int pageSize;
//  int totalPage;
//  QList<QSharedPointer<HCIM>> dataList;
//};

//class HCIMDao
//{
//public:
//  HCIMDao();
//  //新增
//  bool add(QSharedPointer<HCIM> entity);
//  //修改
//  bool updateById(QSharedPointer<HCIM> entity);
//  //批量查询
//  QList<QSharedPointer<HCIM> > findList(QVector<SqlCondition> &conditions);
//  //分页查询
//  HCIMPage findPage(QVector<SqlCondition> &conditions, const int pageSize, const int pageNum);
//  //根据id查询
//  QSharedPointer<HCIM> findById(int id);
//  //根据wellInfoId and runInfoId查询
//  QSharedPointer<HCIM> findByWellInfoId(int wellInfoId, int runInfoId);

//private:
//  QString m_tableName = "u_hcim";

//};

#endif // HCIMDAO_H
