#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <fstream>

using namespace cv;
using namespace std;

/**  @function main */
int main( int argc, char** argv )
{

	char strStartPath[50];
	char strEndPath[50];

	  std::vector <std::string> words; // Vector of words
	  std::string str; // Temp string to
	  std::cout << "Read from a file!" << std::endl;
	  std::ifstream fin("masks.txt"); // Open it up!

	  while (fin >> str){ 
	    words.push_back(str);
	  }
	  fin.close();

	for (int i = 0; i < words.size(); ++i){

		  const char* imagename = words.at(i).c_str();
		  std::cout<<"Image Name: "<< imagename << std::endl;
		  sprintf(strStartPath, "MasksStart/%s", imagename);
		  sprintf(strEndPath, "HistoEnd/%s", imagename);
		  std::cout<<"Start Path: "<< strStartPath << std::endl;
		  std::cout<<"End Path: "<< strEndPath << std::endl;


		  Mat src, dst, ycrcb;

		  char* source_window = "Source image";
		  char* equalized_window = "Equalized Image";

		  /// Load image
		  src = imread( strStartPath, 1 );

		  if( !src.data )
		    { cout<<"Usage: ./Histogram_Demo <path_to_image>"<<endl;
		      return -1;}

		  /// Convert to grayscale   YCrCb
		  cvtColor( src, ycrcb, CV_BGR2HSV );

		  vector<Mat> channels;
		  split(ycrcb,channels);

		  /// Apply Histogram Equalization
		  equalizeHist( channels[0], channels[0] );
		  //equalizeHist( channels[1], channels[1] );
		  //equalizeHist( channels[2], channels[2] );

		  Mat result;
		  merge(channels,ycrcb);

		  cvtColor( ycrcb, result, CV_HSV2BGR );

		  /// Display results
		  namedWindow( source_window, CV_WINDOW_NORMAL );
		  namedWindow( equalized_window, CV_WINDOW_NORMAL );

		  imshow( source_window, src );
		  imshow( equalized_window, result );
		  imwrite( strEndPath, result );
		  src.release();
		  ycrcb.release();
		  dst.release();

		  /// Wait until user exits the program
		  //waitKey(0);
	}
	  return 0;
}

