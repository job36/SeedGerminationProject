#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>

using namespace cv;

/** @function main */
int main(int argc, char** argv)
{
  Mat src, src_gray;

  /// Read the image
  src = imread( argv[1], 1 );

  if( !src.data )
    { return -1; }

  /// Convert it to gray
  cvtColor( src, src_gray, CV_BGR2GRAY );

  /// Reduce the noise so we avoid false circle detection
  GaussianBlur( src_gray, src_gray, Size(9, 9), 2, 2 );

  vector<Vec3f> circles;

  /// Apply the Hough Transform to find the circles
  HoughCircles( src_gray, circles, CV_HOUGH_GRADIENT, 1, src_gray.rows/8, 50, 30,80, 400 );

  //creating a new image
  Mat maskimage(src.rows, src.cols, CV_8UC3);

  //set background to black
  maskimage.setTo(Scalar(0,0,0));

  /// Draw the circles detected
  for( size_t i = 0; i < circles.size(); i++ )
  {

      Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
      int radius = cvRound(circles[i][2]);
      // circle center
      circle( maskimage, center, 3, Scalar(255,255,255), -1, 8, 0 );
      // circle outline
      circle( maskimage, center, radius, Scalar(255,255,255), -3, 8, 0 );
   }

  /// Show your results
  namedWindow( "Hough Circle Transform Demo", CV_WINDOW_NORMAL );
  namedWindow( "Test", CV_WINDOW_NORMAL );
  imshow( "Hough Circle Transform Demo", src );
  imshow( "Test", maskimage);
  std::cout<<"Amount of circles: "<<circles.size()<<std::endl;

  waitKey(0);
  return 0;
}

