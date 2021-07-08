#ifndef JYTEKAIDATAPROCESS_H
#define JYTEKAIDATAPROCESS_H

#include "usbdask.h"
#include <map>
#include <vector>
#include <mutex>
#include <queue>
class JytekAi;

class JytekAiDataProcess {
  explicit JytekAiDataProcess();
  ~JytekAiDataProcess();

  /**
   * @brief startProcess    开始数据处理
   * @param wSelectedChans  采集通道数
   * @param wChan           采集通道数组
   */
  void startProcess(const U16 &wSelectedChans, const std::vector<U16> wChan);

  /**
   * @brief stopProcess 停止处理
   */
  void stopProcess();

  /**
   * @brief addBuf  添加采集数据
   * @param buf     采集数据
   * @param size    大小
   */
  void addBuf(const std::vector<U32> buf, const int &size);

  /**
   * @brief getTransferDatas  获取已转换数据
   * @return
   */
  std::map<U16, std::vector<double>> getTransferDatas();

protected:
  void run();
private:
  void clearData();
  bool m_stop;
  std::mutex m_dataProcessMutex;
  std::mutex m_dataTransferMutex;

  U16  m_wSelectedChans;
  std::vector<U16>  m_wChan;

  std::queue<std::vector<U32>> m_bufs;
  std::map<U16, std::vector<double>> m_transferDatas;
  friend JytekAi;
};

#endif // JYTEKAIDATAPROCESS_H
