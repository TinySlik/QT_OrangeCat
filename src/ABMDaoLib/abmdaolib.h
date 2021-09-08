#ifndef ABMDAOLIB_H
#define ABMDAOLIB_H

#include "ABMDaoLib_global.h"
#include "common/mysql/SqlUtils.h"
#include "well/dao/welldao.h"

#include <memory>

class ABMDAOLIB_EXPORT ABMDaoLib {
 public:
  static ABMDaoLib *getInstance();
  static bool createDataBase(const std::string &name);
  ~ABMDaoLib();
  ABMDaoLib();
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

#endif // ABMDAOLIB_H
