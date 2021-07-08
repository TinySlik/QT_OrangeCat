#include "JytekAi.h"
//#include <QDebug>
#include <iostream>
#include <thread>
#include <chrono>

static void callback_data(void) {
  std::cout << "hello bingo." << std::endl;
  std::cout.flush();
}

JytekAi::JytekAi() :
m_task(nullptr),
raw_callback_func(nullptr) {
  m_wChan  = std::vector<U16>(MAX_CHAN_2405);
  m_pAIBuf = std::vector<U32>(AI_SAMPLE_COUNT*MAX_CHAN_2405);
  for(size_t i = 0; i< 4; i++) {
    m_remotes.push_back({false, nullptr});
  }
}

JytekAi::~JytekAi() {
  this->stopAI();
}

void JytekAi::setCardId(const I16 &id) {
  cardNum = id;
}

bool JytekAi::startAI(const bool &channel0, const bool &channel1, const bool &channel2,
                      const bool &channel3, const double &sampleRate, const bool &saveFile) {
  m_fSampleRate = sampleRate;
  m_saveFile    = saveFile;
  m_remotes[0].enable = channel0;
  m_remotes[1].enable = channel1;
  m_remotes[2].enable = channel2;
  m_remotes[3].enable = channel3;

  I16 err = UD_AI_2405_Chan_Config(cardNum, ( P2405_AI_DisableIEPE | P2405_AI_Coupling_None | P2405_AI_Differential),
                                            ( P2405_AI_DisableIEPE | P2405_AI_Coupling_None | P2405_AI_Differential),
                                            ( P2405_AI_DisableIEPE | P2405_AI_Coupling_None | P2405_AI_Differential),
                                            ( P2405_AI_DisableIEPE | P2405_AI_Coupling_None | P2405_AI_Differential) );

  if( err != DaqNoError ) {
    std::cout  << "UD_AI_2405_Chan_Config() failed, error code = " << err << std::endl;;
    return false;
  }

  err = UD_AI_2405_Trig_Config( cardNum, P2405_AI_CONVSRC_INT, P2405_AI_TRGMOD_POST, P2405_AI_TRGSRC_SOFT, 0, 0, 0, 0 );
  if (err != DaqNoError) {
    std::cout  <<  "UD_AI_2405_Trig_Config() failed, error code = " << err << std::endl;
    return false;
  }

  err = UD_AI_AsyncDblBufferMode(cardNum, 1);
  if (err != DaqNoError) {
    std::cout  <<  "UD_AI_AsyncDblBufferMode() failed, error code = " << err << std::endl;
    return false;
  }

  m_wSelectedChans = 0;
  if(channel0) {
    m_wChan[m_wSelectedChans] = 0;
    m_wGain[m_wSelectedChans] = AD_B_10_V;
    m_wSelectedChans++;
  }
  if(channel1) {
    m_wChan[m_wSelectedChans] = 1;
    m_wGain[m_wSelectedChans] = AD_B_10_V;
    m_wSelectedChans++;
  }
  if(channel2) {
    m_wChan[m_wSelectedChans] = 2;
    m_wGain[m_wSelectedChans] = AD_B_10_V;
    m_wSelectedChans++;
  }
  if(channel3) {
    m_wChan[m_wSelectedChans] = 3;
    m_wGain[m_wSelectedChans] = AD_B_10_V;
    m_wSelectedChans++;
  }

  err = UD_AI_ContReadMultiChannels(cardNum, m_wSelectedChans, m_wChan.data(), m_wGain, (U16*)m_pAIBuf.data(), AI_SAMPLE_COUNT*m_wSelectedChans, (F64)m_fSampleRate, ASYNCH_OP);
  if (err != DaqNoError) {
    std::cout  << "UD_AI_ContReadMultiChannels() failed, error code = " << err << std::endl;
    return false;
  }

  m_stop = false;

  // auto res = UD_AI_EventCallBack(cardNum, AIEnd, P1902_EVT_TYPE_EPT0, (U32)(callback_data));
  //  std::cout << "call back res." << res << std::endl;
  //  std::cout.flush();
  m_task = std::make_shared<std::thread>([this]() {
    run();
  });

  return true;
}

void JytekAi::stopAI() {
  U32 count;
  UD_AI_AsyncClear(cardNum, &count);
  m_stop = true;
  m_task -> join();
}

std::map<U16, std::vector<double> > JytekAi::getTransferDatas() {
  return m_dataProcess.getTransferDatas();
}

bool JytekAi::setRawDataCallback(callback_adlink_t callback) {
  raw_callback_func = callback;
  return true;
}

void JytekAi::run() {
  while(!m_stop) {
    BOOLEAN HalfReady;
    BOOLEAN fstop;
    while (!m_stop) {
      I16 err = UD_AI_AsyncDblBufferHalfReady(cardNum, &HalfReady, &fstop);
      // half-buffer ready
      if( HalfReady ) {
        err = UD_AI_AsyncDblBufferTransfer32(cardNum, m_pAIBuf.data());
        if (raw_callback_func != nullptr) {
          std::vector<unsigned char> data;
          for (size_t i = 0; i < m_pAIBuf.size() / 2; i++) {
            data.push_back((m_pAIBuf[i] >> 24) & 0xFF);
            data.push_back((m_pAIBuf[i] >> 16) & 0xFF);
            data.push_back((m_pAIBuf[i] >> 8) & 0xFF);
            data.push_back((m_pAIBuf[i]) & 0xFF);
          }
          raw_callback_func(std::make_shared<std::vector<unsigned char>>(data));
        }
        int enable_count = 0;
        int ready_to_transport_count = 0;
        std::vector<std::shared_ptr<std::vector<unsigned char>>> res;
        for (size_t i = 0; i < m_remotes.size(); ++i) {
          if (m_remotes[i].enable) {
            enable_count++;
            if (m_remotes[i].callback && m_remotes[i].enable) {
              res.push_back(std::make_shared<std::vector<unsigned char>>());
              ready_to_transport_count++;
            } else {
              res.push_back(nullptr);
            }
          }
        }
        if (ready_to_transport_count) {
          unsigned char* cur = (unsigned char*)(m_pAIBuf.data());
          size_t active_size = (m_pAIBuf.size() * 0.5 * (enable_count / 4.0));
          int filter_tag = 0;
          for (size_t i = 0; i < active_size; i++) {
            if (filter_tag >= enable_count) filter_tag = 0;
            if (res[filter_tag]) {
              cur ++;
              (*res[filter_tag]).push_back(*cur);
              cur ++;
              (*res[filter_tag]).push_back(*cur);
              cur ++;
              (*res[filter_tag]).push_back(*cur);
              cur ++;
            } else {
              cur += 4;
            }
            filter_tag ++;
          }
          int cur_res_index = 0;
          for (size_t i = 0; i < m_remotes.size(); ++i) {
            if (m_remotes[i].enable) {
              if (m_remotes[i].callback)
                m_remotes[i].callback(res[cur_res_index]);
              cur_res_index++;
            }
          }
        }
        break;
      }
      std::this_thread::sleep_for(std::chrono::microseconds(1));
    }
  }
}
