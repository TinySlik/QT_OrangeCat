#ifndef JYTEKAI_H
#define JYTEKAI_H

#include "usbdask.h"
#include "JytekAiDataProcess.h"
#include <map>
#include <vector>

#ifndef MAX_CHAN_2405
#define MAX_CHAN_2405	4
#endif

#ifndef AI_SAMPLE_COUNT
#define AI_SAMPLE_COUNT	512
#endif

class adlink;

class JytekAi {
  explicit JytekAi();
  ~JytekAi();

  /**
   * @brief setCardId
   * @param id
   */
  void setCardId(const I16 &id);

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
  std::map<U16, std::vector<double>> getTransferDatas();

protected:
  void run();

private:
  bool m_stop;
  bool m_saveFile;

  I16 cardNum;

  U16  m_wSelectedChans;
  U16  m_wGain[MAX_CHAN_2405];
  std::vector<U16>  m_wChan;
  std::vector<U32>  m_pAIBuf;
  double m_fSampleRate;
  std::shared_ptr<std::thread> m_task;

  JytekAiDataProcess m_dataProcess;
  friend adlink;
};


#endif // JYTEKAI_H
