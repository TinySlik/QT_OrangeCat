#include "wellinfosurveyinfoDao.h"
#include "../../abmdaolib.h"

WellInfoSurveyInfoDao::WellInfoSurveyInfoDao()
{

}

bool WellInfoSurveyInfoDao::add(QSharedPointer<WellInfoSurveyInfo> entity)
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

bool WellInfoSurveyInfoDao::updateById(QSharedPointer<WellInfoSurveyInfo> entity)
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

QList<QSharedPointer<WellInfoSurveyInfo> > WellInfoSurveyInfoDao::findList(QVector<SqlCondition> &conditions)
{
  QList<QMap<QString,QVariant>> dataList;
  ABMDaoLib::getInstance()->getSqlUtils()->queryDatas(m_tableName,conditions,dataList);

  QList<QSharedPointer<WellInfoSurveyInfo>> list;
  for(int i=0;i<dataList.size();i++){
    QSharedPointer<WellInfoSurveyInfo> entity = QSharedPointer<WellInfoSurveyInfo>(new WellInfoSurveyInfo());
    for(auto it = dataList.at(i).cbegin(); it != dataList.at(i).cend(); ++it){
      entity->setProperty(it.key().toLocal8Bit(),it.value());
    }
    list.append(entity);
  }
  return list;
}

WellInfoSurveyInfoPage WellInfoSurveyInfoDao::findPage(QVector<SqlCondition> &conditions, const int pageSize, const int pageNum)
{
  WellInfoSurveyInfoPage page;
  SqlPage sqlPage;
  ABMDaoLib::getInstance()->getSqlUtils()->queryPage(m_tableName,conditions,pageSize, pageNum,sqlPage);
  QList<QSharedPointer<WellInfoSurveyInfo>> list;
  for(int i=0;i<sqlPage.dataList.size();i++){
    QSharedPointer<WellInfoSurveyInfo> entity = QSharedPointer<WellInfoSurveyInfo>(new WellInfoSurveyInfo());
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

QSharedPointer<WellInfoSurveyInfo> WellInfoSurveyInfoDao::findById(int id)
{
  QVector<SqlCondition> conditions;
  conditions.append(SqlCondition(SqlEqual,"id",id));
  conditions.append(SqlCondition(SqlEqual,"is_del",0));
  QMap<QString,QVariant> resultData;

  QSharedPointer<WellInfoSurveyInfo> entity = QSharedPointer<WellInfoSurveyInfo>(new WellInfoSurveyInfo());

  if(!ABMDaoLib::getInstance()->getSqlUtils()->queryOne(m_tableName,conditions,resultData)){
    return entity;
  }

  for(auto it = resultData.cbegin(); it != resultData.cend(); ++it){
    entity->setProperty(it.key().toLocal8Bit(),it.value());
  }
  return entity;
}

QSharedPointer<WellInfoSurveyInfo> WellInfoSurveyInfoDao::findByWellInfoId(int wellInfoId)
{
  QVector<SqlCondition> conditions;
  conditions.append(SqlCondition(SqlEqual,"well_info_id",wellInfoId));
  conditions.append(SqlCondition(SqlEqual,"is_del",0));
  QMap<QString,QVariant> resultData;

  QSharedPointer<WellInfoSurveyInfo> entity = QSharedPointer<WellInfoSurveyInfo>(new WellInfoSurveyInfo());
  if(!ABMDaoLib::getInstance()->getSqlUtils()->queryOne(m_tableName,conditions,resultData)){
    return entity;
  }

  for(auto it = resultData.cbegin(); it != resultData.cend(); ++it){
    entity->setProperty(it.key().toLocal8Bit(),it.value());
  }
  return entity;
}
