/****************************************************************************
**
** Copyright (C) 2020 The ZHIZUO Company Ltd.
**
** This file is part of the ZHIZUO Ultrasound SDK.
**
** Private License
** All right include copy change are reserved.
**
****************************************************************************/

#include "renderutil.h"

int str_to_hex(char *string, unsigned char *cbuf, int len) {
  unsigned char high, low;
  int idx, ii=0;
  for (idx=0; idx<len/2; idx+=2) {
    unsigned char  tmp_high = string[idx];
    unsigned char  tmp_low = string[idx+1];
    string[idx] = string[8 - 2 - idx];
    string[idx+1] = string[8 - 2 - idx + 1];
    string[8 - 2 - idx] = tmp_high;
    string[8 - 2 - idx + 1] = tmp_low;
  }
  for (idx=0; idx<len; idx+=2) {
    high = string[idx];
    low = string[idx+1];

    if(high>='0' && high<='9')
      high = high-'0';
    else if(high>='A' && high<='F')
      high = high - 'A' + 10;
    else if(high>='a' && high<='f')
      high = high - 'a' + 10;
    else
      return -1;

    if(low>='0' && low<='9')
      low = low-'0';
    else if(low>='A' && low<='F')
      low = low - 'A' + 10;
    else if(low>='a' && low<='f')
      low = low - 'a' + 10;
    else
      return -1;
    cbuf[ii++] = high<<4 | low;
  }
  return 0;
}

void hex_to_str(char *ptr,unsigned char *buf,int len) {
  for(int i = len-1; i >= 0; i--) {
    sprintf(ptr, "%02x",buf[i]);
    ptr += 2;
  }
}

std::string color_format_int_to_string(const uint32_t &color) {
  std::string res = "#";
  char color_str[16];
  hex_to_str(color_str, (unsigned char*)(&color), 4);
  res += color_str;
  return res;
}

uint32_t color_format_string_to_int(const std::string &color) {
  uint32_t res = 0xffffffff;
  auto hd = (char *)strstr(color.c_str(),"#");
  if (hd) {
    if (color.length() == 9) {
      if (str_to_hex(hd+1,(unsigned char *)&res, 8) >= 0) {
        return res;
      }
    } else if (color.length() == 7){
      auto color_tmp = color + "ff";
      hd = (char *)strstr(color_tmp.c_str(),"#");
      if (str_to_hex(hd+1,(unsigned char *)&res, 8) >= 0) {
        return res;
      }
    }
  }
  return 0xffffffff;
}

QColor color_format_int_to_qcolor(const uint32_t &color) {
  return {(int(color >> 24)&(0x000000ff)),
          (int(color >> 16)&(0x000000ff)),
          (int(color >> 8) &(0x000000ff)),
          (int(color)      &(0x000000ff))};
}
uint32_t color_format_qcolor_to_int(const QColor color) {
  return  (uint32_t)((uint8_t)(color.redF() * 255.0) << 24) +
          (uint32_t)((uint8_t)(color.greenF() * 255.0) << 16) +
          (uint32_t)((uint8_t)(color.blueF() * 255.0) << 8) +
          (uint32_t)((uint8_t)(color.alphaF() * 255.0));
}

QColor color_format_string_to_qcolor(const std::string &color) {
  QColor res = {0, 0, 0, 0};
  uint32_t temp = 0xffffffff;
  auto hd = (char *)strstr(color.c_str(),"#");
  if (hd) {
    if (color.length() == 9) {
    } else if (color.length() == 7){
      auto color_tmp = color + "ff";
      hd = (char *)strstr(color_tmp.c_str(),"#");
    } else {
      return {0, 0, 0, 0};
    }
    if (str_to_hex(hd+1,(unsigned char *)&temp, 8) >= 0) {
        res = color_format_int_to_qcolor(temp);
    }
  }
  return res;
}

std::string color_format_qcolor_to_string(const QColor color) {
  uint32_t temp = color_format_qcolor_to_int(color);
  return color_format_int_to_string(temp);
}
