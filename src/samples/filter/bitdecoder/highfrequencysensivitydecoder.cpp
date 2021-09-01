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
#include "highfrequencysensivitydecoder.h"
#include "easylogging++.h"
#include <memory>
#include <vector>

HighFrequencySensivityDecoder::HighFrequencySensivityDecoder():
m_match_alpha(50),
m_matchClockFrequency(100),
count(0),
init_wait(1024),
ct_tag(true),
s_tmpBuffer(nullptr) {}

HighFrequencySensivityDecoder::~HighFrequencySensivityDecoder()
{}

configuru::Config HighFrequencySensivityDecoder::defaultParams() {
  LOG(INFO) << __FUNCTION__ << __LINE__;
  return {};
}

bool HighFrequencySensivityDecoder::reset() {
  count = 0;
  init_wait = 1024;
  return true;
}

bool HighFrequencySensivityDecoder::decodeBeforeWait(std::shared_ptr<std::vector<float>> data) {
  auto cache = *data;

  float average = 0.f;
  auto sz = static_cast<int>(data->size());
  for (int i = 0; i < sz; i++) {
    average += (*data)[static_cast<size_t>(i)] / sz;
  }

  std::vector<int> tm;
  for (int i = 0; i < sz; i++) {
    static int count_i = 0;
    if ((*data)[static_cast<size_t>(i)] > average) {
      cache[static_cast<size_t>(i)] = 1.f;
    } else {
      cache[static_cast<size_t>(i)] = 0.f;
    }
    count_i++;
  }

  if (init_wait >= 0) init_wait--;
  count++;

  if (init_wait < 0 && count >= (m_matchClockFrequency - 1)) {
    for (int j = 0; j < sz / m_matchClockFrequency; j++) {
      int count_j = 0;
      for (int k = 0; k < m_matchClockFrequency; k++) {
        if (cache[static_cast<size_t>(j * m_matchClockFrequency + k + sz % m_matchClockFrequency)] > average) {
          count_j++;
        }
      }
      if (count_j > m_match_alpha) {
        for (int k = 0; k < m_matchClockFrequency; k++) {
          cache[static_cast<size_t>(j * m_matchClockFrequency + k + sz % m_matchClockFrequency)] = 1.f;
        }
      } else {
        for (int k = 0; k < m_matchClockFrequency; k++) {
          cache[static_cast<size_t>(j * m_matchClockFrequency + k + sz % m_matchClockFrequency)] = 0.f;
        }
      }
    }
    if (ct_tag) {
      if (cache[static_cast<size_t>(m_matchClockFrequency * 1.5 + sz % m_matchClockFrequency)] > .5f &&
          cache[static_cast<size_t>(m_matchClockFrequency * 2.5 + sz % m_matchClockFrequency)] < .5f) {
        _resualt->push_back('1');
      } else if (cache[static_cast<size_t>(m_matchClockFrequency * 1.5 + sz % m_matchClockFrequency)] < .5f &&
                 cache[static_cast<size_t>(m_matchClockFrequency * 2.5 + sz % m_matchClockFrequency)] > .5f) {
        _resualt->push_back('0');
      } else {
        _resualt->push_back('X');
        ct_tag = !ct_tag;
      }
    }
    ct_tag = !ct_tag;
    count = 0;
    s_tmpBuffer = std::make_shared<std::vector<float>>(cache);
  }
  if (!s_tmpBuffer) {
    _displayBuffer = std::make_shared<std::vector<float>>(cache);
  } else {
    _displayBuffer = s_tmpBuffer;
  }
  return true;
}

bool HighFrequencySensivityDecoder::decodeAfterWait() {
//  LOG(INFO) << __FUNCTION__ << __LINE__;
  return false;
}

