// testProject.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include "lib_img_spatial_operations.h"
#include <fstream>

using namespace std;
using namespace lib_img_spatial_operations;
int main(){

  ifstream iff("D:\\Dropbox\\OtherPrograms\\CV\\Others\\Border Remover\\libImgSpatialOperations\\Debug\\testImage.dat");
  int width, height, graylevel;
  iff>>width>>height>>graylevel;
  int** test_img = new int*[height];
  for (int i = 0 ; i < height; ++i) {
    test_img[i] = new int[width];
    for (int j = 0; j < width; ++j) {
      iff>>test_img[i][j];
    }
  }
  iff.close();
  GrayLevelImage4Byte& img = GrayLevelImage4Byte(width, height, test_img);
  cout<<img.height() <<"\t" <<img.width()<<endl;
  GrayLevelImageHistogram hist = GrayLevelImageHistogram(img);
  hist.OutputHistogram("testImghist.txt");
  GrayLevelImageOp* img_op = new GraylevelImageWhiteRatioBoarderRemoveOp(0.1, 128);
  GrayLevelImage4Byte resimg = img_op->FilterImage(img);
  ofstream off("resultImg.txt");
  for (int i = 0; i < resimg.height(); ++i) {
    for (int j = 0; j < resimg.width(); ++j) {
      off<<resimg.GetPixel(j,i)<<',';
    }
    off<<endl;
  }
  off.close();
  return 0;
}

