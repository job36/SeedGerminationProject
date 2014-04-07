#include <iostream>
#include "opencv2/opencv.hpp"
#include <opencv2/imgproc/imgproc.hpp>
#include <stdio.h>
#include <fstream>

using namespace cv;
using namespace std;

int main( int argc, char** argv ){

char strStartPath[50];
char strStartPathMinus[50];
char strEndPath[50];

  std::vector <std::string> words; // Vector to hold our words read
  std::string str; // Temp string to
  std::cout << "Read from a file!" << std::endl;
  std::ifstream fin("masks.txt"); // Open it up!

  while (fin >> str){
    words.push_back(str);
  }
  fin.close();


 for (int i = 1; i < words.size(); ++i){

const char* imagenameminus = words.at(i-1).c_str();

const char* imagename = words.at(i).c_str();
std::cout<<"Image Name: "<< imagename << std::endl;
sprintf(strStartPath, "MasksStart/%s", imagename);
	  sprintf(strStartPathMinus, "MasksStart/%s", imagenameminus);
sprintf(strEndPath, "ChannelEnd/%s", imagename);
std::cout<<"Start Path: "<< strStartPath << std::endl;
std::cout<<"End Path: "<< strEndPath << std::endl;

Mat image = cvLoadImage(strStartPath, CV_LOAD_IMAGE_COLOR);
Mat imageminus = cvLoadImage(strStartPathMinus, CV_LOAD_IMAGE_COLOR);

if( !image.data )
{ return -1; }

Mat imagehsv;
Mat imagehsvminus;

cvtColor(image, imagehsv, CV_BGR2HSV);
cvtColor(imageminus, imagehsvminus, CV_BGR2HSV);
// Create Matrices (make sure there is an image in input!)

Mat hsv_channel[3];
Mat RGB_channel[3];
Mat hsv_channel_minus[3];
Mat RGB_channel_minus[3];

imshow( "Original Image", image );


// The actual splitting.
split(imagehsv, hsv_channel);
split(image, RGB_channel);
split(imagehsvminus, hsv_channel_minus);
split(imageminus, RGB_channel_minus);

Mat plantpix(image.rows,image.cols, CV_8UC1);

RGB_channel[0].convertTo(RGB_channel[0],CV_16UC1);	
plantpix.convertTo(plantpix, CV_16UC1);

plantpix = RGB_channel[0];
//imshow("plantpix", plantpix);
//waitKey(0);

	RGB_channel_minus[0].convertTo(RGB_channel_minus[0],CV_16UC1);
	add(plantpix, RGB_channel_minus[0], plantpix);


double minVal;
double maxVal;
Point minLoc;
Point maxLoc;

minMaxLoc(plantpix,&minVal, &maxVal, &minLoc, &maxLoc);
cout << "min val with RGB: " << minVal << endl;
cout << "max val with RGB: " << maxVal << endl;

hsv_channel[0].convertTo(hsv_channel[0],CV_16UC1);
add(plantpix, hsv_channel[0], plantpix);
imshow("plantpix", plantpix);

	hsv_channel_minus[0].convertTo(hsv_channel_minus[0],CV_16UC1);
	add(plantpix, hsv_channel_minus[0], plantpix);

minMaxLoc(plantpix,&minVal, &maxVal, &minLoc, &maxLoc);
cout << "min val with HSV: " << minVal << endl;
cout << "max val with HSV: " << maxVal << endl;
imshow("plantpix", plantpix);
//waitKey(0);


divide(plantpix,4,plantpix);

minMaxLoc(plantpix,&minVal, &maxVal, &minLoc, &maxLoc);
cout << "min val end: " << minVal << endl;
cout << "max val end: " << maxVal << endl;


plantpix.convertTo(plantpix, CV_8UC1);
hsv_channel[0].convertTo(hsv_channel[0],CV_8UC1);
RGB_channel[0].convertTo(RGB_channel[0],CV_8UC1);


imshow("plantpix", plantpix);
imshow("H", hsv_channel[0]);
imshow("Blue", RGB_channel[0]);
imwrite(strEndPath,plantpix);


hsv_channel[3].release();
RGB_channel[3].release();
hsv_channel_minus[3].release();
RGB_channel_minus[3].release();
image.release();
imagehsv.release();
imageminus.release();
imagehsvminus.release();
plantpix.release();

//H from HSV and Blue from RGB is good for black
}
//waitKey(0);//Wait for a keystroke in the window
return 0;

}
