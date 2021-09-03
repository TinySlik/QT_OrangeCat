#ifndef TINIMSGDECODERV1_H
#define TINIMSGDECODERV1_H

#include "msgdecoder.h"
#include <vector>
typedef struct decode_unit{
  std::string name;
  size_t size;
  std::function<bool(const std::vector<char>)> func;
} DECODE_UNIT;

class TiniMsgDecoderv1 : public MsgDecoder {
  explicit TiniMsgDecoderv1(const std::string &decode_info);
 public:
  virtual ~TiniMsgDecoderv1() override;
  virtual bool decode(const bool &value) override;
  virtual configuru::Config defaultParams() override;
  virtual bool reset() override;
  static std::shared_ptr<MsgDecoder> create(const std::string &decode_info);
 private:
  std::vector<char> data_;
  std::vector<std::vector<DECODE_UNIT>> _decoders;
  size_t tag_bit;
  int cur_tag;
};

#endif // TINIMSGDECODERV1_H
