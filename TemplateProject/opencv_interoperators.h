// libImgSpatialOperations - Yanxiang Wu's implementation of many frequently
// used spatial image operations
// Copyright 2012 Yanxiang Wu. All right reserved
// https://github.com/cecilulysess/libImgSpatialOperations
//
// License: Apache 2.0

// Author: cosmobserver@gmail.com (Yanxiang Wu)
// First version of this project
// this header file define all the classes and functions used to interoperate
// with OpenCV
#ifndef OPENCV_INTEROPERATORS_H_
#define OPENCV_INTEROPERATORS_H_

// removed include by using forward declaration
#include "lib_img_spatial_operations.h"

#include "opencv2\core\core.hpp"

namespace opencv_interoperators {
  // Get a GrayLevelImage4Byte by providing cv::Mat matrix
  ::lib_img_spatial_operations::GrayLevelImage4Byte* GetGrayLevelImage4Byte(cv::Mat* image_mat);
} //ns opencv_interoperators
#endif