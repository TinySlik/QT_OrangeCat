#ifndef ABMDAOLIB_H
#define ABMDAOLIB_H

#include "windllsupport.h"
#include "well/dao/welldao.h"

#include <memory>
class ABMDaoLibPrivate;

class CLASS_DECLSPEC ABMDaoLib {
 public:
  static ABMDaoLib *getInstance();
  static bool createDataBase(const std::string &name);
  ~ABMDaoLib();
  ABMDaoLib();
  std::shared_ptr<WellDaoJsonInterface> getJsonInterface();
  std::shared_ptr<WellDaoJsonInterface> getWellJsonInterface();
  std::shared_ptr<WellDaoJsonInterface> getRunJsonInterface();
  bool open(const std::string well, const std::string run, const std::string userName = "root", const std::string password = "123456", const std::string host = "192.168.1.171");
 private:
  ABMDaoLibPrivate *_impl;
};

#endif // ABMDAOLIB_H
