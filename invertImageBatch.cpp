#include <opencv2/opencv.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <string>
#include <iostream>
#include <fstream>

using namespace cv;
using namespace std;

int main( int argc, char** argv )
{

char strStartPath[50];
char strEndPath[50];

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
	  sprintf(strStartPath, "OtsuEnd/%s", imagename);
	  sprintf(strEndPath, "InvertedEnd/%s", imagename);
	  std::cout<<"Start Path: "<< strStartPath << std::endl;
	  std::cout<<"End Path: "<< strEndPath << std::endl;



	Mat dst,src;

	src = imread(strStartPath,1); //input image
	//imshow("original Image",src);

	bitwise_not ( src, dst );

	//imshow("Image Changed",dst);
	imwrite(strEndPath, dst);

	dst.release();
	src.release();
}
//waitKey();
}
