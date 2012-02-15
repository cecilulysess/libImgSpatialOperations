// testProject.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include "lib_img_spatial_operations.h"

using namespace std;
using ::lib_img_spatial_operations::GrayLevelImage4Byte;
int main(){
  int** test_arr = new int*[3];
  int element = 0;
  for (int i = 0 ; i < 3; ++i) {
    test_arr[i] = new int[3];
    for (int j = 0; j < 3; ++j) {
      test_arr[i][j] = element++;
    }
  }
  GrayLevelImage4Byte img = GrayLevelImage4Byte(3, 3, test_arr);
  cout<<img.height() <<"\t" <<img.width()<<endl;
  return 0;
}

