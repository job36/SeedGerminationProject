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
int contNumb = 0;
int changedCont = 0;
int germinated = 0;
int minimum =0;
int number=0;
char strStartPath[50];
char strEndPath[50];
char strExample[50];

/// Function header
void thresh_callback(int, void* );

/** @function main */
int main( int argc, char** argv )
{

	minimum = atoi(argv[1]);

	std::vector <std::string> words; // Vector to hold our words read
	std::string str; // Temp string to
	std::cout << "Read from a file!" << std::endl;
	std::ifstream fin("masks.txt"); // Open it up!

	while (fin >> str){ 
		words.push_back(str);
	}
	sprintf(strExample, "DefectsExamples/example%d.txt", minimum);

	ofstream myfile;
	myfile.open (strExample);

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

		thresh_callback( 0, 0 );
	number++;
	
	myfile <<number << " " << germinated << "\n";
		germinated = 0;
		contNumb = 0;
		changedCont = 0;
	}


	myfile.close();

	//waitKey(0);
	//return(0);
}

/** @function thresh_callback */
void thresh_callback(int, void* )
{
	Mat src_copy = src.clone();
	Mat threshold_output;
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;

	/// Detect edges using Threshold
	threshold( src_gray, threshold_output, thresh, 255, THRESH_BINARY );

	/// Find contours
	findContours( threshold_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

	/// Find the convex hull object for each contour
	vector<vector<Point> >hull( contours.size() );
	vector<vector<int> >hull2( contours.size() );
	for( int i = 0; i < contours.size(); i++ ){
		convexHull( Mat(contours[i]), hull[i], false );
		convexHull( Mat(contours[i]), hull2[i], false );

	}

	vector<vector<Vec4i> > defects(contours.size());
	//convexityDefects(contours, hull, defects);
	for(int i = 0; i < contours.size(); i++){

		if(hull2[i].size() >=4){

			convexityDefects(contours[i], hull2[i], defects[i]);
		
		}
		//std::cout << "Defects: "<< defects[i].depth << std::endl;
	}

	/// Draw contours + hull results
	Mat drawing = Mat::zeros( threshold_output.size(), CV_8UC3 );
	for( int i = 0; i < contours.size(); i++ )
	{
		if(contours[i].size() < 500){
			//if( (contours[i].size() - hull[i].size()) > 60 ){
				std::cout << "Countour Size: "<< contours[i].size() << std::endl;
				std::cout << "Hull Size: "<< hull[i].size() << std::endl;
				std::cout << "Hull - Contour Size: "<< contours[i].size() - hull[i].size() << std::endl;
				//if( (contours[i].size() - hull[i].size()) > 55 ){
				Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
				drawContours( drawing, hull, i, color, -1, 8, vector<Vec4i>(), 0, Point() );
				drawContours( drawing, contours, i, 0, -1, 8, vector<Vec4i>(), 0, Point() );
			//}
		}
	}

		/// Show in a window
		//namedWindow( "Hull demo", CV_WINDOW_NORMAL );
		//imshow( "Hull demo", drawing );
		//waitKey(0);

		//Mat drawing = Mat::zeros( threshold_output.size(), CV_8UC3 );
		/// Draw convexityDefects
		
		for( int i = 0; i< contours.size(); i++ )
		{
			contNumb = i;

			//if((contours[i].size() < 500) && (contours[i].size() > 35)){
			//if( (contours[i].size() - hull[i].size()) > 60 ){
			//size_t count = contours[i].size();
			//if( count <300 )
			//continue;
			std::cout << "Contour" << std::endl;
			vector<Vec4i>::iterator d=defects[i].begin();
			while( d!=defects[i].end() ) {
				Vec4i& v=(*d);
				int startidx=v[0]; Point ptStart( contours[i][startidx] );
				int endidx=v[1]; Point ptEnd( contours[i][endidx] );
				int faridx=v[2]; Point ptFar( contours[i][faridx] );
				float depth = v[3] / 256;

				std::cout << "Defect Depth: "<< int(depth) << std::endl;
				if((int(depth) > minimum) && (int(depth) < 102)){

					if(changedCont != contNumb){
						changedCont = contNumb;
						germinated++;
					}
					
					line( drawing, ptStart, ptEnd, Scalar(0,255,0), 1 );
					line( drawing, ptStart, ptFar, Scalar(0,255,0), 1 );
					line( drawing, ptEnd, ptFar, Scalar(0,255,0), 1 );
					circle( drawing, ptFar,   4, Scalar(0,255,0), 2 );

				}
					d++;
				
			}
		}
		std::cout << "ContNumb: " << contNumb << std::endl;
		std::cout << "ChangedCont: " << changedCont << std::endl;
		std::cout << "Germinated Guess: " << germinated << std::endl;
		//imshow( "Hull demo", drawing );
		imwrite(strEndPath, drawing);
		drawing.release();
		threshold_output.release();
		//}
		//}

	}
