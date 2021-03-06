#include <iostream>
#include "opencv2/opencv.hpp"
#include <opencv2/imgproc/imgproc.hpp>
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


	Mat image,imagehsv,imagelab,fin_img,im0;
	image = cvLoadImage(argv[1], CV_LOAD_IMAGE_COLOR);
	//im0 = image.clone();
	//image.copyTo(im0(Rect(left, top, image.cols, image.rows)));

	//cvtColor(image, imagelab, CV_LBGR2Lab); //convert rgb to lab
	//cvtColor(image, imagehsv, CV_BGR2HSV); //convert rgb to hsv
	//cvtColor(image, imageycrcb, CV_BGR2YCrCb); //convert rgb to YCbCr
	cvtColor(image, imagehsv, CV_BGR2HSV);
	namedWindow("Original Image",CV_WINDOW_NORMAL);
	namedWindow("H",CV_WINDOW_NORMAL);
	namedWindow("B",CV_WINDOW_NORMAL);
	namedWindow("plantpix",CV_WINDOW_NORMAL);

	// Create Matrices (make sure there is an image in input!)

	Mat hsv_channel[3];
	Mat RGB_channel[3];

	imshow( "Original Image", image );


	// The actual splitting.
	split(imagehsv, hsv_channel);
	split(image, RGB_channel);
	
	imshow("H", hsv_channel[0]);

	Mat plantpix(image.rows,image.cols, CV_8UC1);
	
	imshow("B", RGB_channel[0]);
	
	RGB_channel[0].convertTo(RGB_channel[0],CV_16UC1);	
	plantpix.convertTo(plantpix, CV_16UC1);

	plantpix = RGB_channel[0];
	//imshow("plantpix", plantpix);
	//waitKey(0);


	double minVal;
	double maxVal;
	Point minLoc;
	Point maxLoc;
	
	minMaxLoc(plantpix,&minVal, &maxVal, &minLoc, &maxLoc);
	cout << "min val with RGB: " << minVal << endl;
	cout << "max val with RGB: " << maxVal << endl;
	
	imshow("H", hsv_channel[0]);	
	hsv_channel[0].convertTo(hsv_channel[0],CV_16UC1);
	add(plantpix, hsv_channel[0], plantpix);
	imshow("plantpix", plantpix);

	minMaxLoc(plantpix,&minVal, &maxVal, &minLoc, &maxLoc);
	cout << "min val with HSV: " << minVal << endl;
	cout << "max val with HSV: " << maxVal << endl;
	imshow("plantpix", plantpix);
	waitKey(0);


	divide(plantpix,2,plantpix);

	minMaxLoc(plantpix,&minVal, &maxVal, &minLoc, &maxLoc);
	cout << "min val end: " << minVal << endl;
	cout << "max val end: " << maxVal << endl;
	

		plantpix.convertTo(plantpix, CV_8UC1);
		hsv_channel[0].convertTo(hsv_channel[0],CV_8UC1);
		RGB_channel[0].convertTo(RGB_channel[0],CV_8UC1);
	

	imshow("plantpix", plantpix);
	imshow("H", hsv_channel[0]);
	imshow("B", RGB_channel[0]);
	imwrite("plantpix.png",plantpix);

	image.release();
	imagehsv.release();
	plantpix.release();

	//H from HSV and Blue from RGB is good for black
	
	


	//imshow("Blue",channel[0]);
	//imshow("Green",channel[1]);
	//imshow("Red",channel[2]);

	//imshow("H",hsv_channel[0]);
	//imshow("S",hsv_channel[1]);
	//imshow("V",hsv_channel[2]);
	//channel[0]=Mat::zeros(image.rows, image.cols, CV_8UC1);//Set blue channel to 0

	//Merging red and green channels

	//merge(channel,3,image);
	//imshow("R+G", image);
	//imwrite("dest.jpg",image);

	waitKey(0);//Wait for a keystroke in the window
	return 0;
}
