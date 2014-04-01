#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

/**  @function main */
int main( int argc, char** argv )
{
  Mat src, dst, ycrcb;

  char* source_window = "Source image";
  char* equalized_window = "Equalized Image";

  /// Load image
  src = imread( argv[1], 1 );

  if( !src.data )
    { cout<<"Usage: ./Histogram_Demo <path_to_image>"<<endl;
      return -1;}

  /// Convert to grayscale   YCrCb
  cvtColor( src, ycrcb, CV_BGR2YCrCb );

  vector<Mat> channels;
  split(ycrcb,channels);

  /// Apply Histogram Equalization
  equalizeHist( channels[0], channels[0] );
  equalizeHist( channels[1], channels[1] );
  equalizeHist( channels[2], channels[2] );

  Mat result;
  merge(channels,ycrcb);

  cvtColor( ycrcb, result, CV_YCrCb2BGR );

  /// Display results
  namedWindow( source_window, CV_WINDOW_NORMAL );
  namedWindow( equalized_window, CV_WINDOW_NORMAL );

  imshow( source_window, src );
  imshow( equalized_window, result );
  imwrite( "HistoEqual.png", result );

  /// Wait until user exits the program
  waitKey(0);

  return 0;
}

