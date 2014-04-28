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
	char strStartPathMinusTwo[50];
	char strEndPath[50];

	//find all of the image names and save to a vector

	std::vector <std::string> words; // Vector to hold our words read
	std::string str; // Temp string to
	std::cout << "Read from a file!" << std::endl;
	std::ifstream fin("masks.txt"); // Open it up!

	while (fin >> str){ 
		words.push_back(str);
	}
	fin.close();

	//Mat's and consts used

	Mat hsv_channel[3];
	Mat hsv_channel_minus[3];
	Mat hsv_channel_minus_two[3];
	Mat RGB_channel[3];
	Mat RGB_channel_minus[3];
	Mat RGB_channel_minus_two[3];
	Mat hsv_channel_minus_three[3];
	Mat RGB_channel_minus_three[3];
	Mat hsv_channel_minus_four[3];
	Mat RGB_channel_minus_four[3];
	Mat hsv_channel_minus_five[3];
	Mat RGB_channel_minus_five[3];


	Mat image, imageminus, imageminustwo,imageminusthree, imagehsv, imagehsvminus, imagehsvminustwo, imagehsvminusthree,imageminusfour, imagehsvminusfour, imageminusfive, imagehsvminusfive;

	const char* imagename;
	const char* imagenameminus;
	const char* imagenameminustwo;

	for (int i = 0; i < words.size(); ++i){

		//check to stop the earlier images breaking things	
	
		//if( i == 0){
		//	imagenameminus = words.at(i).c_str();
			//imagenameminustwo = words.at(i).c_str();
		//} //else if( i == 1 ){ 
		//	imagenameminus = words.at(i).c_str();
		//	imagenameminustwo = words.at(i-1).c_str();
		//} else {
		//	imagenameminus = words.at(i-1).c_str();
		//	imagenameminustwo = words.at(i-2).c_str();		

		//}

	
		//sort out filenames and paths to save and load from
		  imagename = words.at(i).c_str();
		  //std::cout<<"Image Name: "<< imagename << std::endl;
		  sprintf(strStartPath, "MasksStart/%s", imagename);
		  //sprintf(strStartPathMinus, "MasksStart/%s", imagenameminus);
		  //sprintf(strStartPathMinusTwo, "MasksStart/%s", imagenameminustwo);
		  sprintf(strEndPath, "ChannelEnd/%s", imagename);
		  //std::cout<<"Start Path: "<< strStartPath << std::endl;
		  std::cout<<"End Path: "<< strEndPath << std::endl;


		//load in images
		  image = cvLoadImage(strStartPath, CV_LOAD_IMAGE_COLOR);
		  //imageminus = cvLoadImage(strStartPathMinus, CV_LOAD_IMAGE_COLOR);
		  //imageminustwo = cvLoadImage(strStartPathMinusTwo, CV_LOAD_IMAGE_COLOR);

		/*if(i == 0){
			imageminus = image.clone();
			imageminustwo = image.clone();
			imageminusthree = image.clone();
			//imageminusfour = image.clone();
			//imageminusfive = image.clone();
		} else if(i == 1){
			imageminus = image.clone();
			imageminustwo = imageminus.clone();
			imageminusthree = imageminus.clone();
			//imageminusfour = imageminus.clone();
			//imageminusfive = imageminus.clone();
		}else if(i == 2){
			imageminus = image.clone();
			imageminustwo = imageminus.clone();
			imageminusthree = imageminustwo.clone();
			//imageminusfour = imageminustwo.clone();
			//imageminusfive = imageminustwo.clone();
		}*//*else if(i == 3){
			imageminus = image.clone();
			imageminustwo = imageminus.clone();
			imageminusthree = imageminustwo.clone();
			imageminusfour = imageminusthree.clone();
			imageminusfive = imageminusthree.clone();
		}else if(i == 4){
			imageminus = image.clone();
			imageminustwo = imageminus.clone();
			imageminusthree = imageminustwo.clone();
			imageminusfour = imageminusthree.clone();
			imageminusfive = imageminusfour.clone();
		}*/
		

		  if( !image.data )
		    { return -1; }

		//get hsv components in the images
		cvtColor(image, imagehsv, CV_BGR2HSV);
		//cvtColor(imageminus, imagehsvminus, CV_BGR2HSV);
		//cvtColor(imageminustwo, imagehsvminustwo, CV_BGR2HSV);
		//cvtColor(imageminusthree, imagehsvminusthree, CV_BGR2HSV);
		//cvtColor(imageminusfour, imagehsvminusfour, CV_BGR2HSV);
		//cvtColor(imageminusfive, imagehsvminusfive, CV_BGR2HSV);


		// The actual splitting.
		split(imagehsv, hsv_channel);
		//split(imagehsvminus, hsv_channel_minus);
		//split(imagehsvminustwo, hsv_channel_minus_two);
		split(image, RGB_channel);
		//split(imageminus, RGB_channel_minus);
		//split(imageminustwo, RGB_channel_minus_two);
		//split(imagehsvminusthree, hsv_channel_minus_three);
		//split(imageminusthree, RGB_channel_minus_three);
		//split(imagehsvminusfour, hsv_channel_minus_four);
		//split(imageminusfour, RGB_channel_minus_four);
		//split(imagehsvminusfive, hsv_channel_minus_five);
		//split(imageminusfive, RGB_channel_minus_five);

		//set plantpix to equal the B component of RGB in the first image
		Mat plantpix(image.rows,image.cols, CV_8UC1);
	
		RGB_channel[0].convertTo(RGB_channel[0],CV_16UC1);	
		plantpix.convertTo(plantpix, CV_16UC1);

		plantpix = RGB_channel[0];

		//add remaining RGB channels

		//RGB_channel_minus[0].convertTo(RGB_channel_minus[0],CV_16UC1);
		//add(plantpix, RGB_channel_minus[0], plantpix);
		//RGB_channel_minus_two[0].convertTo(RGB_channel_minus_two[0],CV_16UC1);
		//add(plantpix, RGB_channel_minus_two[0], plantpix);
		//RGB_channel_minus_three[0].convertTo(RGB_channel_minus_three[0],CV_16UC1);
		//add(plantpix, RGB_channel_minus_three[0], plantpix);
		//RGB_channel_minus_four[0].convertTo(RGB_channel_minus_four[0],CV_16UC1);
		//add(plantpix, RGB_channel_minus_four[0], plantpix);
		//RGB_channel_minus_five[0].convertTo(RGB_channel_minus_five[0],CV_16UC1);
		//add(plantpix, RGB_channel_minus_five[0], plantpix);
	
		//add HSV - H channels

		hsv_channel[0].convertTo(hsv_channel[0],CV_16UC1);
		add(plantpix, hsv_channel[0], plantpix);

		//hsv_channel_minus[0].convertTo(hsv_channel_minus[0],CV_16UC1);
		//add(plantpix, hsv_channel_minus[0], plantpix);
		//hsv_channel_minus_two[0].convertTo(hsv_channel_minus_two[0],CV_16UC1);
		//add(plantpix, hsv_channel_minus_two[0], plantpix);
		//hsv_channel_minus_three[0].convertTo(hsv_channel_minus_three[0],CV_16UC1);
		//add(plantpix, hsv_channel_minus_three[0], plantpix);
		//hsv_channel_minus_four[0].convertTo(hsv_channel_minus_four[0],CV_16UC1);
		//add(plantpix, hsv_channel_minus_four[0], plantpix);
		//hsv_channel_minus_five[0].convertTo(hsv_channel_minus_five[0],CV_16UC1);
		//add(plantpix, hsv_channel_minus_five[0], plantpix);

		//divide by number of channels and convert back to format within 0-255

		divide(plantpix,2,plantpix);
		plantpix.convertTo(plantpix, CV_8UC1);


	
		//save image to end location
		imwrite(strEndPath,plantpix);

		//try and free up images so that program doesn't crash

		//imageminus = image.clone();
		//imageminustwo = imageminus.clone();
		//imageminusthree = imageminustwo.clone();
		//imageminusfour = imageminusthree.clone();
		//imageminusfive = imageminusfour.clone();

		//cvReleaseImage( &image );
		//cvReleaseImage( &imageminus );
		//cvReleaseImage( &imageminustwo );

	
		//hsv_channel[3].release();
		//hsv_channel_minus[3].release();
		//hsv_channel_minus_two[3].release();
		//RGB_channel[3].release();
		//RGB_channel_minus[3].release();
		//RGB_channel_minus_two[3].release();
		//image.release();
		//imagehsv.release();
		//imageminus.release();
		//imagehsvminus.release();
		//imageminustwo.release();
		//imagehsvminustwo.release();
		plantpix.release();


	}

	return 0;

}
