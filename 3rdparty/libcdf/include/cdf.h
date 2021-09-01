
/*
 * Copyright (c) 2021-2024 Tini Software Limited
 * All rights reserved
 *
 */

#ifndef OIL_3RDPARTY_LIBCDF_INCLUDE_CDF_H_
#define OIL_3RDPARTY_LIBCDF_INCLUDE_CDF_H_
#include <string>
#include <vector>
#include "windllsupport.h"

struct CLASS_DECLSPEC cdf {
  static std::string cdfStringToInfoListJson_v1_0(const std::string &src);
  static std::string infoListJsonToCdfString(const std::string &src);
};

#endif  // OIL_3RDPARTY_LIBCDF_INCLUDE_CDF_H_
