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

#include "lib_img_spatial_operations.h"

// removed include by using forward declaration
//#include "lib_img_spatial_operations.h"
#include "opencv2\core\core.hpp"

#ifdef _EXPORTINGLISO
  #define LISO_CLASS_DECLSPEC    __declspec(dllexport)
#else
  #define LISO_CLASS_DECLSPEC    __declspec(dllimport)
#endif

namespace lib_img_spatial_operations {
  
  class LISO_CLASS_DECLSPEC OpenCVInteroperator {
  public:
    // Get a GrayLevelImage4Byte by providing cv::Mat matrix
    static ::lib_img_spatial_operations::GrayLevelImage4Byte*
        GetGrayLevelImage4ByteFromMat(const cv::Mat& image_mat);
    
    static cv::Mat* GetMatFromGrayLevelImage4Byte(
        const ::lib_img_spatial_operations::GrayLevelImage4Byte& image);

    // show an image with an opencv window, and its histogram
    static void ShowImage(
        const ::lib_img_spatial_operations::GrayLevelImage4Byte& image2show, 
        const char* window_title);
  };
} //ns lib_img_spatial_operations

#endif