#ifndef TINIMSGDECODERV2_H
#define TINIMSGDECODERV2_H

#include "msgdecoder.h"
#include <vector>

class TiniMsgDecoderv2 : public MsgDecoder {
  typedef struct decode_unit{
    std::string name;
    size_t size;
    std::function<bool(const std::vector<char>)> func;
  } DECODE_UNIT;
  explicit TiniMsgDecoderv2(const std::string &decode_info);
 public:
  virtual ~TiniMsgDecoderv2() override;
  virtual bool decode(const bool &value) override;
  virtual configuru::Config defaultParams() override;
  virtual bool reset() override;
  static std::shared_ptr<MsgDecoder> create(const std::string &decode_info);
 private:
  std::vector<char> data_;
  std::vector<std::vector<DECODE_UNIT>> _decoders;
  size_t tag_bit;
  int cur_tag;
  bool start_tag;
  bool _process_init_wait_tag;
};

#endif // TINIMSGDECODERV2_H
