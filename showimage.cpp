 #include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

 using namespace cv;
 using namespace std;

/** @function main */
int main( int argc, char** argv )
 {
   /// Load source image and convert it to gray
   Mat src = imread( argv[1], 1 );
   Mat src_gray;

   /// Convert image to gray and blur it
   cvtColor( src, src_gray, CV_BGR2GRAY );

   namedWindow( "Image", CV_WINDOW_NORMAL );
   imshow( "Image", src );

   namedWindow( "Gray", CV_WINDOW_NORMAL );
   imshow( "Gray", src_gray );

   waitKey(0);
   return(0);
 
 }
