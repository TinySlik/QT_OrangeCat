/** Copyright 2021 Tiny Oh, Ltd. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#define CONFIGURU_IMPLEMENTATION 1
#include "parameterserver.h"
#include "easylogging++.h"
#include "gtest/gtest.h"
#include "ABMDaoLib/abmdaolib.h"
#define CONFIGURU_IMPLEMENTATION 1 // call in cpp just once
#include "configuru.hpp"

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

INITIALIZE_EASYLOGGINGPP

bool test_db_find() {
  std::string well_name = "well001";
  std::string run_name = "run0100";
  bool res = ABMDaoLib::getInstance()->open(well_name.c_str(), run_name.c_str());
  if (res) LOG(INFO) << "well: " << well_name << "--run: " << run_name << " success";
  if (!res) return false;


  // 查找 find
  std::shared_ptr<WellDaoInterface> jsonInterface = ABMDaoLib::getInstance()->getJsonInterface();
  configuru::Config cfg = {{"target_table", {
      {"name", "u_well_depth_status"},
      {"well_id", "001"}
    }}
  };
  std::string res_str = jsonInterface->find(dump_string(cfg, configuru::JSON).c_str());
  configuru::Config res_cfg = configuru::parse_string(res_str.c_str(),configuru::JSON, "null");
  std::string rr = static_cast<std::string>(res_cfg["well_id"]);
  return rr == "001";
}

class DBTest: public testing::Test {
 public:
  DBTest(){}
};

TEST_F(DBTest, find_record) {
  EXPECT_TRUE(test_db_find());
}


int main(int argc, char **argv) {

  LOG(INFO) << "unit test start:";
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
