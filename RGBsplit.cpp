#include <iostream>
#include "opencv2/opencv.hpp"
#include <stdio.h>    

using namespace cv;
using namespace std;

	// Covert RGB to CMYK using the formula from
// http://rapidtables.com/convert/color/rgb-to-cmyk.htm
void rgb2cmyk(cv::Mat& src, std::vector<cv::Mat>& cmyk){
    CV_Assert(src.type() == CV_8UC3);

    cmyk.clear();
    for (int i = 0; i < 4; ++i)
        cmyk.push_back(cv::Mat(src.size(), CV_32F));

    for (int i = 0; i < src.rows; ++i)
    {
        for (int j = 0; j < src.cols; ++j)
        {
            cv::Vec3b p = src.at<cv::Vec3b>(i,j);

            float r = p[2] / 255.;
            float g = p[1] / 255.;
            float b = p[0] / 255.;
            float k = (1 - std::max(std::max(r,g),b));

            cmyk[0].at<float>(i,j) = (1 - r - k) / (1 - k); 
            cmyk[1].at<float>(i,j) = (1 - g - k) / (1 - k);
            cmyk[2].at<float>(i,j) = (1 - b - k) / (1 - k);
            cmyk[3].at<float>(i,j) = k;
        }
    }
}


int main( int argc, char** argv ){

	Mat image,imagehsv,fin_img;
	image = cvLoadImage(argv[1], CV_LOAD_IMAGE_COLOR);

	std::vector<cv::Mat> cmyk;
	rgb2cmyk(image, cmyk);

	//cvtColor(image, imagehsv, CV_BGR2HSV);
	namedWindow( "Original Image", CV_WINDOW_NORMAL );
	namedWindow( "C", CV_WINDOW_NORMAL );

	Mat channel[3];
	imshow( "Original Image", image);


	//split(cmyk, channel);

	imshow("C",cmyk[2]);


	waitKey(0);//Wait for a keystroke in the window
	return 0;
}

