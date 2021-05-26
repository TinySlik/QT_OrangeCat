#ifndef MANCHESTERDECODER_H
#define MANCHESTERDECODER_H
#include <memory>


class ManchesterDecoder: public std::enable_shared_from_this<ManchesterDecoder> {
public:
  ManchesterDecoder();
  bool decodeBeforeWait();
  bool decodeAfterWait();
};

#endif // MANCHESTERDECODER_H
