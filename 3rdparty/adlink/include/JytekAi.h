#ifndef JYTEKAI_H
#define JYTEKAI_H

#include "usbdask.h"
#include "JytekAiDataProcess.h"
#include <map>
#include <vector>
#include <memory>

#ifndef MAX_CHAN_2405
#define MAX_CHAN_2405	4
#endif

#ifndef AI_SAMPLE_COUNT
#define AI_SAMPLE_COUNT	256
#endif

class adlink;

class JytekAi {
  using callback_adlink_t = std::function<void(std::shared_ptr<std::vector<unsigned char>>)>;
  typedef struct remote_unit {
    bool enable;
    callback_adlink_t callback;
    bool isNeedCallback() {
      return enable && callback;
    }
  } REMOTE_UNIT;
  explicit JytekAi();
  ~JytekAi();

  bool setRawDataCallback(callback_adlink_t callback);
  inline bool setRawDataCallback1(callback_adlink_t callback) {
    if (m_remotes.size() == 4) {
      m_remotes[0].callback = callback;
      return true;
    }
    return false;
  }
  inline bool setRawDataCallback2(callback_adlink_t callback) {
    if (m_remotes.size() == 4) {
      m_remotes[1].callback = callback;
      return true;
    }
    return false;
  }
  inline bool setRawDataCallback3(callback_adlink_t callback) {
    if (m_remotes.size() == 4) {
      m_remotes[2].callback = callback;
      return true;
    }
    return false;
  }
  inline bool setRawDataCallback4(callback_adlink_t callback){
    if (m_remotes.size() == 4) {
      m_remotes[3].callback = callback;
      return true;
    }
    return false;
  }

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
  std::vector<REMOTE_UNIT> m_remotes;
  callback_adlink_t raw_callback_func;
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
