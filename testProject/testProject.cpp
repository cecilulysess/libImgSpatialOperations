// testProject.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <fstream>

#include "lib_img_spatial_operations.h"
#include "opencv_interoperators.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>


using namespace std;
using namespace cv;
using namespace lib_img_spatial_operations;
using ::opencv_interoperators::OpenCVInteroperator;

int main(int argc, char** argv){
  if( argc != 2) {
     cout <<" Usage: testProject ImageToTest" << endl;
     return -1;
  }

  cv::Mat image = cv::imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
  namedWindow( "Display Original window", CV_WINDOW_AUTOSIZE );// Create a window for display.
  imshow( "Display Original window", image );
  GrayLevelImage4Byte* img = OpenCVInteroperator::GetGrayLevelImage4ByteFromMat(&image);
  cout<<"Read input image: width: "<<img->width() <<"\tHeight" <<img->height()<<endl;
  GrayLevelImageHistogram hist = GrayLevelImageHistogram(*img);
  GrayLevelImageOp* img_op = new GraylevelImageWhiteRatioBoarderRemoveOp(0.1, 128);
  GrayLevelImage4Byte resimg = img_op->FilterImage(*img);
  cv::Mat result_image = *OpenCVInteroperator::GetMatFromGrayLevelImage4Byte(img);
  cout<<"Read input image: width: "<<result_image.size[1] <<"\tHeight" <<result_image.size[0]<<endl;
  namedWindow( "Display Result window", CV_WINDOW_AUTOSIZE );// Create a window for display.
  imshow( "Display Result window", result_image );
  waitKey(0);                                          // Wait for a keystroke in the window
  return 0;
}

