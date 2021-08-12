#include "time.h"

uint64_t get_micro_second() {
  uint64_t current_time;
#ifdef WIN32
  current_time = GetTickCount64();
#else
  struct timeval current;
  gettimeofday(&current, NULL);
  current_time = current.tv_sec * 1000 + current.tv_usec/1000;
//  std::cout << current_time << std::endl;;
//  std::cout.flush();
#endif
  return current_time;
}
