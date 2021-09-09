#ifndef PCDDAO_H
#define PCDDAO_H

#include "../entity/pcd.h"
#include "../../common/mysql/SqlUtils.h"

///**
// * @brief The SQL_PAGE struct 分页查询返回结构体
// */
//struct PCDPage
//{
//  int pageNum;
//  int pageSize;
//  int totalPage;
//  QList<QSharedPointer<PCD>> dataList;
//};

//class PCDDao
//{
//public:
//  PCDDao();
//  //新增
//  bool add(QSharedPointer<PCD> entity);
//  //修改
//  bool updateById(QSharedPointer<PCD> entity);
//  //批量查询
//  QList<QSharedPointer<PCD> > findList(QVector<SqlCondition> &conditions);
//  //分页查询
//  PCDPage findPage(QVector<SqlCondition> &conditions, const int pageSize, const int pageNum);
//  //根据id查询
//  QSharedPointer<PCD> findById(int id);
//  //根据wellInfoId and runInfoId查询
//  QSharedPointer<PCD> findByWellInfoId(int wellInfoId, int runInfoId);

//private:
//  QString m_tableName = "u_pcd";

//};

#endif // PCDDAO_H
