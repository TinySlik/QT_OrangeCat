#ifndef TINIMSGDECODERV1_H
#define TINIMSGDECODERV1_H

#include "msgdecoder.h"

class TiniMsgDecoderv1 : public MsgDecoder {
  explicit TiniMsgDecoderv1(const std::string &decode_info);
 public:
  virtual ~TiniMsgDecoderv1() override;
  virtual bool decode(const bool &value) override;
  virtual configuru::Config defaultParams() override;
  virtual bool reset() override;
  static std::shared_ptr<MsgDecoder> create(const std::string &decode_info);
};

#endif // TINIMSGDECODERV1_H
