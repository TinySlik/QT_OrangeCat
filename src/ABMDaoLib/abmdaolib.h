#ifndef ABMDAOLIB_H
#define ABMDAOLIB_H

#include "windllsupport.h"
#include "well/dao/welldao.h"

#include <memory>
class ABMDaoLibPrivate;

#define ABMDAOLIB_USER_NAME "root"
#define ABMDAOLIB_PASSWORD "123456"
#define ABMDAOLIB_HOST "192.168.1.171"

/** dao interface demo easy readme
 *
//方便json字段解析使用的解析代码
#define CONFIGURU_IMPLEMENTATION 1 // call in cpp just once
#include "configuru.hpp"

// 使用一个名称创建数据库（目前名称格式well001 / well001_run0100） create datebase
if (ABMDaoLib::createDataBase("well001")) {
  LOG(INFO) << "bingo";
}

if (ABMDaoLib::createDataBase("well001_run0100")) {
  LOG(INFO) << "bingo";
}


// 使用一个名称创建数据库 well run with open
std::string well_name = "well001";
std::string run_name = "run0100";

bool res = ABMDaoLib::getInstance()->open(well_name.c_str(), run_name.c_str());
if (res) LOG(INFO) << "well: " << well_name << "--run: " << run_name << " success";


// 使用一个表单 create table
字段类型有  "bool" "int" "float" "double" "string" "date"
主键为map中一项，目前必设
configuru::Config cfg_create_table_sample = {
  {"target_table", "hello"},
  {"design_map", {{"kkk", "string"}, {"lll", "int"}}},
  {"primary_key", "kkk"}
};
if (ABMDaoLib::getInstance()->getWellJsonInterface()->createTable((dump_string(cfg_create_table_sample, configuru::JSON).c_str()))) {
  LOG(INFO) << "success";
}

// 查找 find
auto jsonInterface = ABMDaoLib::getInstance()->getJsonInterface();
configuru::Config cfg = {{"target_table", {
    {"name", "u_well_depth_status"},
    {"wellId", "001"}
  }}
};
auto js = jsonInterface->find(dump_string(cfg, configuru::JSON).c_str());
auto res = configuru::parse_string(js.c_str(),configuru::JSON, "null");

// 更新 update
res["drilling"] = 2.0;
configuru::Config updateval = {
  {"target_table", "u_well_depth_status"},
  {"update_val", res},
  {"index_val", {{"wellId", res["wellId"]}}}
};
jsonInterface->update(dump_string(updateval, configuru::JSON).c_str());

// 插入 insert
res["wellId"] = "002";
configuru::Config insertval = {
  {"target_table", "u_well_depth_status"},
  {"insert_val", res},
};
jsonInterface->add(dump_string(insertval, configuru::JSON).c_str());
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
