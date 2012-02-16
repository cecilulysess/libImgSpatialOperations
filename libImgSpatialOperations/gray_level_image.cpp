// libImgSpatialOperations - Yanxiang Wu's implementation of many frequently
// used spatial image operations
// Copyright 2012 Yanxiang Wu. All right reserved
// https://github.com/cecilulysess/libImgSpatialOperations
//
// License: Apache 2.0

// Author: cosmobserver@gmail.com (Yanxiang Wu)
// Implementation of GrayLevelImage4Byte, this is a classe used for 4byte uint
// gray level image

#include "include/lib_img_spatial_operations.h"

#include <stdexcept>

namespace lib_img_spatial_operations {
  int GrayLevelImage4Byte::obj_counter = 0;
  GrayLevelImage4Byte::GrayLevelImage4Byte(int width, int height, 
      int** image_data) 
      : width_(width), height_(height), gray_level_(256){
        this->Init(image_data);
  }

  GrayLevelImage4Byte::GrayLevelImage4Byte(int width, int height, 
      int** image_data, int graylevels)
      : width_(width), height_(height), gray_level_(graylevels){
        this->Init(image_data);
  }

  void GrayLevelImage4Byte::Init(int** image_data){
    //update the identifier
    this->id_ = obj_counter++;
    image_data_ = new int*[height_];
    for (int i = 0 ; i <height_ ; ++i) {
      image_data_[i] = new int[width_];
      for (int j = 0; j < width_; ++j) {
        image_data_[i][j] = image_data[i][j];
      }
    }
  }

  GrayLevelImage4Byte::~GrayLevelImage4Byte(){
    for (int i = 0 ; i <height_ ; ++i) {
      delete[] image_data_[i];
    }
    delete[] image_data_;
  }

  int GrayLevelImage4Byte::height() const { return this->height_; }
  int GrayLevelImage4Byte::width() const { return this->width_; }
  const int* const * GrayLevelImage4Byte::image_data() const { return this->image_data_; }
    
  int** GrayLevelImage4Byte::GetImageData() const {
    int** copy_image_data_ = new int*[height_];
    for (int i = 0 ; i <height_ ; ++i) {
      image_data_[i] = new int[width_];
      for (int j = 0; j < width_; ++j) {
        copy_image_data_[i][j] = image_data_[i][j];
      }
    }
    return copy_image_data_;
  }

  int GrayLevelImage4Byte::GetPixel(int x, int y) const {
    if (x >= this->width_ || y >= this->height_ || x*y < 0 ) {
      throw new std::out_of_range("x, y out is too large");
    }
    return this->image_data_[y][x];
  }

  int GrayLevelImage4Byte::gray_level() const {
    return this->gray_level_;
  }

} // namespace lib_img_spatial_operations