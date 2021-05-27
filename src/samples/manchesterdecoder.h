#ifndef MANCHESTERDECODER_H
#define MANCHESTERDECODER_H
#include <memory>
#include <vector>
#include "parameterserver.h"

class ManchesterDecoder: public std::enable_shared_from_this<ManchesterDecoder> {
public:
  virtual bool decodeBeforeWait(std::shared_ptr<std::vector<float>> data) = 0;
  virtual bool decodeAfterWait() =  0;
  virtual configuru::Config defaultParams() = 0;
  virtual std::shared_ptr<std::vector<float>> displayBuffer();
  virtual configuru::Config syncParams(configuru::Config &cfg);

  explicit ManchesterDecoder();
  virtual ~ManchesterDecoder();
  virtual char getCurrentResualt();
  virtual const std::shared_ptr<std::vector<char>> getResualtList();

protected:
  std::shared_ptr<std::vector<char>> _resualt;
  std::shared_ptr<std::vector<float>> _displayBuffer;
};

#endif // MANCHESTERDECODER_H
