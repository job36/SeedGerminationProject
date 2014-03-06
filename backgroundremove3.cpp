#include<highgui.h>
#include<cv.h>
#include<stdio.h>
#include<fstream>
#define h 280
#define w 320
char strStartPath[100];
char strEndPath[100];

int main(int argc, char** argv)
{

  std::vector <std::string> words; // Vector to hold our words read
  std::string str; // Temp string to
  std::cout << "Read from a file!" << std::endl;
  std::ifstream fin("pics.txt"); // Open it up!


  while (fin >> str){ 
    words.push_back(str);
  }
  fin.close();

  for (int i = 0; i < words.size(); ++i){
	std::cout<<"In the for loop"<< std::endl;

	const char* imagename = words.at(i).c_str();
	std::cout<<"Image Name: "<< imagename << std::endl;
	sprintf(strStartPath, "RemoveBackgroundStart/%s", imagename);
	sprintf(strEndPath, "RemoveBackgroundEnd/%s", imagename);
	std::cout<<"Start Path: "<< strStartPath << std::endl;
	std::cout<<"End Path: "<< strEndPath << std::endl;


	//Image variables
	//char* imageName = argv[1];
	IplImage* img=cvLoadImage(strStartPath);
	IplImage* rimg=cvCreateImage(cvSize(w,h),8,3);
	IplImage* hsvimg=cvCreateImage(cvSize(w,h),8,3);
	IplImage* thresh=cvCreateImage(cvSize(w,h),8,1);
	
	std::cout<<"Loaded Images "<< std::endl;
	 
	//Variables
	int h1=0;int s1=0;int v1=6;
	int h2=100;int s2=255;int v2=255;

	//Resizing the image
	cvResize(img,rimg,CV_INTER_LINEAR);
	//Changing into HSV plane
	cvCvtColor(rimg,hsvimg,CV_BGR2HSV);

	std::cout<<"Resize Images and HSV "<< std::endl;

	//Thresholding the image
	cvInRangeS(hsvimg,cvScalar(h1,s1,v1),cvScalar(h2,s2,v2),thresh);

	cvSaveImage(strEndPath,thresh);

	std::cout<<"Save Image "<< std::endl;

	//Cleanup
	cvReleaseImage(&img);
	cvReleaseImage(&thresh);
	cvReleaseImage(&rimg);
	cvReleaseImage(&hsvimg);
	cvDestroyAllWindows();

  }

  return 0;
 
}
