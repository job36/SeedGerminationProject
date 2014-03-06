#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <fstream>

using namespace cv;
char strStartPath[100];

/** @function main */
int main(int argc, char** argv)
{
  Mat src, src_gray;
  std::vector<Mat> Masks;
  char mask_name[50];
  char path[50];

  std::vector <std::string> words; // Vector to hold our words read
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
	  //sprintf(strEndPath, "MasksEnd/%s", imagename);
	  std::cout<<"Start Path: "<< strStartPath << std::endl;
	  //std::cout<<"End Path: "<< strEndPath << std::endl;

	  /// Read the image
	  src = imread( strStartPath, 1 );

	  if( !src.data )
	    { return -1; }

	  /// Convert it to gray
	  cvtColor( src, src_gray, CV_BGR2GRAY );

	  /// Reduce the noise so we avoid false circle detection
	  GaussianBlur( src_gray, src_gray, Size(9, 9), 2, 2 );

	  vector<Vec3f> circles;

	  /// Apply the Hough Transform to find the circles
	  HoughCircles( src_gray, circles, CV_HOUGH_GRADIENT, 1, src_gray.rows/8, 70, 50, 0, 0 );

	  std::cout<<"Creating Masks: "<<std::endl;
	  for(int i = 0; i < circles.size(); i++){
		//creating a new image
		 Mat image(src.rows,src.cols, CV_8UC3);

	 	//set background to black
	 	 image.setTo(Scalar(0,0,0));
	
	  	//add to vector
	 	 Masks.push_back(image);

	  }

	  std::cout<<"Drawing circles: "<<std::endl;
	  /// Draw the circles detected
	  for( size_t i = 0; i < circles.size(); i++ )
	  {

	      Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
	      int radius = cvRound(circles[i][2]);
	      // circle center
	      circle( Masks.at(i), center, 3, Scalar(255,255,255), -1, 8, 0 );
	      // circle outline
	      circle( Masks.at(i), center, radius, Scalar(255,255,255), -3, 8, 0 );
	   }


	 for( int i = 0; i < circles.size(); i++ )
	  {

	   Mat imageDest = cvCreateMat(src.rows, src.cols, CV_8UC3);
	   src.copyTo(imageDest, Masks.at(i));
	   //sprintf(mask_name, "imagename", i);
	   sprintf(path, "Masks%d/%s", i, imagename);
	   namedWindow(mask_name, CV_WINDOW_NORMAL);
	   imshow(mask_name, Masks.at(i));
	   imwrite(path, imageDest);

	  }

  }
  
  std::cout<<"Ends: "<<std::endl;
  return 0;
}

