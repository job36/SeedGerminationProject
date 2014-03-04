#include <cv.h>
#include <highgui.h>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>


using namespace cv;

int kernel_size = 3;
int low_threshold = 20;
int high_threshold = 100;

int main( int argc, char** argv )
{
 char* imageName = argv[1];

 Mat image;
 image = imread( imageName, 1 );

 if( argc != 2 || !image.data )
 {
   printf( " No image data \n " );
   return -1;
 }

// Mat detected_edges;
 Canny(detected_edges, detected_edges, low_threshold, high_threshold, kernel_size);

 imwrite( "Canny_Image.jpg", detected_edges );

 namedWindow( imageName, CV_WINDOW_AUTOSIZE );
 namedWindow( "Canny image", CV_WINDOW_AUTOSIZE );

 imshow( imageName, image );
 imshow( "Canny image", detected_edges );

 waitKey(0);

 return 0;
}
