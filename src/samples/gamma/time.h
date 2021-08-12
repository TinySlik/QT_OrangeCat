#ifndef TIME_C_H
#define TIME_C_H


#ifdef WIN32
#include <windows.h>
#include <process.h>
#else
#include <unistd.h>
#include <sys/time.h>
#include <netinet/in.h>
#endif

#include <iostream>

uint64_t get_micro_second();


#endif // TIME_C_H
