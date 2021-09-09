#ifndef RUNINFOMATCHEDSYSTEMSTRACKINGDAO_H
#define RUNINFOMATCHEDSYSTEMSTRACKINGDAO_H

#include "../entity/runinfomatchedsystemstracking.h"
#include "../../common/mysql/SqlUtils.h"

///**
// * @brief The SQL_PAGE struct 分页查询返回结构体
// */
//struct RunInfoMatchedSystemsTrackingPage
//{
//  int pageNum;
//  int pageSize;
//  int totalPage;
//  QList<QSharedPointer<RunInfoMatchedSystemsTracking>> dataList;
//};

//class RunInfoMatchedSystemsTrackingDao
//{
//public:
//  RunInfoMatchedSystemsTrackingDao();
//  //新增运行号信息 MatchedSystemsTracking 信息
//  bool add(QSharedPointer<RunInfoMatchedSystemsTracking> entity);
//  //修改运行号信息 MatchedSystemsTracking 信息
//  bool updateById(QSharedPointer<RunInfoMatchedSystemsTracking> entity);
//  //批量查询运行号信息 MatchedSystemsTracking 集合
//  QList<QSharedPointer<RunInfoMatchedSystemsTracking> > findList(QVector<SqlCondition> &conditions);
//  //分页查询运行号信息 MatchedSystemsTracking 集合
//  RunInfoMatchedSystemsTrackingPage findPage(QVector<SqlCondition> &conditions, const int pageSize, const int pageNum);
//  //根据id查询
//  QSharedPointer<RunInfoMatchedSystemsTracking> findById(int id);
//  //根据runInfoId查询
//  QSharedPointer<RunInfoMatchedSystemsTracking> findByRunInfoId(int runInfoId);

//private:
//  QString m_tableName = "u_run_matched_systems_tracking";
//};

#endif // RUNINFOMATCHEDSYSTEMSTRACKINGDAO_H
