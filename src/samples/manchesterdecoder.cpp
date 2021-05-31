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
_resualt_mem_size_tag(_resualt->size()) {
}

ManchesterDecoder::~ManchesterDecoder() {
}

char ManchesterDecoder::getCurrentResualt() {
  if (_resualt && _resualt_mem_size_tag != _resualt->size()) {
    _resualt_mem_size_tag = _resualt->size();
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
