#include "welldao.h"
#define CONFIGURU_IMPLEMENTATION 1
#include "configuru.hpp"
//#include "../entity/wellinfodepthstatus.h"
#include <iostream>
#include "../../abmdaolib.h"

WellDao::WellDao(){
}

bool WellDao::add(const std::string &json) {
  auto data = configuru::parse_string(json.c_str(), configuru::JSON, nullptr);
  _mutex.lock();
  _mutex.unlock();
  return false;
}

bool WellDao::update(const std::string &json) {
  auto data = configuru::parse_string(json.c_str(), configuru::JSON, nullptr);
  _mutex.lock();
  _mutex.unlock();
  return false;
}

std::string WellDao::find(const std::string &json) {
  auto data = configuru::parse_string(json.c_str(), configuru::JSON, nullptr);
  _mutex.lock();
  if (data.has_key("target_table") &&
      data["target_table"].is_object() &&
      data["target_table"].has_key("name") &&
      data["target_table"]["name"].is_string()) {
    auto local_table = data["target_table"];
    auto name = std::string(local_table["name"]);
    QVector<SqlCondition> conditions;
    QMap<QString,QVariant> resultData;
    std::cout << data;
    for (auto& p : local_table.as_object()) {
        std::cout << "\tKey: " << p.key() << std::endl;
        std::cout << "\tValue: " << p.value() << std::endl;
        p.value() = "new value";
        if(!ABMDaoLib::getInstance()->getSqlUtils()->queryOne(name.c_str(), conditions, resultData))
          return "{}";

//        conditions.append(SqlCondition(SqlEqual, p.key(), p.value()));
        std::cout.flush();
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
