#ifndef PARAMPROTOCOL_H
#define PARAMPROTOCOL_H
#include "parameterserver.h"


class ParamProtocol {
 public:
  ParamProtocol();
  ~ParamProtocol(){}
  virtual configuru::Config getParamConfig() = 0;
  virtual bool syncParamConfig(const configuru::Config & config) = 0;
};

#endif // PARAMPROTOCOL_H
