#include "currentdatadao.h"

#include "../../abmdaolib.h"

//CurrentDataDao::CurrentDataDao()
//{

//}

//bool CurrentDataDao::add(QSharedPointer<CurrentData> entity)
//{
//  QMap<QString, QVariant> map = entity->toMap();

//  if(ABMDaoLib::getInstance()->getSqlUtils()->insertValue(m_tableName,map)){
//    return true;
//  }else{
//    return false;
//  }
//}

//bool CurrentDataDao::updateByKey(QSharedPointer<CurrentData> entity)
//{
//  if(entity->getKey().isEmpty()){
//    qDebug() << "key 不能为空";
//    return false;
//  }
//  QMap<QString, QVariant> map = entity->toMap();
//  QVector<SqlCondition> conditions;
//  SqlCondition eqId(SqlOperator::SqlEqual,"key",entity->getKey());
//  conditions.append(eqId);
//  return ABMDaoLib::getInstance()->getSqlUtils()->updateValue(m_tableName,map,conditions);
//}

//QList<QSharedPointer<CurrentData> > CurrentDataDao::findList(QVector<SqlCondition> &conditions)
//{
//  QList<QMap<QString,QVariant>> dataList;
//  ABMDaoLib::getInstance()->getSqlUtils()->queryDatas(m_tableName,conditions,dataList);

//  QList<QSharedPointer<CurrentData>> list;
//  for(int i=0;i<dataList.size();i++){
//    QSharedPointer<CurrentData> entity = QSharedPointer<CurrentData>(new CurrentData());
//    for(auto it = dataList.at(i).cbegin(); it != dataList.at(i).cend(); ++it){
//      entity->setProperty(it.key().toLocal8Bit(),it.value());
//    }
//    list.append(entity);
//  }
//  return list;
//}

//QSharedPointer<CurrentData> CurrentDataDao::findByKey(QString key)
//{
//  QVector<SqlCondition> conditions;
//  conditions.append(SqlCondition(SqlEqual,"key",key));
//  QMap<QString,QVariant> resultData;

//  QSharedPointer<CurrentData> entity = QSharedPointer<CurrentData>(new CurrentData());

//  if(!ABMDaoLib::getInstance()->getSqlUtils()->queryOne(m_tableName,conditions,resultData)){
//    return entity;
//  }

//  for(auto it = resultData.cbegin(); it != resultData.cend(); ++it){
//    entity->setProperty(it.key().toLocal8Bit(),it.value());
//  }
//  return entity;
//}

//QList<QSharedPointer<CurrentData>> CurrentDataDao::findByModel(QString model)
//{
//  QVector<SqlCondition> conditions;
//  conditions.append(SqlCondition(SqlEqual,"model",model));

//  QList<QMap<QString,QVariant>> dataList;
//  ABMDaoLib::getInstance()->getSqlUtils()->queryDatas(m_tableName,conditions,dataList);

//  QList<QSharedPointer<CurrentData>> list;
//  for(int i=0;i<dataList.size();i++){
//    QSharedPointer<CurrentData> entity = QSharedPointer<CurrentData>(new CurrentData());
//    for(auto it = dataList.at(i).cbegin(); it != dataList.at(i).cend(); ++it){
//      entity->setProperty(it.key().toLocal8Bit(),it.value());
//    }
//    list.append(entity);
//  }
//  return list;
//}

