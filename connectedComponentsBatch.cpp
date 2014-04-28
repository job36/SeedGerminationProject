#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <cstdlib> 

using namespace cv;
using namespace std;

int thresh = 10;
int max_thresh = 255;
RNG rng(12345);
int amount = 0;
int number = 0;
int minimum =0;
Mat src; Mat src_gray;
char strStartPath[50];
char strEndPath[50];
char strExample[50];
/// Function header
void thresh_callback(int, void* );

/** @function main */
int main( int argc, char** argv )
{

	minimum = atoi(argv[1]);

	//istringstream ss(argv[1]);
	//int test;
	//if (!(ss >> test))
    	//cerr << "Invalid number " << argv[1] << '\n';

	std::vector <std::string> words; // Vector to hold our words read
	std::string str; // Temp string to
	std::cout << "Read from a file!" << std::endl;
	std::ifstream fin("masks.txt"); // Open it up!

	while (fin >> str){ 
		words.push_back(str);
	}
	fin.close();

	sprintf(strExample, "Examples/example%d.txt", minimum);

	ofstream myfile;
	myfile.open (strExample);
	//myfile << "Writing this to a file.\n";
	//myfile.close();	

	for (int i = 0; i < words.size(); ++i){


		const char* imagename = words.at(i).c_str();
		std::cout<<"Image Name: "<< imagename << std::endl;
		sprintf(strStartPath, "InvertedEnd/%s", imagename);
		sprintf(strEndPath, "ConnectedEnd/%s", imagename);
		std::cout<<"Start Path: "<< strStartPath << std::endl;
		std::cout<<"End Path: "<< strEndPath << std::endl;

		/// Load source image and convert it to gray
		src = imread( strStartPath, 1 );

		/// Convert image to gray and blur it
		cvtColor( src, src_gray, CV_BGR2GRAY );
		blur( src_gray, src_gray, Size(3,3) );

		/// Create Window
		//char* source_window = "Source";
		//namedWindow( source_window, CV_WINDOW_NORMAL );
		//imshow( source_window, src );

		//createTrackbar( " Threshold:", "Source", &thresh, max_thresh, thresh_callback );
		thresh_callback( 0, 0 );
		
		number++;
		myfile <<number << " " << amount << "\n";
		amount = 0;

		//src.release();
		//src_gray.release();

		//waitKey(0);
		//return(0);
	}
	myfile.close();

}

/** @function thresh_callback */
void thresh_callback(int, void* )
{
	Mat threshold_output;
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;

	/// Detect edges using Threshold
	threshold( src_gray, threshold_output, thresh, 255, THRESH_BINARY );
	/// Find contours
	findContours( threshold_output, contours, hierarchy, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

	/// Approximate contours to polygons + get bounding rects and circles
	vector<vector<Point> > contours_poly( contours.size() );
	vector<Rect> boundRect( contours.size() );
	vector<Point2f>center( contours.size() );
	vector<float>radius( contours.size() );

	for( int i = 0; i < contours.size(); i++ ) { 

		if((contours[i].size() < 500) && (contours[i].size() > minimum)){
			approxPolyDP( Mat(contours[i]), contours_poly[i], 3, true );
			boundRect[i] = boundingRect( Mat(contours_poly[i]) );
			minEnclosingCircle( (Mat)contours_poly[i], center[i], radius[i] );
			amount++;
		}

	}
	std::cout << "Amount: "<< amount << std::endl;

	/// Draw polygonal contour + bonding rects + circles
	Mat drawing = Mat::zeros( threshold_output.size(), CV_8UC3 );
	for( int i = 0; i< contours.size(); i++ )
	{
		Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
		drawContours( drawing, contours_poly, i, color, 1, 8, vector<Vec4i>(), 0, Point() );
		//std::cout << boundRect[i].width() << std::endl;
		//boundRect[i].tl()
		rectangle( drawing, boundRect[i].tl(), boundRect[i].br(), color, 2, 8, 0 );
		//circle( drawing, center[i], (int)radius[i], color, 2, 8, 0 );
	}

	/// Show in a window
	//namedWindow( "Contours", CV_WINDOW_NORMAL );
	//imshow( "Contours", drawing );
	//imwrite(strEndPath, drawing);
	drawing.release();
	threshold_output.release();
}
