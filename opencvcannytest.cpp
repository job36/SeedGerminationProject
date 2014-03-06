#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>

using namespace cv;

/// Global variables

Mat src, src_gray;
Mat dst, detected_edges;

int edgeThresh = 1;
int lowThreshold = 38;
int const max_lowThreshold = 100;
int ratio = 3;
int kernel_size = 3;
char* window_name = "Edge Map";
char strStartPath[100];
char strEndPath[100];


/**
* @function CannyThreshold
* @brief Trackbar callback - Canny thresholds input with a ratio 1:3
*/
void CannyThreshold(int, void*)
{
  /// Reduce noise with a kernel 3x3
  blur( src_gray, detected_edges, Size(3,3) );

  /// Canny detector
  Canny( detected_edges, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size );

  /// Using Canny's output as a mask, we display our result
  dst = Scalar::all(0);

  //Mat dst;
  src.copyTo( dst, detected_edges);
  imshow( window_name, dst );
 }


/** @function main */
int main( int argc, char** argv )
{
  
  char* folder_name = "CannyFolderStart";


  std::vector <std::string> words; // Vector to hold our words read
  std::string str; // Temp string to
  std::cout << "Read from a file!" << std::endl;
  std::ifstream fin("pics.txt"); // Open it up!


  while (fin >> str){ 
    words.push_back(str);
  }
  fin.close(); 

  for (int i = 0; i < words.size(); ++i){
    std::cout << words.at(i) << std::endl;
    std::cout<<"In the for loop"<< std::endl;

    const char* picname = words.at(i).c_str();
    //strcat(picname, words.at(i));

    sprintf(strStartPath, "%s/%s", folder_name, picname);
    std::cout<<"Start Path: "<<strStartPath<<std::endl;
    src = imread(strStartPath);

    if( !src.data )
    { return -1; }

    /// Create a matrix of the same type and size as src (for dst)
    dst.create( src.size(), src.type() );
    /// Convert the image to grayscale
    cvtColor( src, src_gray, CV_BGR2GRAY );
    /// Show the image
    CannyThreshold(0, 0);

    sprintf(strEndPath, "CannyFolderEnd/%s", picname);
    std::cout<<"End Path: "<<strEndPath<<std::endl;
    //strcpy (strEndPath, "../testFolderEnd/doge");
    //strcat (strEndPath, sprintf(str, "%d", n));
    //strcat (strEndPath, ".jpg");

    imwrite(strEndPath, detected_edges);

  }


  return 0;
  }
