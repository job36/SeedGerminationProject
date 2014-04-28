#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

/**  @function main */
int main( int argc, char** argv )
{
  Mat src, dst;

  char* source_window = "Source image";
  char* equalized_window = "Equalized Image";

  /// Load image
  src = imread( argv[1], CV_LOAD_IMAGE_COLOR );

  if( !src.data )
    { cout<<"Usage: ./Histogram_Demo <path_to_image>"<<endl;
      return -1;}

  /// Convert to grayscale
  cvtColor( src, src, CV_BGR2GRAY );

  /// Convert to grayscale
  //cvtColor( src, src, CV_BGR2HSV );

  /// Apply Histogram Equalization
  equalizeHist( src, dst );

  //cvtColor( dst, dst, CV_HSV2BGR );

  /// Display results
  namedWindow( source_window, CV_WINDOW_NORMAL );
  namedWindow( equalized_window, CV_WINDOW_NORMAL );

  imshow( source_window, src );
  imshow( equalized_window, dst );
  imwrite( "HistoEqual.png", dst );

  /// Wait until user exits the program
  waitKey(0);

  return 0;
}

