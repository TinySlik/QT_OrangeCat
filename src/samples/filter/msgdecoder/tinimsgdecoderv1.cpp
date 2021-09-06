#include "tinimsgdecoderv1.h"
#include "easylogging++.h"
#define MAX_BIT_COUNT (1024)

struct decode_tempalete_unit {
  const char *name;
  size_t check;
  size_t length;
  std::function<configuru::Config(std::vector<char> data)> func;
};

configuru::Config DefaultProcess(std::vector<char> data) {
  data.push_back('\0');
  LOG(INFO) << "  content: " << data.data();
  return data.data();
}

int charArrayToInt(std::vector<char> data) {
  int res = 0;
//  for(size_t i = 0; i < data.size(); ++i) {
//    int tmp = data[i] == '1' ? 1 : 0;
//    if (i == 0 && tmp == 1) res = 0xffffffff
//    res += data[i] == '1' ? 1 : 0;
//    res <<= 1;
//  }
}

const struct decode_tempalete_unit decode_tempalete_table[] = {
  {"PU",  0, 8,   nullptr},
  {"PD",  0, 8,   nullptr},
  {"GX",  1, 13,  DefaultProcess},
  {"GY",  1, 13,  DefaultProcess},
  {"GZ",  1, 13,  DefaultProcess},
  {"BX",  1, 13,  DefaultProcess},
  {"BY",  1, 13,  DefaultProcess},
  {"BZ",  1, 13,  DefaultProcess},
  {"IN",  1, 12,  DefaultProcess},
  {"GT",  1, 8,   DefaultProcess},
  {"TM",  1, 7,   DefaultProcess},
  {"RM",  1, 9,   DefaultProcess},
  {"HS",  1, 9,   DefaultProcess},
  {"BM",  1, 13,  DefaultProcess},
  {"BC",  1, 13,  DefaultProcess},
  {"BS",  1, 8,   DefaultProcess},
  {"TS",  0, 1,   DefaultProcess},
  {"TF",  1, 7,   DefaultProcess},
  {"CV",  0, 1,   DefaultProcess},
  {"SC",  1, 12,  DefaultProcess},
  {"LC",  1, 12,  DefaultProcess},
  {"GA",  1, 9,   DefaultProcess},
  {"GB",  1, 9,   DefaultProcess},
  {"ABI", 1, 13,  DefaultProcess},
  {"ABS", 1, 9,   DefaultProcess},
};

TiniMsgDecoderv1::TiniMsgDecoderv1(const std::string &decode_info):
MsgDecoder(decode_info),
tag_bit(0),
cur_tag(-1),
start_tag(false) {
  LOG(INFO) << __FUNCTION__ << decode_info_;
  auto list_count = decode_info_.as_array().size();
  unsigned int res_log = 1;
  while (res_log < list_count) {
    res_log <<= 1;
    tag_bit++;
  }
  for (auto& v: decode_info_.as_array()) {
    _decoders.push_back(std::vector<DECODE_UNIT>());
    for (auto& vi: v["array"].as_array()) {
      DECODE_UNIT res = {std::string(vi), 0, nullptr};
      for(size_t k = 0; k < sizeof(decode_tempalete_table)/sizeof(decode_tempalete_unit); ++k) {
        if (res.name == decode_tempalete_table[k].name) {
          res.size = decode_tempalete_table[k].length;
//          LOG(INFO) << res.size;
        }
      }
      _decoders[_decoders.size() - 1].push_back(res);
    }
  }
  auto status = ParameterServer::instance()->GetCfgStatusRoot();
  status["list_current_target"] = "NULL";
  status["list_current_target"].add_callback([this](configuru::Config &a, const configuru::Config &b)->bool {
    if (!b.is_string()) return false;
    auto str1 = std::string(a);
    auto str2 = std::string(b);
    if (str1 == "NULL") return true;
    LOG(INFO) << str1;
    for (size_t k = 0; k < sizeof(decode_tempalete_table)/sizeof(decode_tempalete_unit); ++k) {
      if (str1 == decode_tempalete_table[k].name) {
      if (data_.size() < decode_tempalete_table[k].length) {
        break;
      }
      std::vector<char> res;
      char * dt = data_.data() + data_.size() - decode_tempalete_table[k].length;
      for (size_t j = 0; j < decode_tempalete_table[k].length; ++j) {
        res.push_back(*dt);
        dt++;
      }
      if (decode_tempalete_table[k].check > 0) {
        unsigned char res_check = res[res.size() - 1] == '1' ? 1 : 0;
        res.pop_back();
        for (size_t k = 0; k < res.size(); ++k) {
          res_check ^= res[k] == '1' ? 1 : 0;
        }
        if (res_check == 0) {
          decode_tempalete_table[k].func(res);
        } else {
          LOG(INFO) << "check bit error";
        }
      } else {
        decode_tempalete_table[k].func(res);
      }
      return true;
      }
    }
    return false;
  });
}

TiniMsgDecoderv1::~TiniMsgDecoderv1() {
}

bool TiniMsgDecoderv1::decode(const bool &value) {
  data_.push_back(value? '1' : '0');
  if (data_.size() > MAX_BIT_COUNT) {
    LOG(ERROR) << "data out of range";
    data_.clear();
    return false;
  }
  auto status = ParameterServer::instance()->GetCfgStatusRoot();
  size_t sz = data_.size();
  char *data = data_.data();
  if (sz > 6 && memcmp(data + sz - 7 , "1111110", 7) == 0) {
    if (start_tag) {
      data_.pop_back();
      data_.pop_back();
      data_.pop_back();
      data_.pop_back();
      data_.pop_back();
      data_.pop_back();
      data_.pop_back();
      data_.pop_back();
      status["list_current_target"] << "NULL";
      auto index = static_cast<size_t>(cur_tag);
      auto queue = _decoders[index];
      size_t leg = tag_bit;
      for (size_t k = 0; k < queue.size(); ++k) {
        leg += queue[k].size;
      }
      if (leg == data_.size()) {
        LOG(INFO) << "expect length: " << leg << "--" << "real length: " << data_.size();
        status["last_msg_completeness_check"] = "Credible";
      } else {
        LOG(INFO) << "expect length: " << leg << "--" << "real length: " << data_.size();
        status["last_msg_completeness_check"] = "Undependable";
        start_tag = false;
      }
    } else {
      start_tag = true;
    }

    data_ = {'0', '1', '1', '1', '1', '1', '1', '0'};
    cur_tag = -1;
    if (status.has_key("list_name")) {
      status["last_name"] = status["list_name"];
      status.erase("list_name");
    }
    if (status.has_key("list_content")) {
      status["last_content"] = status["list_content"];
      status.erase("list_content");
    }
  }
  std::vector<char> data__ = data_;
  data__.push_back('\0');

  std::string bits = data__.data();
  auto length = bits.length();
  status["bits"] = bits;
  if (length == (8 + tag_bit)) {
    unsigned char res = 0;
    for (size_t j = 0; j < tag_bit; ++j)
        res += bits.c_str()[8 + tag_bit - j - 1] == '1' ? 1 << j : 0;
    cur_tag = static_cast<int>(res);
    status["list_name"] = decode_info_[static_cast<size_t>(cur_tag)]["name"];
    std::string res_list_content = "";
    for (auto& vi: decode_info_[static_cast<size_t>(cur_tag)]["array"].as_array()) {
      res_list_content += " ";
      res_list_content += std::string(vi);
    }
    status["list_content"] = res_list_content.c_str();
  }
  if (cur_tag > 0) {
    auto index = static_cast<size_t>(cur_tag);
    auto queue = _decoders[index];
    std::string res_list_content = "";
    bool fst_tag = true;
    int length_i = static_cast<int>(length);
    length_i -= tag_bit;
    for (size_t k = 0; k < queue.size(); ++k) {
      length_i -= queue[k].size;
      if (fst_tag && length_i < 0) {
        fst_tag = false;
        status["list_current_target"] << queue[k].name.c_str();
        res_list_content += "*";
      } else {
        res_list_content += " ";
      }
      res_list_content += queue[k].name;
    }
    status["list_content"] = res_list_content.c_str();
  }

  return true;
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
