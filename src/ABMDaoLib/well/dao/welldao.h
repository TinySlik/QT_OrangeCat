#ifndef WELLINFODEPTHSTATUSDAO_H
#define WELLINFODEPTHSTATUSDAO_H
#include "jsoninterface.h"

#include "../entity/wellinfodepthstatus.h"
#include "../../common/mysql/SqlUtils.h"
#include "../../ABMDaoLib_global.h"
#include <vector>
#include <memory>
#include <mutex>
#include <string>

/** dao interface demo
auto jsonInterface = ABMDaoLib::getInstance()->getJsonInterface();
configuru::Config cfg = {{"target_table", {
    {"name", "u_well_depth_status"},
    {"wellId", "001"}
  }}
};
auto js = jsonInterface->find(dump_string(cfg, configuru::JSON).c_str());
auto res = configuru::parse_string(js.c_str(),configuru::JSON, "null");
res["drilling"] = 2.0;

configuru::Config updateval = {
  {"target_table", "u_well_depth_status"},
  {"update_val", res},
  {"index_val", {{"wellId", res["wellId"]}}}
};

jsonInterface->update(dump_string(updateval, configuru::JSON).c_str());

res["wellId"] = "002";
configuru::Config insertval = {
  {"target_table", "u_well_depth_status"},
  {"insert_val", res},
};

jsonInterface->add(dump_string(insertval, configuru::JSON).c_str());
*/

class ABMDAOLIB_EXPORT WellDaoJsonInterface: public jsonInterface, public std::enable_shared_from_this<WellDaoJsonInterface> {
 public:
  WellDaoJsonInterface();
  ~WellDaoJsonInterface();
  virtual bool add(const std::string &json);
  virtual bool update(const std::string &json);
  virtual std::string find(const std::string &json);
 private:
  std::mutex _mutex;
};

#endif // WELLINFODEPTHSTATUSDAO_H
