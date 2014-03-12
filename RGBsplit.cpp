#include <iostream>
#include "opencv2/opencv.hpp"
#include <stdio.h>    

using namespace cv;
using namespace std;

int main( int argc, char** argv ){


	Mat image,imagehsv,fin_img;
	image = cvLoadImage(argv[1], CV_LOAD_IMAGE_COLOR);
	//image = imread("baboon.jpg", CV_LOAD_IMAGE_COLOR);   // Read the file
	//cvtColor(image, imagelab, CV_LBGR2Lab); //convert rgb to lab
	//cvtColor(image, imagehsv, CV_BGR2HSV); //convert rgb to hsv
	//cvtColor(image, imageycrcb, CV_BGR2YCrCb); //convert rgb to YCbCr
	cvtColor(image, imagehsv, CV_BGR2XYZ);
	namedWindow( "Original Image", CV_WINDOW_NORMAL );// Create a window for display.
                      // Show our image inside it.

	// Create Windows
	//namedWindow("Blue",CV_WINDOW_NORMAL);
	//namedWindow("Green",CV_WINDOW_NORMAL);
	//namedWindow("Red",CV_WINDOW_NORMAL);

	namedWindow("H",CV_WINDOW_NORMAL);
	namedWindow("S",CV_WINDOW_NORMAL);
	namedWindow("V",CV_WINDOW_NORMAL);

	// Create Matrices (make sure there is an image in input!)

	Mat channel[3];
	imshow( "Original Image", image );


	// The actual splitting.
	split(imagehsv, channel);

	//imshow("Blue",channel[0]);
	//imshow("Green",channel[1]);
	//imshow("Red",channel[2]);

	imshow("H",channel[0]);
	imshow("S",channel[1]);
	imshow("V",channel[2]);
	//channel[0]=Mat::zeros(image.rows, image.cols, CV_8UC1);//Set blue channel to 0

	//Merging red and green channels

	//merge(channel,3,image);
	//imshow("R+G", image);
	//imwrite("dest.jpg",image);

	waitKey(0);//Wait for a keystroke in the window
	return 0;
}
