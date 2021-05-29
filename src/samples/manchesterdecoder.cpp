#include "manchesterdecoder.h"
using namespace configuru;


ManchesterDecoder::ManchesterDecoder() {
}

ManchesterDecoder::~ManchesterDecoder() {
}

char ManchesterDecoder::getCurrentResualt() {
  if (_resualt && _resualt->size() > 0) {
    return *(_resualt->begin());
  }
  return '\0';
}

const std::shared_ptr<std::vector<char>> ManchesterDecoder::getResualtList() {
  return _resualt;
}

configuru::Config ManchesterDecoder::syncParams(configuru::Config &cfg) {
  return cfg;
}

std::shared_ptr<std::vector<float>>  ManchesterDecoder::displayBuffer() {
  return _displayBuffer;
}
