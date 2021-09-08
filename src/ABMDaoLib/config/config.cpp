#include "config.h"
#include "../abmdaolib.h"

Config::Config()
{

}

//QString Config::getSystemWellId()
//{
//  return this->getCurrentData("wellId");
//}

//void Config::setSystemWellId(const QString &value)
//{
//  this->setCurrentData("wellId",value);
//}

//QString Config::getSystemRun()
//{
//  return this->getCurrentData("run");
//}

//void Config::setSystemRun(const QString &value)
//{
//  this->setCurrentData("run",value);
//}

//QString Config::getCurrentData(QString key)
//{
//  QSharedPointer<CurrentData> data = ABMDaoLib::getInstance()->getCurrentDataDao()->findByKey(key);
//  if(data->getKey().isEmpty()){
//    return nullptr;
//  }
//  return data->getValue();
//}

//bool Config::setCurrentData(QString key, QString value, QString model,QString remark)
//{
//  QSharedPointer<CurrentData> data = ABMDaoLib::getInstance()->getCurrentDataDao()->findByKey(key);
//  if(data->getKey().isEmpty()){
//    data->setModel(model);
//    data->setKey(key);
//    data->setValue(value);
//    if(remark != nullptr){
//      data->setRemark(remark);
//    }
//    return ABMDaoLib::getInstance()->getCurrentDataDao()->add(data);
//  }else{
//    data->setValue(value);
//    if(remark != nullptr){
//      data->setRemark(remark);
//    }
//    return ABMDaoLib::getInstance()->getCurrentDataDao()->updateByKey(data);
//  }
//}
