#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>

using namespace cv;

void Sharpen(const Mat& myImage,Mat& Result)
{
    CV_Assert(myImage.depth() == CV_8U);  // accept only uchar images

    Result.create(myImage.size(),myImage.type());
    const int nChannels = myImage.channels();

    for(int j = 1 ; j < myImage.rows-1; ++j)
    {
        const uchar* previous = myImage.ptr<uchar>(j - 1);
        const uchar* current  = myImage.ptr<uchar>(j    );
        const uchar* next     = myImage.ptr<uchar>(j + 1);

        uchar* output = Result.ptr<uchar>(j);

        for(int i= nChannels;i < nChannels*(myImage.cols-1); ++i)
        {
            *output++ = saturate_cast<uchar>(5*current[i]
                         -current[i-nChannels] - current[i+nChannels] - previous[i] - next[i]);
        }
    }

    Result.row(0).setTo(Scalar(0));
    Result.row(Result.rows-1).setTo(Scalar(0));
    Result.col(0).setTo(Scalar(0));
    Result.col(Result.cols-1).setTo(Scalar(0));
}

/** @function main */
int main(int argc, char** argv)
{
  Mat src, frame;


  /// Read the image
  src = imread( argv[1], 1 );
  frame = src;

  if( !src.data )
    { return -1; }

  src = Sharpen(src, frame);

  std::cout<<"Showing Results: "<<std::endl;
  /// Show your results
  //namedWindow( "frame", CV_WINDOW_NORMAL );
  namedWindow( "src", CV_WINDOW_NORMAL );
  //imshow( "frame", frame );
  imshow( "src", src);
  
  std::cout<<"Ends: "<<std::endl;
  waitKey(0);
  return 0;
}

