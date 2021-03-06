#include "welldao.h"
#define CONFIGURU_IMPLEMENTATION 1
#include "configuru.hpp"

//#include "../entity/wellinfodepthstatus.h"
#include <iostream>
#include <string>
#include "../../abmdaolib.h"
#include "common/log/easylogging++.h"


QVariant configToQval(const configuru::Config &a) {
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
const configuru::Config qvalToConfig(const QVariant &a) {
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
  configuru::Config res;
  if (a.type() == QVariant::Int) {
    res = a.toInt();
  } else if (a.type() == QVariant::String) {
    res = std::string(a.toString().toLatin1().data());
  } else if (a.type() == QVariant::Double) {
    res = a.toDouble();
  }
  return res;
}


WellDaoJsonInterface::WellDaoJsonInterface(){
}

WellDaoJsonInterface::~WellDaoJsonInterface(){
}

bool WellDaoJsonInterface::add(const std::string &json) {
  auto data = configuru::parse_string(json.c_str(), configuru::JSON, "null");
  bool res = false;
  _mutex.lock();
  if (data.has_key("target_table") &&
      data["target_table"].is_string() &&
      data.has_key("insert_val") &&
      data["insert_val"].is_object()) {
    auto name = std::string(data["target_table"]);
    QMap<QString, QVariant> mapInsert;
    for (auto& p : data["insert_val"].as_object()) {
        mapInsert[p.key().c_str()] = configToQval((p.value()));
    }
    res = ABMDaoLib::getInstance()->getSqlUtils()->insertValue(name.c_str(), mapInsert);
  }
  _mutex.unlock();
  return res;
}

bool WellDaoJsonInterface::update(const std::string &json) {
  auto data = configuru::parse_string(json.c_str(), configuru::JSON, "null");
  _mutex.lock();
  bool res = false;
  if (data.has_key("target_table") &&
      data["target_table"].is_string() &&
      data.has_key("index_val") &&
      data["index_val"].is_object() &&
      data.has_key("update_val") &&
      data["update_val"].is_object()) {
    auto name = std::string(data["target_table"]);
    QVector<SqlCondition> conditions;
    QMap<QString, QVariant> resultData;
    for (auto& p : data["index_val"].as_object()) {
        auto st = (std::string)(p.key());
        QString a = st.c_str();
        conditions.append(SqlCondition(SqlEqual, a, configToQval(p.value())));
    }
    QMap<QString, QVariant> mapUpdate;
    for (auto& p : data["update_val"].as_object()) {
        mapUpdate[p.key().c_str()] = configToQval((p.value()));
    }
    res = ABMDaoLib::getInstance()->getSqlUtils()->updateValue(name.c_str(), mapUpdate, conditions);
  }
  _mutex.unlock();
  return res;
}

std::string WellDaoJsonInterface::find(const std::string &json) {
  auto data = configuru::parse_string(json.c_str(), configuru::JSON, "null");
  _mutex.lock();
  configuru::Config res = configuru::Config::object();
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
      conditions.append(SqlCondition(SqlEqual, a, configToQval(p.value())));
    }
    if(!ABMDaoLib::getInstance()->getSqlUtils()->queryOne(name.c_str(), conditions, resultData)) {
      LOG(ERROR) << "not find target table!";
      _mutex.unlock();
      return "{}";
    }
    for(auto it = resultData.cbegin(); it != resultData.cend(); ++it){
      std::string str = it.key().toLocal8Bit().data();
      res.judge_with_create_key(str.c_str()) = qvalToConfig(it.value());
    }
  }
  _mutex.unlock();
  return dump_string(res, configuru::JSON).c_str();
}
