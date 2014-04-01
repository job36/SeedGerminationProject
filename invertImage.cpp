#include <opencv2/opencv.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <string>
#include <iostream>

using namespace cv;
using namespace std;

int main( int argc, char** argv )
{

Mat dst,src;

src = imread(argv[1],1); //input image
imshow("original Image",src);

bitwise_not ( src, dst );

imshow("Image Changed",dst);
imwrite("inverted.png", dst);

waitKey();
}
