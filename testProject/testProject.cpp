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

int main(int argc, char** argv){
  if( argc != 2) {
     cout <<" Usage: testProject ImageToTest" << endl;
     return -1;
  }

  cv::Mat image = cv::imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
  GrayLevelImage4Byte* img = OpenCVInteroperator::GetGrayLevelImage4ByteFromMat(image);
  cout<<"Read input image: width: "<<img->width() <<"\tHeight:" <<img->height()<<endl;
  GrayLevelImageHistogram hist = GrayLevelImageHistogram(*img);
  OpenCVInteroperator::ShowImage(*img, "Source image");
  try {
    GraylevelImageWhiteRatioBoarderRemoveOp* img_op = 
        new GraylevelImageWhiteRatioBoarderRemoveOp(0.1, 128);
    GrayLevelImage4Byte* resimg = img_op->FilterImage(*img);
    delete resimg;
    GraylevelImageCropOp* crop_op = new GraylevelImageCropOp(
        img_op->crop_coordinate_x(),
        img_op->crop_coordinate_y(),
        img_op->crop_width(),
        img_op->crop_height()
        );
    resimg = crop_op->FilterImage(*img);
    cv::Mat* result_image = OpenCVInteroperator::GetMatFromGrayLevelImage4Byte(*resimg);
    cout<<"Result image: Width: "<<result_image->size[1] <<"\tHeight:" <<result_image->size[0]<<endl;
    cout<<"Upperleft crop point: ("<<img_op->crop_coordinate_x()<<", "<<
        img_op->crop_coordinate_y()<<"), Width:"<<img_op->crop_width()<<
        ", Height: "<<img_op->crop_height()<<endl;
    namedWindow( "Result image", CV_WINDOW_NORMAL );// Create a window for display.
    imshow( "Result image", *result_image );
    imwrite("CroppedResult.jpg", *result_image);
    waitKey(0); waitKey(0);                            // Wait for a keystroke in the window
  } catch (...) {
    cout<<"this algorithm is invalid for the input image "<<endl;
    waitKey(0);
  }
  return 0;
}

