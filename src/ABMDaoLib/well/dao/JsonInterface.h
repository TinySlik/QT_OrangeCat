#ifndef JSONINTERFACE_H
#define JSONINTERFACE_H
#include <string>

struct jsonInterface {
  virtual bool add(const std::string &json) = 0;
  virtual bool update(const std::string &json) = 0;
  virtual std::string find(const std::string &json) = 0;
};


#endif // JSONINTERFACE_H
