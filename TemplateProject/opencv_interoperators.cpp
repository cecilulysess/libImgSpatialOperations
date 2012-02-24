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

#include "opencv_interoperators.h"

#include <iostream>

#include "lib_img_spatial_operations.h"

#include "opencv2\core\core.hpp"

using namespace std;
using ::lib_img_spatial_operations::GrayLevelImage4Byte;
GrayLevelImage4Byte* GetGrayLevelImage4Byte(cv::Mat* image_mat){
  //cv::Mat.size() return
  //int** image_data = new int*[image_mat->size[1]];
  cout<<image_mat->size<<endl;
  return NULL;
}