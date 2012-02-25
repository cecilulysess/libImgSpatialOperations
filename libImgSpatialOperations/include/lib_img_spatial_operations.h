// libImgSpatialOperations - Yanxiang Wu's implementation of many frequently
// used spatial image operations
// Copyright 2012 Yanxiang Wu. All right reserved
// https://github.com/cecilulysess/libImgSpatialOperations
//
// License: Apache 2.0

// Author: cosmobserver@gmail.com (Yanxiang Wu)
// First version of this project
// this header file define all the public classes and functions of this library
// due to the trick used below about the dllexport and dllimport, please 
// directly include this header file with your client program


#ifndef LIB_IMG_SPATIAL_OPERATIONS_H_
#define LIB_IMG_SPATIAL_OPERATIONS_H_

// trick to automatic import and export at both client and dll
//#ifdef LISO_CLASS_DECLSPEC
//  #undef LISO_CLASS_DECLSPEC
//#endif
#ifdef _EXPORTINGLISO
  #define LISO_CLASS_DECLSPEC    __declspec(dllexport)
#else
  #define LISO_CLASS_DECLSPEC    __declspec(dllimport)
#endif


namespace lib_img_spatial_operations {
  // Defined in gray_level_image.cpp
  // GrayLevelImage4Byte describe a gray level image with its width and height.
  // All of the image processed in this library should be the instance of 
  // this class
  // The original information of this image is a unsigned int** 2D array
  class LISO_CLASS_DECLSPEC GrayLevelImage4Byte {
    
  public:
    // A serial number used by the library to determine the code version
    static const int kSerialNumber  = 0x10000001;

    // constructor
    // Create a GrayLevelImage4Byte from a unsigned int 2D array
    // graylevels specify how many levels in this image, it will start from 0
    GrayLevelImage4Byte(int width, int height, int** image_data, int graylevels);

    // Create a GrayLevelImage4Byte from a unsigned int 2D array.
    // This will assume that it is a 256 graylevels image
    GrayLevelImage4Byte(int width, int height, int** image_data);

    // todo destructor
    ~GrayLevelImage4Byte();

    // accessors
    int height() const;
    
    int width() const;

    int gray_level() const;

    // return a read only int** array of this image
    const int* const *  image_data() const;
    // methods
    
    // get a copy of image_data
    int** GetImageData() const;

    // get the value of given pixel
    // Throws out_of_range exception if x y is larger than width or height
    int GetPixel(int x, int y) const;

  private:
    // invoked only by constructor to initialize the instance
    void Init(int** image_data);

    // the width and height of the image
    int height_, width_;
    int gray_level_;

    // inner_name of this image, used for identification purpose
    int id_;
    static int obj_counter;
    // the content of the image
    int** image_data_;
  };

//-----------------------------------------------------------------------------

  // the interface for Operating of graylevel image
  class LISO_CLASS_DECLSPEC GrayLevelImageOp {
  public:
    // A serial number used by the library to determine the code version
    static const int kSerialNumber  = 0x10000001;

    // FilterImage performing an operation at source_img and returen
    // a new image as the result. Note that this method will never change
    // the source_img
    virtual GrayLevelImage4Byte* FilterImage(
        const GrayLevelImage4Byte& source_img) const = 0;
  };

//-----------------------------------------------------------------------------
  // performing Otsu thresholding to source_img
  class LISO_CLASS_DECLSPEC GraylevelOtsuThresholdingOp : public GrayLevelImageOp {
  public:
    // A serial number used by the library to determine the code version
    static const int kSerialNumber  = 0x10000001;

    GrayLevelImage4Byte* FilterImage(
        const GrayLevelImage4Byte& source_img) const;
  };

//-----------------------------------------------------------------------------
  // performing Image crop operation to source_img
  class LISO_CLASS_DECLSPEC GraylevelImageCropOp : public GrayLevelImageOp {
  public:
    // A serial number used by the library to determine the code version
    static const int kSerialNumber  = 0x10000001;

    // constructor, setting the crop parameter
    GraylevelImageCropOp(int x, int y, int width, int height);

    // conduct the crop operation
    // throw invalid_argument if the parameter is invalid
    GrayLevelImage4Byte* FilterImage(
        const GrayLevelImage4Byte& source_img) const;
  private:
    //crop parameter
    int x_, y_, width_, height_;
  };


//-----------------------------------------------------------------------------
  // a histogram for gray level image
  class LISO_CLASS_DECLSPEC GrayLevelImageHistogram {
  public:
    // A serial number used by the library to determine the code version
    static const int kSerialNumber  = 0x10000001;

    // Constructor:
    // create a histogram of given image
    GrayLevelImageHistogram(const GrayLevelImage4Byte& image);

    // accessor
    
    // get the histogram
    const int* histogram() const;

    // get the normalized histogram
    const double* normalized_histogram() const;

    // get the gray level of this histogram
    int gray_level() const;

    #ifdef _DEBUG
    // debug using only, this will export the histogram to ./filename
    void OutputHistogram(char* filename);
    #endif
  private:
    int* histogram_;
    double* normalized_histogram_;
    int gray_level_;

  };

//-----------------------------------------------------------------------------
  // Remove the boarder of a image that contains a rectangle object at the 
  // center
  // Typically, this would be a calibarited scanned document 
  class LISO_CLASS_DECLSPEC GraylevelImageWhiteRatioBoarderRemoveOp : 
      public GrayLevelImageOp {
  public:
    // A serial number used by the library to determine the code version
    static const int kSerialNumber  = 0x10000001;

    // constructor, setting the ratio_threshold such that when the white ratio
    // is larger than it will be determined as a boarder line
    // if the value of pixel >= white_threshold then it will be trate as 
    // white pixel
    GraylevelImageWhiteRatioBoarderRemoveOp(double ratio_threshold,
                                            int white_threshold);

    // accessors
    int crop_coordinate_x();
    int crop_coordinate_y();
    int crop_width();
    int crop_height();

    // receiving a gray level image and applying Otsu thresholding to get
    // the binarized image of the source_img, and then conduce the row and 
    // column based white pixel statistic, and crop the source_img to a new
    // image as return
    // throw invalid_argument if the parameter is invalid
    // this method can only operating graylevel image, however,
    // if you want to use the information for other purpose, you can
    // use the accessor to the the crop coordinates;
    // throw invalid_argument exception if the source_img can not find 
    // a valid border
    GrayLevelImage4Byte* FilterImage(
        const GrayLevelImage4Byte& source_img) const;
  private:
    // get the white ratio of given row or column at search_index
    // if !is_row then is column
    double GetWhiteRatio(const GrayLevelImage4Byte& source_img, 
                         int search_index, bool is_row) const ;
    //white ratio threshold
    double ratio_threshold_;
    int white_threshold_;

    // store the crop coordinate and width and height for other usage
    // Conceptual constness, once you filter the image, this operation
    // should provides the new x, y coordinate and width and height
    mutable int crop_coordinate_x_, crop_coordinate_y_, crop_width_, crop_height_;
  };

} // namespace lib_img_spatial_operations

#ifdef LISO_CLASS_DECLSPEC
  #undef LISO_CLASS_DECLSPEC
#endif

#endif //LIB_IMG_SPATIAL_OPERATIONS_H_