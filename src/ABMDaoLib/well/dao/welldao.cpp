#include "welldao.h"
#define CONFIGURU_IMPLEMENTATION 1
#include "configuru.hpp"


//#include "../entity/wellinfodepthstatus.h"
#include <iostream>
#include <string>
#include "../../abmdaolib.h"
#include "common/log/easylogging++.h"


QVariant configToQval(const configtini::Config &a) {
  QVariant res = NULL;
  if (a.is_bool()) {
    auto tmp = bool(a);
    res = int(tmp);
  } else if (a.is_int()) {
    auto tmp = int(a);
    res = tmp;
  } else if (a.is_float()) {
    auto tmp = float(a);
    res = tmp;
  } else if (a.is_string()) {
    auto tmp = std::string(a);
    res = tmp.c_str();
  }
  return res;
}
const configtini::Config qvalToConfig(const QVariant &a) {
  /**
        Bool = QMetaType::Bool,
        Int = QMetaType::Int,
        UInt = QMetaType::UInt,
        LongLong = QMetaType::LongLong,
        ULongLong = QMetaType::ULongLong,
        Double = QMetaType::Double,
        Char = QMetaType::QChar,
        Map = QMetaType::QVariantMap,
        List = QMetaType::QVariantList,
        String = QMetaType::QString,
        StringList = QMetaType::QStringList,
        ByteArray = QMetaType::QByteArray,
        BitArray = QMetaType::QBitArray,
        Date = QMetaType::QDate,
        Time = QMetaType::QTime,
        DateTime = QMetaType::QDateTime,
    */
  configtini::Config res;
  if (a.type() == QVariant::Int) {
    res = a.toInt();
  } else if (a.type() == QVariant::String) {
    res = std::string(a.toString().toLatin1().data());
  } else if (a.type() == QVariant::Double) {
    res = a.toDouble();
  }
  return res;
}


WellDao::WellDao(){
  LOG(INFO) << __FUNCTION__;
}

WellDao::~WellDao(){
  LOG(INFO) << __FUNCTION__;
}

bool WellDao::add(const std::string &json) {
  auto data = configtini::parse_string(json.c_str(), configtini::JSON, nullptr);
  _mutex.lock();
  _mutex.unlock();
  return false;
}

bool WellDao::update(const std::string &json) {
  auto data = configtini::parse_string(json.c_str(), configtini::JSON, nullptr);
  _mutex.lock();
  if (data.has_key("target_table") &&
      data["target_table"].is_object() &&
      data["target_table"].has_key("name") &&
      data["target_table"]["name"].is_string()) {
    auto local_table = data["target_table"];
    auto name = std::string(local_table["name"]);
    QVector<SqlCondition> conditions;
    QMap<QString,QVariant> resultData;
    for (auto& p : local_table.as_object()) {
      if (p.key() == "name") continue;
      auto st = (std::string)(p.key());
      QString a = st.c_str();
//      auto stb = (std::string)(p.value());
//      QString b = stb.c_str();
      conditions.append(SqlCondition(SqlEqual, a, configToQval(p.value())));
    }
    if(!ABMDaoLib::getInstance()->getSqlUtils()->queryOne(name.c_str(), conditions, resultData)) {
      LOG(INFO) << "error";
      _mutex.unlock();
      return false;
    }
    for(auto it = resultData.cbegin(); it != resultData.cend(); ++it){
      qDebug() << "\tKey: " << it.key().toLocal8Bit();
      qDebug() << "\tValue: " << it.value();
    }
  }
  _mutex.unlock();
  return false;
}

std::string WellDao::find(const std::string &json) {
  auto data = configtini::parse_string(json.c_str(), configtini::JSON, "null");
  _mutex.lock();
  if (data.has_key("target_table") &&
      data["target_table"].is_object() &&
      data["target_table"].has_key("name") &&
      data["target_table"]["name"].is_string()) {
    auto local_table = data["target_table"];
    auto name = std::string(local_table["name"]);
    QVector<SqlCondition> conditions;
    QMap<QString,QVariant> resultData;
    for (auto& p : local_table.as_object()) {
      if (p.key() == "name") continue;
      LOG(INFO) << "\tKey: " << p.key();
      LOG(INFO) << "\tValue: " << p.value();
      auto st = (std::string)(p.key());
      QString a = st.c_str();
      conditions.append(SqlCondition(SqlEqual, a, configToQval(p.value())));
    }
    if(!ABMDaoLib::getInstance()->getSqlUtils()->queryOne(name.c_str(), conditions, resultData)) {
      LOG(INFO) << "error";
      _mutex.unlock();
      return "{}";
    }
    qDebug() << resultData.size();
    for(auto it = resultData.cbegin(); it != resultData.cend(); ++it){
      qDebug() << "\tKey: " << it.key().toLocal8Bit();
      qDebug() << "\tValue: " << it.value();
    }
  }


  _mutex.unlock();
//  conditions.append(SqlCondition(SqlEqual,"id",id));
//  QMap<QString,QVariant> resultData;

//  QSharedPointer<WellInfoGeneral> entity = QSharedPointer<WellInfoGeneral>(new WellInfoGeneral());

//  if(!ABMDaoLib::getInstance()->getSqlUtils()->queryOne(m_tableName,conditions,resultData)){
//    return entity;
//  }

//  for(auto it = resultData.cbegin(); it != resultData.cend(); ++it){
//    entity->setProperty(it.key().toLocal8Bit(),it.value());
//  }
//  return entity;

  return "{}";
}
