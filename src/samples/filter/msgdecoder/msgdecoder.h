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

#ifndef MSGDECODER_H
#define MSGDECODER_H
#include <memory>
#include <vector>
#include "parameterserver.h"

class MsgDecoder: public std::enable_shared_from_this<MsgDecoder> {
 protected:
  explicit MsgDecoder();
 public:
  virtual bool decodeBeforeWait(const bool &value) = 0;
  virtual bool decodeAfterWait() =  0;
  virtual configuru::Config defaultParams() = 0;
  virtual bool reset() = 0;
  virtual std::shared_ptr<std::vector<float>> displayBuffer();
  virtual configuru::Config syncParams(configuru::Config &cfg);
  virtual ~MsgDecoder();
  virtual char getCurrentResualt();
  virtual const std::shared_ptr<std::vector<char>> getResualtList();

 protected:
  configuru::Config decode_info_;
};

class EmptyMsgDecoder : public MsgDecoder {
  EmptyMsgDecoder();
 public:
  virtual ~EmptyMsgDecoder() override;
  virtual bool decodeBeforeWait(const bool &valuedata) override;
  virtual bool decodeAfterWait() override;
  virtual configuru::Config defaultParams() override;
  virtual bool reset() override;
  static  std::shared_ptr<MsgDecoder> create(const std::string &decode_info);
};


#endif  // MSGDECODER_H
