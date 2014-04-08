#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>

using namespace cv;
using namespace std;

Mat src; Mat src_gray;
int thresh = 10;
int max_thresh = 255;
RNG rng(12345);
int amount = 0;
int germinated = 0;

/// Function header
void thresh_callback(int, void* );

/** @function main */
int main( int argc, char** argv )
{
	/// Load source image and convert it to gray
	src = imread( argv[1], 1 );

	/// Convert image to gray and blur it
	cvtColor( src, src_gray, CV_BGR2GRAY );
	blur( src_gray, src_gray, Size(3,3) );

	/// Create Window
	char* source_window = "Source";
	namedWindow( source_window, CV_WINDOW_NORMAL );
	imshow( source_window, src );

	createTrackbar( " Threshold:", "Source", &thresh, max_thresh, thresh_callback );
	thresh_callback( 0, 0 );

	waitKey(0);
	return(0);
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

	std::cout << "contours.size(): "<< contours.size() << std::endl;
	for( int i = 0; i < contours.size(); i++ ) { 

		if((contours[i].size() < 400) && (contours[i].size() > 55)){
			approxPolyDP( Mat(contours[i]), contours_poly[i], 3, true );
			boundRect[i] = boundingRect( Mat(contours_poly[i]) );
			std::cout << "width?: "<< boundRect[i].width << std::endl;
			std::cout << "height?: "<< boundRect[i].height << std::endl;
			std::cout << "width divide height: "<< boundRect[i].width/boundRect[i].height<< std::endl;
			std::cout << "height divide width: "<< boundRect[i].height/boundRect[i].width<< std::endl;
			std::cout << "width difference height: "<< boundRect[i].width - boundRect[i].height<< std::endl;
			std::cout << "height difference width: "<< boundRect[i].height - boundRect[i].width<< std::endl;


if( (boundRect[i].width - boundRect[i].height < 10) && (boundRect[i].width - boundRect[i].height > -10) ){

	if( (boundRect[i].height - boundRect[i].width < 10) && (boundRect[i].height - boundRect[i].width > -10) ){

		germinated++;
	}

}




			std::cout << contours[i].size() << std::endl;
			minEnclosingCircle( (Mat)contours_poly[i], center[i], radius[i] );
			amount++;
		}

	}
	std::cout << "Amount: "<< amount << std::endl;
	std::cout << "germinated: "<< germinated << std::endl;

	ofstream myfile;
	myfile.open ("example.txt");
	myfile << "Writing this to a file.\n";
	myfile.close();

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
	namedWindow( "Contours", CV_WINDOW_NORMAL );
	imshow( "Contours", drawing );
	imwrite( "connected.png", drawing);
	amount = 0;
	germinated = 0;
}
