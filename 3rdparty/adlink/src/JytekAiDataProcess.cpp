#include "JytekAiDataProcess.h"
#include <list>

JytekAiDataProcess::JytekAiDataProcess() {
}

JytekAiDataProcess::~JytekAiDataProcess() {
  this->stopProcess();
}

void JytekAiDataProcess::startProcess(const U16 &wSelectedChans, const std::vector<U16> wChan) {
  m_stop = false;
  m_wSelectedChans = wSelectedChans;
  m_wChan = wChan;

//  this->start();
}

void JytekAiDataProcess::stopProcess() {
//  if(this->isRunning()) {
//    m_stop = true;
//    this->wait();
//  }

  clearData();
}

void JytekAiDataProcess::addBuf(const std::vector<U32> buf, const int &size)
{
  m_dataProcessMutex.lock();
//  m_bufs.enqueue(buf.mid(0,size));
//  m_bufs.emplace(buf.mid(0,size));
  m_dataProcessMutex.unlock();
}

std::map<U16, std::vector<double> > JytekAiDataProcess::getTransferDatas() {
  m_dataTransferMutex.lock();

  std::map<U16, std::vector<double>> tempData = m_transferDatas;
  m_transferDatas.clear();
  m_dataTransferMutex.unlock();

  return tempData;
}

void JytekAiDataProcess::run()
{
  while(!m_stop) {
    std::vector<U32> buf;

    m_dataProcessMutex.lock();
    if(!m_bufs.empty()) {
//      buf = m_bufs.dequeue();
    }
    m_dataProcessMutex.unlock();

    if(!buf.empty()) {
      //数据解析并转换成电压
      std::map<U16, std::vector<double>> datas;
      int bufSize = buf.size();

      for(int i = 0; i < bufSize; ++i) {
        U16 channel = m_wChan[i%m_wSelectedChans];

        U32 dwTemp = buf[i];
        if( dwTemp & 0x00800000 )
          dwTemp = (dwTemp | 0xFF000000);

        I32 ai_data = (I32)(dwTemp);
        double hv = ai_data * 1.1921*pow(10,-6);

        datas[channel].push_back(hv);
      }

      //数据存储
      m_dataTransferMutex.lock();

//      std::list<U16> keylist = datas.key_comp();
//      for(int i = 0; i < keylist.size(); ++i){
//        m_transferDatas[keylist[i]].append(datas[keylist[i]]);
//      }

      m_dataTransferMutex.unlock();
    }

//    QThread::msleep(1);
  }
}

void JytekAiDataProcess::clearData()
{
  m_dataProcessMutex.lock();
//  m_bufs.clear();
  m_dataProcessMutex.unlock();

  m_dataTransferMutex.lock();
  m_transferDatas.clear();
  m_dataTransferMutex.unlock();
}
