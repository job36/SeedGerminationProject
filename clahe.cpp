#include <opencv2/opencv.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <string>
#include <iostream>
#include <cstdlib>
#include "cxcore.h"


using namespace cv;
using namespace std;
using cv::CLAHE;


int main( int argc, char** argv )
{
Mat m= imread(argv[1],CV_LOAD_IMAGE_GRAYSCALE); //input image
imshow("dogeGRAYSCALE",m);

Ptr<CLAHE> clahe = createCLAHE();
clahe->setClipLimit(4);

Mat dst;
dst = m;
clahe->apply(m,dst);
imshow("doge_CLAHE",dst);
imwrite("clah.png", dst);

waitKey();
}
