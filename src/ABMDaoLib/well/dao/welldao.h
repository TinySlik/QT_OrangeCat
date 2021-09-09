#ifndef WELLINFODEPTHSTATUSDAO_H
#define WELLINFODEPTHSTATUSDAO_H
#include "jsoninterface.h"

#include "../entity/wellinfodepthstatus.h"
#include "../../common/mysql/SqlUtils.h"
#include "../../windllsupport.h"
#include <vector>
#include <memory>
#include <mutex>
#include <string>

class CLASS_DECLSPEC WellDaoJsonInterface: public jsonInterface, public std::enable_shared_from_this<WellDaoJsonInterface> {

 public:
  virtual ~WellDaoJsonInterface();
  virtual bool add(const std::string &json);
  virtual bool update(const std::string &json);
  virtual std::string find(const std::string &json);
  virtual bool createTable(const std::string &content);
  virtual bool createDatabase(const std::string &name);
  static std::shared_ptr<WellDaoJsonInterface> create(std::shared_ptr<SqlUtils> util = nullptr);

 private:
  WellDaoJsonInterface();
  std::mutex _mutex;
  std::shared_ptr<SqlUtils> _util;
};

#endif // WELLINFODEPTHSTATUSDAO_H
