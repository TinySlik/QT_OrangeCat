#ifndef WELLINFODEPTHSTATUSDAO_H
#define WELLINFODEPTHSTATUSDAO_H
#include "jsoninterface.h"

#include "../../windllsupport.h"
#include <vector>
#include <memory>
#include <mutex>
#include <string>
class SqlUtils;

class CLASS_DECLSPEC WellDaoInterface: public jsonInterface, public std::enable_shared_from_this<WellDaoInterface> {

 public:
  virtual ~WellDaoInterface();
  virtual bool add(const std::string &json);
  virtual bool update(const std::string &json);
  virtual std::string find(const std::string &json);
  virtual bool createTable(const std::string &content);
  virtual bool createDatabase(const std::string &name);
  static std::shared_ptr<WellDaoInterface> create(std::shared_ptr<SqlUtils> util = nullptr);

 private:
  WellDaoInterface();
  std::mutex _mutex;
  std::shared_ptr<SqlUtils> _util;
};

#endif // WELLINFODEPTHSTATUSDAO_H
