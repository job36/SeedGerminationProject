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
	im0 = image.clone();


	cvtColor(image, imagehsv, CV_BGR2Lab);
	namedWindow( "Original Image", CV_WINDOW_NORMAL );

	//imshow("C", cmyk[0]);

	//hsvs, cmykc, cmykm

	// Create Windows
	namedWindow("C", CV_WINDOW_NORMAL);
	namedWindow("M",CV_WINDOW_NORMAL);
	namedWindow("S",CV_WINDOW_NORMAL);
	// Create Matrices (make sure there is an image in input!)

	Mat hsv_channel[3];

	Mat cmyk_channel[4];
	imshow( "Original Image", image );


	// The actual splitting.
	split(imagehsv, hsv_channel);

	imshow("S", hsv_channel[2]);

	namedWindow("plantpix",CV_WINDOW_NORMAL);

	Mat plantpix(image.rows,image.cols, CV_8UC1);
	
	hsv_channel[2].convertTo(hsv_channel[2],CV_32F);
	divide(hsv_channel[2],255,hsv_channel[2]);	
	plantpix.convertTo(plantpix, CV_32F);

	plantpix = hsv_channel[2];
	//imshow("plantpix", plantpix);
	//waitKey(0);


	double minVal;
	double maxVal;
	Point minLoc;
	Point maxLoc;
	
	minMaxLoc(plantpix,&minVal, &maxVal, &minLoc, &maxLoc);
	cout << "min val with hsv: " << minVal << endl;
	cout << "max val with hsv: " << maxVal << endl;

	

	std::vector<cv::Mat> cmyk;
	rgb2cmyk(im0, cmyk);

	cout << "make cmyk" << endl;
	imshow("C", cmyk[2]);
	waitKey(0);

	//multiply(cmyk[0],255,cmyk[0]);
	add(plantpix, cmyk[2], plantpix);
	//cmyk[0].convertTo(cmyk[0],CV_8UC1);

	minMaxLoc(cmyk[2],&minVal, &maxVal, &minLoc, &maxLoc);
	cout << "min cmykval: " << minVal << endl;
	cout << "max cmykval: " << maxVal << endl;	

	imshow("C",cmyk[2]);
	//imshow("M", cmyk[1]);
	imshow("plantpix", plantpix);
	cout << "convert, add to plantpix and then convert back" << endl;
	waitKey(0);
	imwrite("PlantPix.png",plantpix);
	minMaxLoc(plantpix,&minVal, &maxVal, &minLoc, &maxLoc);
	cout << "min val with CMYK: " << minVal << endl;
	cout << "max val with CMYK: " << maxVal << endl;



	divide(plantpix,2,plantpix);
	multiply(plantpix,255,plantpix);

	minMaxLoc(plantpix,&minVal, &maxVal, &minLoc, &maxLoc);
	cout << "min val end: " << minVal << endl;
	cout << "max val end: " << maxVal << endl;
	

		plantpix.convertTo(plantpix, CV_8UC1);
		//lab_channel[2].convertTo(lab_channel[2],CV_8UC1);
		hsv_channel[2].convertTo(hsv_channel[2],CV_8UC1);
		//cmyk2[0].convertTo(cmyk2[0],CV_8UC1);
	

	imshow("plantpix", plantpix);
	imshow("S", hsv_channel[1]);
	imshow("C", cmyk[2]);
	//imshow("M", cmyk[1]);
	//imwrite("PlantPix.png",plantpix);

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
