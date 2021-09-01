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

#ifndef SRC_SAMPLES_FILTER_DECODER_HIGHFREQUENCYSENSIVITYDECODER_H_
#define SRC_SAMPLES_FILTER_DECODER_HIGHFREQUENCYSENSIVITYDECODER_H_

#include "manchesterdecoder.h"
#include <deque>
#include <string>
#include <memory>
#include <vector>

class HighFrequencySensivityDecoder : public ManchesterDecoder {
 public:
  HighFrequencySensivityDecoder();
  virtual ~HighFrequencySensivityDecoder();
  bool decodeBeforeWait(std::shared_ptr<std::vector<float>> data) override;
  bool decodeAfterWait() override;
  configuru::Config defaultParams() override;
  bool reset() override;

 private:
  int m_match_alpha;
  int m_matchClockFrequency;
  int count;
  int init_wait;
  bool ct_tag;
  std::shared_ptr<std::vector<float>> s_tmpBuffer;
};

#endif  // SRC_SAMPLES_FILTER_DECODER_HIGHFREQUENCYSENSIVITYDECODER_H_
