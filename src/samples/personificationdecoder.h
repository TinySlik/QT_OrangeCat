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

#ifndef PERSONIFICATIONDECODER_H
#define PERSONIFICATIONDECODER_H
#include "manchesterdecoder.h"
#include <deque>
#include <string>


class PersonificationDecoder : public ManchesterDecoder {
 public:
  PersonificationDecoder();
  virtual ~PersonificationDecoder() override;
  virtual bool decodeBeforeWait(std::shared_ptr<std::vector<float>> data) override;
  virtual bool decodeAfterWait() override;
  virtual configuru::Config defaultParams() override;

 private:
  int code_step1_trust_count;
  std::string m_code_step1_tmp_str;
  std::deque <unsigned char> m_code_step1_tmp;
  size_t m_code_step1_tmp_cur_head;
  size_t m_decode_step2_tmp_cur_head;
  int count;
  int init_wait;
  int count_case4;
  bool m_code_step1_tmp_start_tag = false;
  bool m_decode_step2_tmp_start_tag = false;
};

#endif // PERSONIFICATIONDECODER_H
