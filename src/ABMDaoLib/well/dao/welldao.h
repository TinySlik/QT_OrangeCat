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

/** dao interface demo

// find
auto jsonInterface = ABMDaoLib::getInstance()->getJsonInterface();
configuru::Config cfg = {{"target_table", {
    {"name", "u_well_depth_status"},
    {"wellId", "001"}
  }}
};
auto js = jsonInterface->find(dump_string(cfg, configuru::JSON).c_str());
auto res = configuru::parse_string(js.c_str(),configuru::JSON, "null");

// update
res["drilling"] = 2.0;
configuru::Config updateval = {
  {"target_table", "u_well_depth_status"},
  {"update_val", res},
  {"index_val", {{"wellId", res["wellId"]}}}
};

jsonInterface->update(dump_string(updateval, configuru::JSON).c_str());

// insert
res["wellId"] = "002";
configuru::Config insertval = {
  {"target_table", "u_well_depth_status"},
  {"insert_val", res},
};
jsonInterface->add(dump_string(insertval, configuru::JSON).c_str());


// create table
configuru::Config cfg_create_table_sample = {
  {"target_table", "hello"},
  {"design_map", {{"kkk", "string"}, {"lll", "int"}}},
  {"primary_key", "kkk"}
};
if (ABMDaoLib::getInstance()->getWellJsonInterface()->createTable((dump_string(cfg_create_table_sample, configuru::JSON).c_str()))) {
  LOG(INFO) << "success";
}

// create datebase
if (ABMDaoLib::createDataBase("bingo")) {
  LOG(INFO) << "bingo";
}
*/

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
