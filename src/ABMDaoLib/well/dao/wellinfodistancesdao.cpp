#include "wellinfodistancesdao.h"
#include "../../abmdaolib.h"

WellInfoDistancesDao::WellInfoDistancesDao()
{

}

bool WellInfoDistancesDao::add(QSharedPointer<WellInfoDistances> entity)
{
  QMap<QString, QVariant> map = entity->toMap();
  map.remove("id");
  if(ABMDaoLib::getInstance()->getSqlUtils()->insertValue(m_tableName,map)){
    entity->setId(map.value("id").toInt());
    return true;
  }else{
    return false;
  }
}

bool WellInfoDistancesDao::updateById(QSharedPointer<WellInfoDistances> entity)
{
  if(entity->getId() == 0){
    qDebug() << "id 不能为0";
    return false;
  }
  QMap<QString, QVariant> map = entity->toMap();
  QVector<SqlCondition> conditions;
  SqlCondition eqId(SqlOperator::SqlEqual,"id",entity->getId());
  conditions.append(eqId);
  return ABMDaoLib::getInstance()->getSqlUtils()->updateValue(m_tableName,map,conditions);
}

QList<QSharedPointer<WellInfoDistances> > WellInfoDistancesDao::findList(QVector<SqlCondition> &conditions)
{
  QList<QMap<QString,QVariant>> dataList;
  ABMDaoLib::getInstance()->getSqlUtils()->queryDatas(m_tableName,conditions,dataList);

  QList<QSharedPointer<WellInfoDistances>> list;
  for(int i=0;i<dataList.size();i++){
    QSharedPointer<WellInfoDistances> entity = QSharedPointer<WellInfoDistances>(new WellInfoDistances());
    for(auto it = dataList.at(i).cbegin(); it != dataList.at(i).cend(); ++it){
      entity->setProperty(it.key().toLocal8Bit(),it.value());
    }
    list.append(entity);
  }
  return list;
}

WellInfoDistancesPage WellInfoDistancesDao::findPage(QVector<SqlCondition> &conditions, const int pageSize, const int pageNum)
{
  WellInfoDistancesPage page;
  SqlPage sqlPage;
  ABMDaoLib::getInstance()->getSqlUtils()->queryPage(m_tableName,conditions,pageSize, pageNum,sqlPage);
  QList<QSharedPointer<WellInfoDistances>> list;
  for(int i=0;i<sqlPage.dataList.size();i++){
    QSharedPointer<WellInfoDistances> entity = QSharedPointer<WellInfoDistances>(new WellInfoDistances());
    for(auto it = sqlPage.dataList.at(i).cbegin(); it != sqlPage.dataList.at(i).cend(); ++it){
      entity->setProperty(it.key().toLocal8Bit(),it.value());
    }
    list.append(entity);
  }
  page.pageNum = sqlPage.pageNum;
  page.pageSize = sqlPage.pageSize;
  page.totalPage = sqlPage.totalPage;
  page.dataList = list;
  return page;
}

QSharedPointer<WellInfoDistances> WellInfoDistancesDao::findById(int id)
{
  QVector<SqlCondition> conditions;
  conditions.append(SqlCondition(SqlEqual,"id",id));
  conditions.append(SqlCondition(SqlEqual,"is_del",0));
  QMap<QString,QVariant> resultData;

  QSharedPointer<WellInfoDistances> entity = QSharedPointer<WellInfoDistances>(new WellInfoDistances());

  if(!ABMDaoLib::getInstance()->getSqlUtils()->queryOne(m_tableName,conditions,resultData)){
    return entity;
  }

  for(auto it = resultData.cbegin(); it != resultData.cend(); ++it){
    entity->setProperty(it.key().toLocal8Bit(),it.value());
  }
  return entity;
}

QSharedPointer<WellInfoDistances> WellInfoDistancesDao::findByWellInfoId(int wellInfoId)
{
  QVector<SqlCondition> conditions;
  conditions.append(SqlCondition(SqlEqual,"well_info_id",wellInfoId));
  conditions.append(SqlCondition(SqlEqual,"is_del",0));
  QMap<QString,QVariant> resultData;

  QSharedPointer<WellInfoDistances> entity = QSharedPointer<WellInfoDistances>(new WellInfoDistances());
  if(!ABMDaoLib::getInstance()->getSqlUtils()->queryOne(m_tableName,conditions,resultData)){
    return entity;
  }

  for(auto it = resultData.cbegin(); it != resultData.cend(); ++it){
    entity->setProperty(it.key().toLocal8Bit(),it.value());
  }
  return entity;
}
