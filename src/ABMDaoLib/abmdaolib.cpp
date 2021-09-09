#include "abmdaolib.h"
#include "common/log/easylogging++.h"
#include <memory>
#include <QtCore/qglobal.h>
#include "common/mysql/SqlUtils.h"
#pragma execution_character_set("utf-8")
INITIALIZE_EASYLOGGINGPP

class ABMDaoLibPrivate {
 public:
  ~ABMDaoLibPrivate() {
  }
  ABMDaoLibPrivate() {
  }
  std::shared_ptr<SqlUtils> getSqlUtils() const;
  void setSqlUtils(const std::shared_ptr<SqlUtils> &sqlUtils);
  std::shared_ptr<WellDaoJsonInterface> getJsonInterface();
  std::shared_ptr<WellDaoJsonInterface> getWellJsonInterface();
  std::shared_ptr<WellDaoJsonInterface> getRunJsonInterface();
  bool open(const std::string well, const std::string run, const std::string userName = "root", const std::string password = "123456", const std::string host = "192.168.1.171");
  void close();
  std::shared_ptr<SqlUtils> getWellSqlUtils() const;
  std::shared_ptr<SqlUtils> getRunSqlUtils() const;
  void setRunSqlUtils(const std::shared_ptr<SqlUtils> sqlUtils);
  void setWellSqlUtils(const std::shared_ptr<SqlUtils> sqlUtils);
 private:
  std::shared_ptr<SqlUtils> m_sqlUtils;
  std::shared_ptr<SqlUtils> m_wellUtils;
  std::shared_ptr<SqlUtils> m_runUtils;
};

ABMDaoLib *ABMDaoLib::getInstance() {
  static ABMDaoLib *instance = nullptr;
  if (instance == nullptr) {
    instance = new ABMDaoLib();
  }
  return instance;
}

bool ABMDaoLib::createDataBase(const std::string &name) {
  auto sql_ = SqlUtils::create(SqlLocationType::SqlSys, "","root","123456","192.168.1.171");
  return sql_->createDatabase(name);
}

ABMDaoLib::~ABMDaoLib(){
  if (_impl) delete _impl;
}

ABMDaoLib::ABMDaoLib(): _impl(nullptr)  {
  _impl = new ABMDaoLibPrivate();
}

std::shared_ptr<SqlUtils> ABMDaoLibPrivate::getSqlUtils() const {
  return m_sqlUtils;
}

void ABMDaoLibPrivate::setSqlUtils(const std::shared_ptr<SqlUtils> &sqlUtils) {
  m_sqlUtils = sqlUtils;
}

std::shared_ptr<SqlUtils> ABMDaoLibPrivate::getWellSqlUtils() const {
  return m_wellUtils;
}

std::shared_ptr<SqlUtils> ABMDaoLibPrivate::getRunSqlUtils() const {
  return m_runUtils;
}

void ABMDaoLibPrivate::setRunSqlUtils(const std::shared_ptr<SqlUtils> sqlUtils) {
  m_runUtils = sqlUtils;
}

void ABMDaoLibPrivate::setWellSqlUtils(const std::shared_ptr<SqlUtils> sqlUtils) {
  m_wellUtils = sqlUtils;
}


std::shared_ptr<WellDaoJsonInterface> ABMDaoLib::getJsonInterface() {
  return _impl->getJsonInterface();
}
std::shared_ptr<WellDaoJsonInterface> ABMDaoLib::getWellJsonInterface() {
  return _impl->getWellJsonInterface();
}
std::shared_ptr<WellDaoJsonInterface> ABMDaoLib::getRunJsonInterface() {
  return _impl->getRunJsonInterface();
}
bool ABMDaoLib::open(const std::string well, const std::string run, const std::string userName, const std::string password, const std::string host) {
  return _impl->open(well, run, userName, password, host);
}


std::shared_ptr<WellDaoJsonInterface> ABMDaoLibPrivate::getJsonInterface() {
  return getWellJsonInterface();
}

std::shared_ptr<WellDaoJsonInterface> ABMDaoLibPrivate::getRunJsonInterface() {
  static std::shared_ptr<WellDaoJsonInterface> jsonDaoInterface = nullptr;
  if(jsonDaoInterface == nullptr) {
    jsonDaoInterface = WellDaoJsonInterface::create(m_runUtils);
  }
  return jsonDaoInterface;
}

std::shared_ptr<WellDaoJsonInterface> ABMDaoLibPrivate::getWellJsonInterface() {
  static std::shared_ptr<WellDaoJsonInterface> jsonDaoInterface = nullptr;
  if(jsonDaoInterface == nullptr) {
    jsonDaoInterface = WellDaoJsonInterface::create(m_wellUtils);
  }
  return jsonDaoInterface;
}

bool ABMDaoLibPrivate::open(const std::string well, const std::string run, const std::string userName, const std::string password, const std::string host) {
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
