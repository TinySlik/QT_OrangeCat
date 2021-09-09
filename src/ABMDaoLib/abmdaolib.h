#ifndef ABMDAOLIB_H
#define ABMDAOLIB_H

#include "windllsupport.h"
#include "well/dao/welldao.h"

#include <memory>
class ABMDaoLibPrivate;

#define ABMDAOLIB_USER_NAME "root"
#define ABMDAOLIB_PASSWORD "123456"
#define ABMDAOLIB_HOST "192.168.1.171"

/** dao interface demo
 *

#define CONFIGURU_IMPLEMENTATION 1 // call in cpp just once
#include "configuru.hpp"

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

class CLASS_DECLSPEC ABMDaoLib {
 public:
  static ABMDaoLib *getInstance();
  static bool createDataBase(const std::string &name);
  ~ABMDaoLib();
  ABMDaoLib();
  std::shared_ptr<WellDaoInterface> getJsonInterface();
  std::shared_ptr<WellDaoInterface> getWellJsonInterface();
  std::shared_ptr<WellDaoInterface> getRunJsonInterface();
  bool open(const std::string well, const std::string run,
            const std::string userName = ABMDAOLIB_USER_NAME,
            const std::string password = ABMDAOLIB_PASSWORD,
            const std::string host = ABMDAOLIB_HOST);
 private:
  ABMDaoLibPrivate *_impl;
};

#endif // ABMDAOLIB_H
