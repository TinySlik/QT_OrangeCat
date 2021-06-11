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

#include "manchesterdecoder.h"
using namespace configuru;
#include "easylogging++.h"

ManchesterDecoder::ManchesterDecoder():
_resualt(std::make_shared<std::vector<char>>()),
_displayBuffer(nullptr),
_resualtMemSizeTag(_resualt->size()) {
}

ManchesterDecoder::~ManchesterDecoder() {
}

char ManchesterDecoder::getCurrentResualt() {
  if (_resualt && _resualtMemSizeTag != _resualt->size()) {
    _resualtMemSizeTag = _resualt->size();
    return _resualt->back();
  }
  return -1;
}

const std::shared_ptr<std::vector<char>> ManchesterDecoder::getResualtList() {
  return _resualt;
}

configuru::Config ManchesterDecoder::syncParams(configuru::Config &cfg) {
  return cfg;
}

std::shared_ptr<std::vector<float>>  ManchesterDecoder::displayBuffer() {
  return _displayBuffer;
}

EmptyDefault::EmptyDefault() {}

EmptyDefault::~EmptyDefault()
{}

configuru::Config EmptyDefault::defaultParams() {
  LOG(INFO) << __FUNCTION__ << __LINE__;
  return {};
}

bool EmptyDefault::reset() {
  return true;
}

bool EmptyDefault::decodeBeforeWait(std::shared_ptr<std::vector<float>> data) {
//  auto cache = *data;

  _displayBuffer = data;
  return true;
}

bool EmptyDefault::decodeAfterWait() {
//  LOG(INFO) << __FUNCTION__ << __LINE__;
  return false;
}
