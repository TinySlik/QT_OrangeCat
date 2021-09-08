#include "abmdaolib.h"
#include "common/log/easylogging++.h"
#include <memory>

#pragma execution_character_set("utf-8")
//初始化easilogging
INITIALIZE_EASYLOGGINGPP


ABMDaoLib *ABMDaoLib::getInstance() {
  static ABMDaoLib *instance = nullptr;
  if (instance == nullptr) {
    instance = new ABMDaoLib();
  }
  return instance;
}

ABMDaoLib::~ABMDaoLib() {
}

ABMDaoLib::ABMDaoLib() {
}

std::shared_ptr<SqlUtils> ABMDaoLib::getSqlUtils() const {
  return m_sqlUtils;
}

void ABMDaoLib::setSqlUtils(const std::shared_ptr<SqlUtils> &sqlUtils) {
  m_sqlUtils = sqlUtils;
}

std::shared_ptr<SqlUtils> ABMDaoLib::getWellSqlUtils() const {
  return m_wellUtils;
}

std::shared_ptr<SqlUtils> ABMDaoLib::getRunSqlUtils() const {
  return m_runUtils;
}

void ABMDaoLib::setRunSqlUtils(const std::shared_ptr<SqlUtils> sqlUtils) {
  m_runUtils = sqlUtils;
}

void ABMDaoLib::setWellSqlUtils(const std::shared_ptr<SqlUtils> sqlUtils) {
  m_wellUtils = sqlUtils;
}

std::shared_ptr<WellDaoJsonInterface> ABMDaoLib::getJsonInterface() {
  return getWellJsonInterface();
}

std::shared_ptr<WellDaoJsonInterface> ABMDaoLib::getRunJsonInterface() {
  static std::shared_ptr<WellDaoJsonInterface> jsonDaoInterface = nullptr;
  if(jsonDaoInterface == nullptr) {
    jsonDaoInterface = WellDaoJsonInterface::create(m_runUtils);
  }
  return jsonDaoInterface;
}

std::shared_ptr<WellDaoJsonInterface> ABMDaoLib::getWellJsonInterface() {
  static std::shared_ptr<WellDaoJsonInterface> jsonDaoInterface = nullptr;
  if(jsonDaoInterface == nullptr) {
    jsonDaoInterface = WellDaoJsonInterface::create(m_wellUtils);
  }
  return jsonDaoInterface;
}

bool ABMDaoLib::open(const std::string well, const std::string run, const std::string userName, const std::string password, const std::string host) {
  m_wellUtils = SqlUtils::create(SqlLocationType::SqlWell, well.c_str(), userName.c_str(), password.c_str(), host.c_str());
  m_runUtils = SqlUtils::create(SqlLocationType::SqlRun, (well + "_" + run).c_str(), userName.c_str(), password.c_str(), host.c_str());
  bool res = true;
  if (m_wellUtils)
      res &= m_wellUtils->connectDatabase();
  else return false;
  if (m_runUtils)
      res &= m_runUtils->connectDatabase();
  else return false;
  return res;
}

void ABMDaoLib::close() {
  if (m_wellUtils) {
    m_wellUtils->disconnect();
    m_wellUtils = nullptr;
  }

  if (m_runUtils) {
    m_runUtils->disconnect();
    m_runUtils = nullptr;
  }
}
