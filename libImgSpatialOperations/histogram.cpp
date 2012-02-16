// libImgSpatialOperations - Yanxiang Wu's implementation of many frequently
// used spatial image operations
// Copyright 2012 Yanxiang Wu. All right reserved
// https://github.com/cecilulysess/libImgSpatialOperations
//
// License: Apache 2.0

// Author: cosmobserver@gmail.com (Yanxiang Wu)
// First version of this project
// This file implement the histogram classes

#include "include/lib_img_spatial_operations.h"

#ifdef _DEBUG
  #include <fstream>
  using namespace std;
#endif

namespace lib_img_spatial_operations {
  GrayLevelImageHistogram::GrayLevelImageHistogram(
      const GrayLevelImage4Byte& image) :
      gray_level_(image.gray_level()){
    
    int total_pixel_number = image.height() * image.width();
    // init the data member
    this->histogram_ = new int[gray_level_];
    this->normalized_histogram_ = new double[gray_level_];
    for (int i = 0; i < gray_level_; ++i) {
      this->histogram_[i] = 0;
      this->normalized_histogram_[i] = 0;
    }
    // calculating the histogram
    for (int i = 0; i < image.height(); ++i) {
      for (int j = 0; j < image.width(); ++j) {
        this->histogram_[image.GetPixel(j, i)] += 1;
      }
    }
    for (int i = 0; i < gray_level_; ++i) {
      this->normalized_histogram_[i] = 
        this->histogram_[i] * 1.0 / total_pixel_number;
    }
  }

  int GrayLevelImageHistogram::gray_level() const {
    return this->gray_level_;
  }

  const int* GrayLevelImageHistogram::histogram() const {
    return this->histogram_;
  }

  const double* GrayLevelImageHistogram::normalized_histogram() const {
    return this->normalized_histogram_;
  }

  #ifdef _DEBUG
    // debug using only, this will export the histogram to ./filename
    void GrayLevelImageHistogram::OutputHistogram(char* filename){
      ofstream ofs(filename);
      for (int i = 0; i < this->gray_level_; ++i) {
        ofs<<this->histogram_[i]<<',';
      }
      ofs<<endl;
      for (int i = 0; i < this->gray_level_; ++i) {
        ofs<<this->normalized_histogram_[i]<<',';
      }
      ofs<<endl;
      for (int i = 0; i < this->gray_level_; ++i) {
        ofs<<i<<":";
        for ( int j = 0; j < (int) (this->normalized_histogram_[i]*100); ++j){
          ofs<<"#";
        }
        ofs<<'\n';
      }
      ofs.close();
    }
  #endif

} //ns lib_img_spatial_operations