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


ManchesterDecoder::ManchesterDecoder():
_resualt(nullptr),
_displayBuffer(nullptr) {
}

ManchesterDecoder::~ManchesterDecoder() {
}

char ManchesterDecoder::getCurrentResualt() {
  if (_resualt && _resualt->size() > 0) {
    return *(_resualt->begin());
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
