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

#include "include\opencv_interoperators.h"

#include <iostream>

#include "opencv2\core\core.hpp"
#include "opencv2\highgui\highgui.hpp"

using namespace std;
namespace lib_img_spatial_operations{

  GrayLevelImage4Byte* OpenCVInteroperator::GetGrayLevelImage4ByteFromMat(
      const cv::Mat& image_mat){
    //cv::Mat.size is [hight, width]
    int** image_data = new int*[image_mat.size[0]];
    for (int i = 0; i < image_mat.size[0]; ++i) {
      image_data[i] = new int[image_mat.size[1]];
      for (int j = 0; j < image_mat.size[1]; ++j) {
        try {
          // see image_mat.elemSize()
          image_data[i][j] = (int)image_mat.at<unsigned char>(i,j);
        } catch (...){
          cout<<"Exceprtion:"<<endl;
        }
      }
    }
    return new GrayLevelImage4Byte(image_mat.size[1], 
                                   image_mat.size[0], 
                                   image_data);
  }

  cv::Mat* OpenCVInteroperator::GetMatFromGrayLevelImage4Byte(
      const GrayLevelImage4Byte& image){
    // graylevel image is always treated as an byte 
    cv::Mat result_mat = cv::Mat::zeros(image.height(), image.width(), CV_8U);
    for (int i = 0; i < image.height(); ++i) {
      for (int j = 0; j < image.width(); ++j) {
        result_mat.at<unsigned char>(i,j) = (unsigned char)image.GetPixel(j, i);
      }
    }
    cv::Mat* res = new cv::Mat();
    result_mat.copyTo(*res);
    return res;
  }

  // show an image with an opencv window, and its histogram
  void OpenCVInteroperator::ShowImage(
      const ::lib_img_spatial_operations::GrayLevelImage4Byte& image2show, 
      const char* window_title){
    cv::Mat* img2show = OpenCVInteroperator::GetMatFromGrayLevelImage4Byte(
        image2show);
    cv::namedWindow(window_title, CV_WINDOW_NORMAL | CV_WINDOW_KEEPRATIO| CV_GUI_EXPANDED);
    imshow(window_title, *img2show);
    //cv::waitKey(0);
  }

} // ns opencv_interoperators