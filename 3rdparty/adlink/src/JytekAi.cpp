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
m_task(nullptr) {
  m_wChan  = std::vector<U16>(MAX_CHAN_2405);
  m_pAIBuf = std::vector<U32>(AI_SAMPLE_COUNT*MAX_CHAN_2405);

//  qRegisterMetaType<U16>("U16");
//  connect(m_dataProcess,&JytekDataProcess::readData_signal,this,&JytekDaq::readData_signal);
}

JytekAi::~JytekAi()
{
  this->stopAI();
}

void JytekAi::setCardId(const I16 &id)
{
  cardNum = id;
}

bool JytekAi::startAI(const bool &channel0, const bool &channel1, const bool &channel2, const bool &channel3, const double &sampleRate, const bool &saveFile)
{
  m_fSampleRate = sampleRate;
  m_saveFile    = saveFile;

  I16 err = UD_AI_2405_Chan_Config( cardNum, ( P2405_AI_DisableIEPE | P2405_AI_Coupling_None | P2405_AI_Differential),
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
  m_task = std::make_shared<std::thread>([this](){
    run();
  });
//  m_dataProcess.startProcess(m_wSelectedChans,m_wChan);

  return true;
}

void JytekAi::stopAI() {
//  m_dataProcess.stopProcess();
  U32 count;
  UD_AI_AsyncClear(cardNum, &count);
  std::cout << "hehe" << std::endl;
  std::cout.flush();
  m_stop = true;
  m_task -> join();
//  this->wait();
}

std::map<U16, std::vector<double> > JytekAi::getTransferDatas() {
  return m_dataProcess.getTransferDatas();
}

void JytekAi::run() {
  while(!m_stop) {
    BOOLEAN HalfReady;
    BOOLEAN fstop;
    while (!m_stop) {
      I16 err = UD_AI_AsyncDblBufferHalfReady(cardNum, &HalfReady, &fstop);

       // half-buffer ready
      if( HalfReady ) {
          static int xx = 0;
          std::cout << xx++ << std::endl;
          std::cout.flush();
        err = UD_AI_AsyncDblBufferTransfer32(cardNum, m_pAIBuf.data());
        break;
      }

      std::this_thread::sleep_for(std::chrono::microseconds(1));
    }
  }
}
