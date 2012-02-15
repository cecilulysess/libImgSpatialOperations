// libImgSpatialOperating - Yanxiang Wu's implementation of many frequently
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
#ifdef _EXPORTINGLISO
   #define CLASS_DECLSPEC    __declspec(dllexport)
#else
   #define CLASS_DECLSPEC    __declspec(dllimport)
#endif


namespace lib_img_spatial_operations {
  
  // Defined in gray_level_image.cpp
  // GrayLevelImage4Byte describe a gray level image with its width and height.
  // All of the image processed in this library should be the instance of 
  // this class
  // The original information of this image is a unsigned int** 2D array
  class CLASS_DECLSPEC GrayLevelImage4Byte {
    
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

    // the content of the image
    int** image_data_;
    int* test_;
  };

  
} // namespace lib_img_spatial_operations

#endif //LIB_IMG_SPATIAL_OPERATIONS_H_