#ifndef WELLINFODEPTHSTATUSDAO_H
#define WELLINFODEPTHSTATUSDAO_H
#include "jsoninterface.h"

#include "../entity/wellinfodepthstatus.h"
#include "../../common/mysql/SqlUtils.h"
#include <vector>
#include <memory>
#include <mutex>

class WellDao: public jsonInterface, public std::enable_shared_from_this<WellDao> {
 public:
  WellDao();
  virtual bool add(const std::string &json);
  virtual bool update(const std::string &json);
  virtual std::string find(const std::string &json);
 private:
  std::mutex _mutex;
};

#endif // WELLINFODEPTHSTATUSDAO_H
