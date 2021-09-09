#include "runinfomwdstatsdao.h"
#include "../../abmdaolib.h"

//RunInfoMWDStatsDao::RunInfoMWDStatsDao()
//{

//}

//bool RunInfoMWDStatsDao::add(QSharedPointer<RunInfoMwdStats> entity)
//{
//  QMap<QString, QVariant> map = entity->toMap();
//  map.remove("id");
//  if(ABMDaoLib::getInstance()->getSqlUtils()->insertValue(m_tableName,map)){
//    entity->setId(map.value("id").toInt());
//    return true;
//  }else{
//    return false;
//  }
//}

//bool RunInfoMWDStatsDao::updateById(QSharedPointer<RunInfoMwdStats> entity)
//{
//  if(entity->getId() == 0){
//    qDebug() << "id 不能为0";
//    return false;
//  }
//  QMap<QString, QVariant> map = entity->toMap();
//  QVector<SqlCondition> conditions;
//  SqlCondition eqId(SqlOperator::SqlEqual,"id",entity->getId());
//  conditions.append(eqId);
//  return ABMDaoLib::getInstance()->getSqlUtils()->updateValue(m_tableName,map,conditions);
//}

//QList<QSharedPointer<RunInfoMwdStats> > RunInfoMWDStatsDao::findList(QVector<SqlCondition> &conditions)
//{
//  QList<QMap<QString,QVariant>> dataList;
//  ABMDaoLib::getInstance()->getSqlUtils()->queryDatas(m_tableName,conditions,dataList);

//  QList<QSharedPointer<RunInfoMwdStats>> list;
//  for(int i=0;i<dataList.size();i++){
//    QSharedPointer<RunInfoMwdStats> entity = QSharedPointer<RunInfoMwdStats>(new RunInfoMwdStats());
//    for(auto it = dataList.at(i).cbegin(); it != dataList.at(i).cend(); ++it){
//      entity->setProperty(it.key().toLocal8Bit(),it.value());
//    }
//    list.append(entity);
//  }
//  return list;
//}

//RunInfoMwdStatsPage RunInfoMWDStatsDao::findPage(QVector<SqlCondition> &conditions, const int pageSize, const int pageNum)
//{
//  RunInfoMwdStatsPage page;
//  SqlPage sqlPage;
//  ABMDaoLib::getInstance()->getSqlUtils()->queryPage(m_tableName,conditions,pageSize, pageNum,sqlPage);
//  QList<QSharedPointer<RunInfoMwdStats>> list;
//  for(int i=0;i<sqlPage.dataList.size();i++){
//    QSharedPointer<RunInfoMwdStats> entity = QSharedPointer<RunInfoMwdStats>(new RunInfoMwdStats());
//    for(auto it = sqlPage.dataList.at(i).cbegin(); it != sqlPage.dataList.at(i).cend(); ++it){
//      entity->setProperty(it.key().toLocal8Bit(),it.value());
//    }
//    list.append(entity);
//  }
//  page.pageNum = sqlPage.pageNum;
//  page.pageSize = sqlPage.pageSize;
//  page.totalPage = sqlPage.totalPage;
//  page.dataList = list;
//  return page;
//}

//QSharedPointer<RunInfoMwdStats> RunInfoMWDStatsDao::findById(int id)
//{
//  QVector<SqlCondition> conditions;
//  conditions.append(SqlCondition(SqlEqual,"id",id));
//  conditions.append(SqlCondition(SqlEqual,"is_del",0));
//  QMap<QString,QVariant> resultData;

//  QSharedPointer<RunInfoMwdStats> entity = QSharedPointer<RunInfoMwdStats>(new RunInfoMwdStats());

//  if(!ABMDaoLib::getInstance()->getSqlUtils()->queryOne(m_tableName,conditions,resultData)){
//    return entity;
//  }

//  for(auto it = resultData.cbegin(); it != resultData.cend(); ++it){
//    entity->setProperty(it.key().toLocal8Bit(),it.value());
//  }
//  return entity;
//}

//QSharedPointer<RunInfoMwdStats> RunInfoMWDStatsDao::findByRunInfoId(int runInfoId)
//{
//  QVector<SqlCondition> conditions;
//  conditions.append(SqlCondition(SqlEqual,"run_info_id",runInfoId));
//  conditions.append(SqlCondition(SqlEqual,"is_del",0));
//  QMap<QString,QVariant> resultData;

//  QSharedPointer<RunInfoMwdStats> entity = QSharedPointer<RunInfoMwdStats>(new RunInfoMwdStats());
//  if(!ABMDaoLib::getInstance()->getSqlUtils()->queryOne(m_tableName,conditions,resultData)){
//    return entity;
//  }

//  for(auto it = resultData.cbegin(); it != resultData.cend(); ++it){
//    entity->setProperty(it.key().toLocal8Bit(),it.value());
//  }
//  return entity;
//}
