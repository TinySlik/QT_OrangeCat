#include "tinimsgdecoderv1.h"
#include "easylogging++.h"


TiniMsgDecoderv1::TiniMsgDecoderv1(const std::string &decode_info):
MsgDecoder(decode_info) {
  LOG(INFO) << __FUNCTION__ << decode_info_;
}

TiniMsgDecoderv1::~TiniMsgDecoderv1() {
}

bool TiniMsgDecoderv1::decode(const bool &value) {
  LOG(INFO)<< __FUNCTION__ << value;
  return false;
}

bool TiniMsgDecoderv1::reset() {
  return false;
}

std::shared_ptr<MsgDecoder> TiniMsgDecoderv1::create(const std::string &decode_info) {
  std::shared_ptr<TiniMsgDecoderv1> res(new TiniMsgDecoderv1(decode_info));
  return res;
}

configuru::Config TiniMsgDecoderv1::defaultParams() {
  return {};
}
