#include "JytekDIO.h"
#include <iostream>
#include <thread>
#include <chrono>

JytekDIO::JytekDIO() {
  m_channel0 = false;
  m_channel1 = false;
}

JytekDIO::~JytekDIO() {
  this->stopDIO();
}

void JytekDIO::setCardId(const I16 &id) {
  cardNum = id;
}

void JytekDIO::startDIO(const bool &channel0, const bool &channel1) {
  m_channel0 = channel0;
  m_channel1 = channel1;

  m_stop = false;

//  this->start();
}

void JytekDIO::stopDIO() {
  m_stop = true;
//  this->wait();

  dataMutex.lock();
  m_datas.clear();
  dataMutex.unlock();
}

std::map<int, std::vector<bool>> JytekDIO::getDioDatas() {
  dataMutex.lock();

  std::map<int, std::vector<bool>> tempData = m_datas;
  m_datas.clear();
  dataMutex.unlock();

  return tempData;
}

void JytekDIO::run() {
  while(!m_stop) {
    if(m_channel0) {
      U16 wTemp;
      I16 nErr = UD_DI_ReadLine ( cardNum, 0, 0, &wTemp );

      if(nErr != DaqNoError) {
        std::cout  << "UD_DI_ReadLine error 0 " << nErr << std::endl;
        std::cout.flush();
        break;
      } else {
        dataMutex.lock();
        m_datas[0].push_back(wTemp);
        dataMutex.unlock();
      }
    }

    if(m_channel1) {
      U16 wTemp;
      I16 nErr = UD_DI_ReadLine ( cardNum, 1, 0, &wTemp );

      if(nErr != DaqNoError) {
        std::cout  << "UD_DI_ReadLine error 1 " << nErr << std::endl;
        std::cout.flush();
        break;
      } else {
        dataMutex.lock();
        m_datas[1].push_back(wTemp);
        dataMutex.unlock();
      }
    }
    std::this_thread::sleep_for(std::chrono::microseconds(1));
  }
}
