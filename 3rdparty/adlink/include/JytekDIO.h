#ifndef JYTEKDIO_H
#define JYTEKDIO_H

#include "usbdask.h"
#include <map>
#include <vector>
#include <mutex>
class adlink;

class JytekDIO {
public:
  explicit JytekDIO();
  ~JytekDIO();

  /**
   * @brief setCardId
   * @param id
   */
  void setCardId(const I16 &id);

  void startDIO(const bool &channel0, const bool &channel1);

  void stopDIO();

  std::map<int, std::vector<bool>> getDioDatas();

protected:
  void run();

private:
  bool m_stop;

  I16 cardNum;
  bool m_channel0;
  bool m_channel1;

  std::map<int, std::vector<bool>> m_datas;
  std::mutex dataMutex;

  friend adlink;
};

#endif // JYTEKDIO_H
