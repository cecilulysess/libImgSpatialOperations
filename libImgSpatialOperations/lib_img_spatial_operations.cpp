// libImgSpatialOperating - Yanxiang Wu's implementation of many frequently
// used spatial image operations
// Copyright 2012 Yanxiang Wu. All right reserved
// https://github.com/cecilulysess/libImgSpatialOperations
//
// License: Apache 2.0

// Author: cosmobserver@gmail.com (Yanxiang Wu)
// First version of this project

#include "lib_img_spatial_operations.h"

#include <stdexcept>

namespace lib_img_spatial_operations {
    double TestFunc::Add(double a, double b) {
      return a + b;
    }

    double TestFunc::Divide(double a, double b) {
      if (b == 0) {
        throw new std::invalid_argument("b cannot be 0");
      }
      return a / b;
    }
} // namespace lib_img_spatial_operations