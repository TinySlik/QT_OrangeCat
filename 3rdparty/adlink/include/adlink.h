// Copyright (c) 2021 Tini Oh
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
#ifndef ADLINK_H
#define ADLINK_H

#include <vector>
#include <map>
#include <memory>
#include "windllsupport.h"
#include "usbdask.h"
#include "JytekAi.h"
#include "JytekDIO.h"

class CLASS_DECLSPEC adlink {
  using callback_adlink_t = std::function<void(std::shared_ptr<std::vector<unsigned char>>)>;
public:
  static adlink *instance() {
    static adlink *_this = nullptr;
    if (_this == nullptr) {
      _this = new adlink;
    }
    return _this;
  }

  bool setRawDataCallback(callback_adlink_t callback);
  bool setRawDataCallback1(callback_adlink_t callback);
  bool setRawDataCallback2(callback_adlink_t callback);
  bool setRawDataCallback3(callback_adlink_t callback);
  bool setRawDataCallback4(callback_adlink_t callback);

  /**
   * @brief getAvailCardID  获取可用设备
   * @return
   */
  std::vector<uint16_t> getAvailCardID();

  /**
   * @brief openCard 打开板卡
   * @param nCardID
   */
  bool openCard(const uint16_t nCardID);

  /**
   * @brief startAI     开始采集
   * @param channel0    通道0开/关
   * @param channel1
   * @param channel2
   * @param channel3
   * @param sampleRate 采样率
   */
  bool startAI(const bool &channel0, const bool &channel1, const bool &channel2, const bool &channel3,
               const double &sampleRate, const bool &saveFile = false);

  /**
   * @brief stopAI  停止采集
   */
  void stopAI();

  /**
   * @brief getTransferDatas  获取已采集数据
   * @return
   */
  std::map<uint16_t, std::vector<double>> getTransferDatas();

  void startDIO(const bool &channel0, const bool &channel1);

  void stopDIO();

  std::map<int, std::vector<bool>> getDioDatas();
  void registerCallFunc();
private:
  callback_adlink_t raw_callback_func;
  explicit adlink();
  ~adlink();
  int16_t cardNum;
  JytekAi m_ai;
  JytekDIO m_dio;
};

#endif // ADLINK_H
