// Copyright (c) 2021 TiniOh
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
#include "adlink.h"
#include <iostream>

adlink::adlink() {
}

adlink::~adlink() {
  stopAI();
  stopDIO();
}

std::vector<uint16_t> adlink::getAvailCardID() {
  std::vector<uint16_t> returnVec;
  uint16_t wModuleNum;
  USBDAQ_DEVICE AvailModules[MAX_USB_DEVICE];

  int16_t nErr = UD_Device_Scan(&wModuleNum, AvailModules);

  if( nErr != DaqNoError ) {
    std::cout << "UD_Device_Scan() failed, error code = " << nErr << std::endl;
  } else {
    for(int i = 0; i < wModuleNum; ++i ) {
      if( AvailModules[i].wModuleType == USB_2405 ) {
        returnVec.push_back(AvailModules[i].wCardID);
      }
    }
  }

  return returnVec;
}

bool adlink::openCard(const uint16_t nCardID) {
  cardNum = UD_Register_Card(USB_2405,nCardID);
  if((cardNum < 0) || (cardNum > MAX_USB_DEVICE -1)) {
    std::cout << "Register_Card ERROR" << cardNum;
    std::cout.flush();
    return false;
  } else {
    std::cout << "Register_Card success" << cardNum;
    std::cout.flush();
    m_ai.setCardId(cardNum);
    m_dio.setCardId(cardNum);
    return true;
  }
}

bool adlink::startAI(const bool &channel0, const bool &channel1,
                     const bool &channel2, const bool &channel3,
                     const double &sampleRate, const bool &saveFile) {
  return m_ai.startAI(channel0, channel1, channel2, channel3, sampleRate, saveFile);
}

void adlink::stopAI() {
  m_ai.stopAI();
}

std::map<uint16_t, std::vector<double>> adlink::getTransferDatas() {
  return m_ai.getTransferDatas();
}

bool adlink::setRawDataCallback(callback_adlink_t callback) {
  m_ai.setRawDataCallback(callback);
  return true;
}

bool adlink::setRawDataCallback1(callback_adlink_t callback) {
  m_ai.setRawDataCallback1(callback);
  return true;
}

bool adlink::setRawDataCallback2(callback_adlink_t callback) {
  m_ai.setRawDataCallback2(callback);
  return true;
}

bool adlink::setRawDataCallback3(callback_adlink_t callback) {
  m_ai.setRawDataCallback3(callback);
  return true;
}

bool adlink::setRawDataCallback4(callback_adlink_t callback) {
  m_ai.setRawDataCallback4(callback);
  return true;
}


void adlink::startDIO(const bool &channel0, const bool &channel1) {
  m_dio.startDIO(channel0, channel1);
}

void adlink::stopDIO() {
  m_dio.stopDIO();
}

std::map<int, std::vector<bool>> adlink::getDioDatas() {
  return m_dio.getDioDatas();
}
