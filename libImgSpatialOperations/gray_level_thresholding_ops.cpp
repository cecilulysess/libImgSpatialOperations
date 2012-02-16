// libImgSpatialOperations - Yanxiang Wu's implementation of many frequently
// used spatial image operations
// Copyright 2012 Yanxiang Wu. All right reserved
// https://github.com/cecilulysess/libImgSpatialOperations
//
// License: Apache 2.0

// Author: cosmobserver@gmail.com (Yanxiang Wu)
// First version of this project
// Implementing the thresholding operations

#include "include/lib_img_spatial_operations.h"
#include <cmath>
#include <fstream>
using namespace std;

namespace lib_img_spatial_operations {
  GrayLevelImage4Byte& GraylevelOtsuThresholdingOp::FilterImage(
      GrayLevelImage4Byte& source_img) const{

    GrayLevelImageHistogram histo = GrayLevelImageHistogram(source_img);
    int graylevel = histo.gray_level();
    int best_threshold = 1, current_threshold = 1;
    double max_sigma_between = 0.0, sigma_between = 0.0;
    const double* normalized_histogram = histo.normalized_histogram();
    // ¦Ø_k = ¡Æ_0^k (Pi) stand for the probablity of graylevel is class 0
    double omega_K = normalized_histogram[0];
    // ¦Ì_T = ¡Æ i*Pi stand for the average of total pixels' graylevel
    double mu_T = 0.0;
    // ¦Ì_K = ¡Æ_0^k (i*Pi) stand for the average of total pixels of class 0's graylevel
    double mu_K = 0.0; // mu_K(0) = 0 * P0 = 0
    for (int i = 0; i < graylevel; ++i) {
      mu_T += (i*normalized_histogram[i]);
    }
    ofstream off("sigmab.txt");

    // find the best threshold value
    for (;current_threshold < graylevel - 1; ++current_threshold) {
      // check the omega_K in case of the occurancy of number/epsilon = infinit
      if (omega_K < 1e-6 || (1 - omega_K) < 1e-6) {
        continue;
      }
      // calculate the sigma_between
      sigma_between = std::pow( mu_T * omega_K - mu_K, 2) /
                      (omega_K * (1 - omega_K));
      if (sigma_between > max_sigma_between) {
        max_sigma_between = sigma_between;
        best_threshold = current_threshold;
      }

      
      off<<sigma_between<<",";

      //update the four variables for next round
      omega_K += normalized_histogram[current_threshold];
      mu_K += current_threshold * normalized_histogram[current_threshold];
    }
    off.close();
    // generate the new binary image
    int** new_img = new int*[source_img.height()];
    for (int i = 0; i < source_img.height(); ++i) {
      new_img[i] = new int[source_img.width()];
      for (int j = 0; j < source_img.width(); ++j) {
        if ( source_img.GetPixel(j, i) > best_threshold ) {
          new_img[i][j] = 255;
        } else {
          new_img[i][j] = 0;
        }
      }
    }
    GrayLevelImage4Byte* res = new GrayLevelImage4Byte(
        source_img.width(),source_img.height(), new_img);
    return *res;
  }
}// ns lib_img_spatial_operations