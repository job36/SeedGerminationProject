#include <iostream>
#include "opencv2/opencv.hpp"
#include <stdio.h>    

using namespace cv;
using namespace std;

int main( int argc, char** argv ){


	Mat image,imagehsv,imagelab,fin_img;
	image = cvLoadImage(argv[1], CV_LOAD_IMAGE_COLOR);
	//image = imread("baboon.jpg", CV_LOAD_IMAGE_COLOR);   // Read the file
	cvtColor(image, imagelab, CV_LBGR2Lab); //convert rgb to lab
	//cvtColor(image, imagehsv, CV_BGR2HSV); //convert rgb to hsv
	//cvtColor(image, imageycrcb, CV_BGR2YCrCb); //convert rgb to YCbCr
	cvtColor(image, imagehsv, CV_BGR2HSV);
	namedWindow( "Original Image", CV_WINDOW_NORMAL );// Create a window for display.
                      // Show our image inside it.

	// Create Windows
	namedWindow("Blue",CV_WINDOW_NORMAL);
	//namedWindow("Green",CV_WINDOW_NORMAL);
	//namedWindow("Red",CV_WINDOW_NORMAL);

	//namedWindow("H",CV_WINDOW_NORMAL);
	namedWindow("H",CV_WINDOW_NORMAL);
	//namedWindow("V",CV_WINDOW_NORMAL);
	namedWindow("B",CV_WINDOW_NORMAL);
	// Create Matrices (make sure there is an image in input!)

	Mat hsv_channel[3];
	Mat RGB_channel[3];
	Mat lab_channel[3];
	imshow( "Original Image", image );


	// The actual splitting.
	split(imagehsv, hsv_channel);
	split(image, RGB_channel);
	split(imagelab, lab_channel);

	//imshow("B", lab_channel[0]);
	imshow("H", hsv_channel[0]);
	imshow("Blue", RGB_channel[0]);


	namedWindow("plantpix",CV_WINDOW_NORMAL);

	Mat plantpix(image.rows,image.cols, CV_8UC1);
	
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
	cout << "min val: " << minVal << endl;
	cout << "max val: " << maxVal << endl;


	//lab_channel[2].convertTo(lab_channel[2],CV_16UC1);
	//add(plantpix, lab_channel[2], plantpix);
	//imshow("plantpix", plantpix);
	//waitKey(0);

	//minMaxLoc(plantpix,&minVal, &maxVal, &minLoc, &maxLoc);
	//cout << "min val: " << minVal << endl;
	//cout << "max val: " << maxVal << endl;
	
	hsv_channel[0].convertTo(hsv_channel[0],CV_16UC1);
	add(plantpix, hsv_channel[0], plantpix);
	imshow("plantpix", plantpix);
	waitKey(0);

	minMaxLoc(plantpix,&minVal, &maxVal, &minLoc, &maxLoc);
	cout << "min val: " << minVal << endl;
	cout << "max val: " << maxVal << endl;


	divide(plantpix,2,plantpix);

	minMaxLoc(plantpix,&minVal, &maxVal, &minLoc, &maxLoc);
	cout << "min val end: " << minVal << endl;
	cout << "max val end: " << maxVal << endl;
	

		plantpix.convertTo(plantpix, CV_8UC1);
		//lab_channel[2].convertTo(lab_channel[2],CV_8UC1);
		hsv_channel[0].convertTo(hsv_channel[0],CV_8UC1);
		RGB_channel[0].convertTo(RGB_channel[0],CV_8UC1);
	

	imshow("plantpix", plantpix);
	//imshow("B", lab_channel[2]);
	imshow("H", hsv_channel[0]);
	imshow("Blue", RGB_channel[0]);
	imwrite("PlantPix.png",plantpix);

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
