﻿
/*
 * Copyright (c) 2021-2024 Tini Software Limited
 * All rights reserved
 *
 */

#include "cdf.h"
#define CONFIGURU_IMPLEMENTATION 1
#include "configuru.hpp"
#include <iostream>

//#define DEBUG_CDF

//{"GX" ,0x74},
//{"GY" ,0x75},
//{"GZ" ,0x76},
//{"BX" ,0x62},
//{"BY" ,0x63},
//{"BZ" ,0x64},
//{"RM" ,0x50},
//{"TM" ,0x4d},
//{"TS" ,0x78},
//{"TF" ,0x54},
//{"IN" ,0x49},
//{"CV" ,0x79},
//{"SC" ,0x43},
//{"LC" ,0x41},
//{"GT" ,0x47},
//{"HS" ,0x48},
//{"BTM",0x28},
//{"BTC",0x29},
//{"BS" ,0x59},
//{"SV" ,0x77},

//{"HGR" ,0xfe},
//{"HGA" ,0xfd},
//{"HGB" ,0xfc},
//{"HAI" ,0xff},
//{"HVS",0xFB};

/**
  0x3e	List1/List2的Preamble中第一个PU
  0x4c	List1/List2/SRS中Loop中的第一个PU
  0x46	Alarm中的PU
  0x46	List1/List2/SRS的Preamble中第一个以后的PU
  0x46	List1/List2/SRS的Loop中第一个以后的PU
  0x3c	List1/List2的Preamble中第一个PD
  0x3d	SRS的Preamble中第一个PD
  0x66	List1/List2/SRS的Preamble中第一个以后的PD
  0x7C	List1/List2/SRS的Loop中第一个以后的PD
  0x74	GX
  0x75	GY
  0x76	GZ
  0x62	BX
  0x63	BY
  0x64	BZ
  0x50	RM
  0x4d	TM
  0x78	TS
  0x54	TF
  0x49	IN
  0x79	CV
  0x43	SC
  0x41	LC
  0x47	GT
  0x48	HS
  0x28	BTM(BM)
  0x29	BTC(BC)
  0x59	BS
  0x77	SVSS（SV）
  0x4E	GR
  0x26	GR
  0x40	CG
  0xFF	ABI
  0xFE	GA
  0xFD	GB
  0xFC	ABS
*/

std::string cdf::cdfStringToInfoListJson_v1_0(const std::string &src) {
  configuru::Config res = configuru::Config::array();

  std::string tmp_or = src;
  char *cur = const_cast<char *>(tmp_or.c_str());
  cur += 28;
  std::string cur_list_name = "Alarm";
  int cur_index = -1;
  bool break_tag = false;
  for (size_t i = 0; i< src.length(); ++i) {
    auto val = (unsigned int) (unsigned char)(*cur);
#ifdef DEBUG_CDF
    std::cout << std::hex << val << "|";
#endif
    if (val == 0x3e ||
        val == 0x4c ||
        val == 0x46 ||
        val == 0x3c ||
        val == 0x3d ||
        val == 0x66 ||
        val == 0x7C) {
      if (val == 0x46 && i == 0) {
        res.push_back(
              {
                {"name", cur_list_name.c_str()},
                {"array", configuru::Config::array({"PU"})}
              });
        cur_index++;
      } else if (val == 0x46) {
          res.push_back(
                {
                  {"name", cur_list_name.c_str()},
                  {"array", configuru::Config::array({"PU"})}
                }
                );
          cur_index++;
//        res[static_cast<size_t>(cur_index)]["array"].push_back("PU");
      } else if (val == 0x3e) {
        if (cur_list_name == "Alarm") cur_list_name = "List1Preamble";
        else if (cur_list_name == "List1Preamble") cur_list_name = "List2Preamble";
        else if (cur_list_name == "List1Loop") cur_list_name = "List2Preamble";
        res.push_back(
              {
                {"name", cur_list_name.c_str()},
                {"array", configuru::Config::array({"PD"})}
              });
        cur_index++;
      } else if (val == 0x4c) {
        if (cur_list_name == "Alarm") cur_list_name = "List1Loop";
        else if (cur_list_name == "List1Preamble") cur_list_name = "List1Loop";
        else if (cur_list_name == "List2Preamble") cur_list_name = "List2Loop";
        else if (cur_list_name == "List1Loop") cur_list_name = "List2Loop";
        else if (cur_list_name == "SRSPreamble") cur_list_name = "SRSLoop";
        else if (cur_list_name == "List2Loop") cur_list_name = "SRSLoop";
        res.push_back(
              {
                {"name", cur_list_name.c_str()},
                {"array", configuru::Config::array({"PU"})}
              }
              );
        cur_index++;
      } else if (val == 0x3c) {
        if (cur_list_name == "Alarm") cur_list_name = "List1Preamble";
        else if (cur_list_name == "List1Preamble") cur_list_name = "List2Preamble";
        else if (cur_list_name == "List1Loop") cur_list_name = "List2Preamble";
        res.push_back(
              {
                {"name", cur_list_name.c_str()},
                {"array", configuru::Config::array({"PD"})}
              }
              );
        cur_index++;
      } else if (val == 0x3d) {
        cur_list_name = "SRSPreamble";
        res.push_back(
              {
                {"name", cur_list_name.c_str()},
                {"array", configuru::Config::array({"PD"})}
              }
              );
        cur_index++;
      } else if (val == 0x66 || val == 0x7c) {
          res.push_back(
                {
                  {"name", cur_list_name.c_str()},
                  {"array", configuru::Config::array({"PD"})}
                }
                );
          cur_index++;
//        res[static_cast<size_t>(cur_index)]["array"].push_back("PD");
      }
    } else {
      switch (val) {
        case 0x74:	res[static_cast<size_t>(cur_index)]["array"].push_back("GX");
          break;
        case 0x75:	res[static_cast<size_t>(cur_index)]["array"].push_back("GY");
          break;
        case 0x76:	res[static_cast<size_t>(cur_index)]["array"].push_back("GZ");
          break;
        case 0x62:	res[static_cast<size_t>(cur_index)]["array"].push_back("BX");
          break;
        case 0x63:	res[static_cast<size_t>(cur_index)]["array"].push_back("BY");
          break;
        case 0x64:	res[static_cast<size_t>(cur_index)]["array"].push_back("BZ");
          break;
        case 0x50:	res[static_cast<size_t>(cur_index)]["array"].push_back("RM");
          break;
        case 0x4d:	res[static_cast<size_t>(cur_index)]["array"].push_back("TM");
          break;
        case 0x78:	res[static_cast<size_t>(cur_index)]["array"].push_back("TS");
          break;
        case 0x54:	res[static_cast<size_t>(cur_index)]["array"].push_back("TF");
          break;
        case 0x49:	res[static_cast<size_t>(cur_index)]["array"].push_back("IN");
          break;
        case 0x79:	res[static_cast<size_t>(cur_index)]["array"].push_back("CV");
          break;
        case 0x43:	res[static_cast<size_t>(cur_index)]["array"].push_back("SC");
          break;
        case 0x41:	res[static_cast<size_t>(cur_index)]["array"].push_back("LC");
          break;
        case 0x47:	res[static_cast<size_t>(cur_index)]["array"].push_back("GT");
          break;
        case 0x48:	res[static_cast<size_t>(cur_index)]["array"].push_back("HS");
          break;
        case 0x28:	res[static_cast<size_t>(cur_index)]["array"].push_back("BM");
          break;
        case 0x29:	res[static_cast<size_t>(cur_index)]["array"].push_back("BC");
          break;
        case 0x59:	res[static_cast<size_t>(cur_index)]["array"].push_back("BS");
          break;
        case 0x77:	res[static_cast<size_t>(cur_index)]["array"].push_back("SV");
          break;
        case 0x4E:	res[static_cast<size_t>(cur_index)]["array"].push_back("GR");
          break;
        case 0x26:	res[static_cast<size_t>(cur_index)]["array"].push_back("GR");
          break;
        case 0x40:	res[static_cast<size_t>(cur_index)]["array"].push_back("CG");
          break;
        case 0xFF:	res[static_cast<size_t>(cur_index)]["array"].push_back("ABI");
          break;
        case 0xFE:	res[static_cast<size_t>(cur_index)]["array"].push_back("GA");
          break;
        case 0xFD:	res[static_cast<size_t>(cur_index)]["array"].push_back("GB");
          break;
        case 0xFC:	res[static_cast<size_t>(cur_index)]["array"].push_back("ABS");
          break;
          //{"HGR" ,0xfe},
          //{"HGA" ,0xfd},
          //{"HGB" ,0xfc},
          //{"HAI" ,0xff},
          //{"HVS",0xFB};
//        case 0xfe:	res[static_cast<size_t>(cur_index)]["array"].push_back("HGR");
//          break;
//        case 0xfd:	res[static_cast<size_t>(cur_index)]["array"].push_back("HGA");
//          break;
//        case 0xfc:	res[static_cast<size_t>(cur_index)]["array"].push_back("HGB");
//          break;
//        case 0xff:	res[static_cast<size_t>(cur_index)]["array"].push_back("HAI");
//          break;
//        case 0xfb:	res[static_cast<size_t>(cur_index)]["array"].push_back("HVS");
//          break;

        case 0x2e:
        case 0x20:	break_tag = true;
          break;
        default:
          std::cout << "unknow tag in decode cdf file." << "0x" << std::hex << val << std::endl;
          std::cout.flush();
          break;
      }
    }
    if (break_tag) break;
    cur++;
  }
#ifdef DEBUG_CDF
  std::cout << std::endl;
  std::cout.flush();
#endif
  return configuru::dump_string(res, configuru::JSON);
}

std::string cdf::infoListJsonToCdfString(const std::string &src) {
  return "todo";
}
