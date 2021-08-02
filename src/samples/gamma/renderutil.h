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

#ifndef RENDERUTIL_H
#define RENDERUTIL_H
#include <iostream>
#include <string>
#include <QColor>

int str_to_hex(char *string, unsigned char *cbuf, int len);
void hex_to_str(char *ptr,unsigned char *buf,int len);
std::string color_format_int_to_string(const uint32_t &color);
uint32_t color_format_string_to_int(const std::string &color);

QColor color_format_string_to_qcolor(const std::string &color);
std::string color_format_qcolor_to_string(const QColor);

QColor color_format_int_to_qcolor(const uint32_t &color);
uint32_t color_format_qcolor_to_int(const QColor);

#endif // RENDERUTIL_H
