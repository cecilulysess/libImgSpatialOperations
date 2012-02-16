// libImgSpatialOperations - Yanxiang Wu's implementation of many frequently
// used spatial image operations
// Copyright 2012 Yanxiang Wu. All right reserved
// https://github.com/cecilulysess/libImgSpatialOperations
//
// License: Apache 2.0

// Author: cosmobserver@gmail.com (Yanxiang Wu)
// First version of this project
// Implement the graylevel image's spatial transform operations,
// which include crop, scale, rotate, and torture.
#include "include/lib_img_spatial_operations.h"

#include <stdexcept>

namespace lib_img_spatial_operations {
  GraylevelImageCropOp::GraylevelImageCropOp(
      int x, int y, int width, int height) : 
      x_(x), y_(y), width_(width), height_(height) { }

  GrayLevelImage4Byte& GraylevelImageCropOp::FilterImage(
      const GrayLevelImage4Byte& source_img) const {
    // valid the parameter
    if (x_ * y_ < 0 || width_ * height_ < 0 ||  //check the negative case
        x_ + width_ > source_img.width() ||
        y_ + height_ > source_img.height() ) {
        throw new std::invalid_argument(
            "given parameter is not suit for the image");
    } 
    int** new_img = new int*[height_];
    for (int i = 0; i < height_; ++i) {
      new_img[i] = new int[width_];
      for (int j = 0; j < width_; ++j) {
        new_img[i][j] = source_img.GetPixel(x_ + j, y_ + i);
      }
    }
    GrayLevelImage4Byte* newImg = new GrayLevelImage4Byte(width_, height_, new_img);
    return *newImg;
  }

  GraylevelImageWhiteRatioBoarderRemoveOp::
      GraylevelImageWhiteRatioBoarderRemoveOp(double ratio_threshold,
                                              int white_threshold) :
      ratio_threshold_(ratio_threshold), white_threshold_(white_threshold) { }

  GrayLevelImage4Byte& GraylevelImageWhiteRatioBoarderRemoveOp::
      FilterImage(
          const GrayLevelImage4Byte& source_img) const {
    // get the binary image
    GraylevelOtsuThresholdingOp otsu_thresolding = GraylevelOtsuThresholdingOp();
    GrayLevelImage4Byte& resimg = otsu_thresolding.FilterImage(source_img);
    // find the crop rectangle
    int x1, y1, x2, y2, width, height;
    bool is_first_border = true;
    //find y
    for (int i = 0 ; i < resimg.height(); ++i) {
      // if suddently find a line larger than threshold, 
      // this is the first boarder
      if (is_first_border &&
          this->GetWhiteRatio(resimg, i, true) >= 
          this->ratio_threshold_) {
        is_first_border = false;
        y1 = i;
      } else {
        if (!is_first_border &&
            this->GetWhiteRatio(resimg, i, true) < ratio_threshold_) {
          y2 = i - 1;
          break;
        }
      }
    }
    is_first_border = true;
    //find x
    for (int i = 0 ; i < resimg.width(); ++i) {
      // if suddently find a line larger than threshold, 
      // this is the first boarder
      if (is_first_border &&
          this->GetWhiteRatio(resimg, i, false) >= 
          this->ratio_threshold_) {
        is_first_border = false;
        x1 = i;
      } else {
        double tmp = this->GetWhiteRatio(resimg, i, false);
        if (!is_first_border &&
            this->GetWhiteRatio(resimg, i, false) < ratio_threshold_) {
          x2 = i - 1;
          break;
        }
      }
    }
    width = x2 - x1;
    height = y2 - y1;
    GraylevelImageCropOp crop_op = 
        GraylevelImageCropOp(x1, y1, width, height);
    return crop_op.FilterImage(resimg);
  }

  double GraylevelImageWhiteRatioBoarderRemoveOp::GetWhiteRatio(
      const GrayLevelImage4Byte& source_img, 
      int search_index, bool is_row) const {

    int upper_limit = 0, white_count = 0, pixel_value = 0;
    if (is_row) {
      upper_limit = source_img.width();
    } else {
      upper_limit = source_img.height();
    }
    for (int i = 0; i < upper_limit; ++i) {
      if (is_row) {
        pixel_value = source_img.GetPixel(i, search_index);
      } else {
        pixel_value = source_img.GetPixel(search_index, i);
      }
      if (pixel_value > this->white_threshold_) {
          ++white_count;
        }
    }
    return white_count * 1.0 / upper_limit;
  }

  int GraylevelImageWhiteRatioBoarderRemoveOp::crop_coordinate_x() {
    return this->crop_coordinate_x_;
  }
  int GraylevelImageWhiteRatioBoarderRemoveOp::crop_coordinate_y() {
    return this->crop_coordinate_y_;
  }
  int GraylevelImageWhiteRatioBoarderRemoveOp::crop_height() {
    return this->crop_height_;
  }
  int GraylevelImageWhiteRatioBoarderRemoveOp::crop_width() {
    return this->crop_width_;
  }

} //ns  lib_img_spatial_operations