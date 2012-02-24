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
namespace opencv_interoperators{

  GrayLevelImage4Byte* OpenCVInteroperator::GetGrayLevelImage4ByteFromMat(
      cv::Mat* image_mat){
    //cv::Mat.size is [hight, width]
    int** image_data = new int*[image_mat->size[0]];
    for (int i = 0; i < image_mat->size[0]; ++i) {
      image_data[i] = new int[image_mat->size[1]];
      for (int j = 0; j < image_mat->size[1]; ++j) {
        try {
          // see image_mat->elemSize()
          image_data[i][j] = (int)image_mat->at<char>(i,j);
        } catch (...){
          cout<<"Exceprtion:"<<endl;
        }
      }
    }
    return new GrayLevelImage4Byte(image_mat->size[1], image_mat->size[0], image_data);
  }

  cv::Mat* OpenCVInteroperator::GetMatFromGrayLevelImage4Byte(
      GrayLevelImage4Byte* image){
    // graylevel image is always treated as an byte 
    cv::Mat result_mat = cv::Mat::zeros(image->height(), image->width(), CV_8U);
    for (int i = 0; i < image->height(); ++i) {
      for (int j = 0; j < image->width(); ++j) {
        result_mat.at<unsigned char>(i,j) = (unsigned char)image->GetPixel(j, i);
      }
    }
    cv::Mat* res = new cv::Mat();
    result_mat.copyTo(*res);
    return res;
    //return NULL;
  }

} // ns opencv_interoperators