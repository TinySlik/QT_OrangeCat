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

#include "msgdecoder.h"
using namespace configuru;
#include "easylogging++.h"

MsgDecoder::MsgDecoder(const std::string &decode_info) {
  std::string tmp = decode_info;
  decode_info_ = configuru::parse_string(tmp.c_str(), configuru::JSON, "null");
//  for (auto& v: decode_info_.as_array()) {
//    v["worklist"] = configuru::Config::array();
//    for (auto& vi: v["array"].as_array()) {
//      configuru::Config tmp = {{"code", vi}};
//      v["worklist"].push_back(tmp);
//    }
//    v.erase("array");
//  }
}

configuru::Config MsgDecoder::syncParams(configuru::Config &cfg) {
  return {};
}

MsgDecoder::~MsgDecoder() {
}

EmptyMsgDecoder::EmptyMsgDecoder(const std::string &decode_info):
MsgDecoder(decode_info) {
}

EmptyMsgDecoder::~EmptyMsgDecoder() {
}

bool EmptyMsgDecoder::decode(const bool &value) {
  return false;
}

bool EmptyMsgDecoder::reset() {
  return false;
  //
}

std::shared_ptr<MsgDecoder> EmptyMsgDecoder::create(const std::string &decode_info) {
  std::shared_ptr<EmptyMsgDecoder> res(new EmptyMsgDecoder(decode_info));
  return res;
}

configuru::Config EmptyMsgDecoder::defaultParams() {
  return {};
}
