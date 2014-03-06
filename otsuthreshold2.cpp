//----------------------------------------------------------
// binarisation otsu
//----------------------------------------------------------
#include "iostream"
#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "time.h"
#include "cxcore.h"
#include "cv.h"
#include "highgui.h"
#include <fstream>
 
int GRAYLEVEL = 256;
char strStartPath[100];
char strEndPath[100];
#define MAX_BRIGHTNESS 255
//const double INFO_THRESHOLD = 0.2;
 
using namespace std;
 
//----------------------------------------------------------
// binarization by Otsu's method
// based on maximization of inter-class variance
//----------------------------------------------------------
void binarize_otsu(IplImage* image, IplImage* imgBin )
{
int hist[GRAYLEVEL];
double prob[GRAYLEVEL],
omega[GRAYLEVEL]; // prob of graylevels
double myu[GRAYLEVEL]; // mean value for separation
double max_sigma,
sigma[GRAYLEVEL]; // inter-class variance
 
int i, x, y; /* Loop variable */
int threshold; /* threshold for binarization */
 
// Histogram generation
memset((int*) hist , 0, GRAYLEVEL * sizeof(int) );
 
CvSize size = cvGetSize(image);
 
for (int i = 0; i < size.height; ++i)
{
unsigned char* pData = (unsigned char*) (image->imageData + i *
image->widthStep);
for (int j = 0; j < size.width; ++j)
{
int k = (int)((unsigned char) *(pData+j));
hist[k]++;
}
}
 
int taille = size.width * size.height;
 
// calculation of probability density
for ( i = 0; i < GRAYLEVEL; ++i )
{
prob[i] = (double) ((double)hist[i] / (double)taille);
}
 
/*
int LEVEL = GRAYLEVEL;
double sumProb = 0.0;
for ( i = 0; i < GRAYLEVEL; ++i )
{
sumProb += prob[i];
if ( sumProb > INFO_THRESHOLD)
{
LEVEL = i;
break;
}
}
GRAYLEVEL = LEVEL;
*/
 
// omega & myu generation
omega[0] = prob[0];
myu[0] = 0.0;
for (i = 1; i < GRAYLEVEL; i++)
{
omega[i] = omega[i-1] + prob[i];
myu[i] = myu[i-1] + (i*prob[i]);
}
 
//----------------------------------------------------------
// sigma maximization
// sigma stands for inter-class variance
// and determines optimal threshold value
//----------------------------------------------------------
threshold = 0;
max_sigma = 0.0;
for (i = 0; i < GRAYLEVEL-1; i++)
{
if (omega[i] != 0.0 && omega[i] != 1.0)
{
//sigma[i] = (omega[i]*(1.0 - omega[i])) * ((myu[GRAYLEVEL-1] - 2*myu[i]) *
(myu[GRAYLEVEL-1] - 2*myu[i]);
sigma[i] = ((myu[GRAYLEVEL-1]*omega[i] - myu[i]) *
(myu[GRAYLEVEL-1]*omega[i] - myu[i])) / (omega[i]*(1.0 - omega[i]));
}
else
{
sigma[i] = 0.0;
}
if (sigma[i] > max_sigma)
{
max_sigma = sigma[i];
threshold = i;
}
}
 
printf("threshold = %dn", threshold);
 
// binarization output into imgBin
for (y = 0; y < size.height; ++y)
{
unsigned char* pData = (unsigned char*) (image->imageData + (y *
image->widthStep));
unsigned char* pDataBin = (unsigned char*) (imgBin->imageData + (y *
imgBin->widthStep));
for (x = 0; x < size.width; ++x)
{
if ( *(pData+x) > threshold)
	{
*(pDataBin+x) = MAX_BRIGHTNESS;
}
else
{
*(pDataBin+x) = 0;
}
}
}
 
}
 
int main(int argc, char* argv[] )
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

	IplImage* image = 0;
	IplImage* imgBin = 0;
	clock_t start = clock();

	const char* imagename = words.at(i).c_str();
	std::cout<<"Image Name: "<< imagename << std::endl;
	sprintf(strStartPath, "Masks0/%s", imagename);
	sprintf(strEndPath, "OtsuEnd/%s", imagename);
	std::cout<<"Start Path: "<< strStartPath << std::endl;
	std::cout<<"End Path: "<< strEndPath << std::endl;

	image = cvLoadImage(strStartPath, CV_LOAD_IMAGE_GRAYSCALE);
	std::cout<<"Load Image "<< std::endl;
 
	//if ( image != NULL )
	//{
	imgBin = cvCloneImage(image);
	binarize_otsu(image,imgBin);
	cvSaveImage(strEndPath, imgBin);
	cvReleaseImage(&image);
	cvReleaseImage(&imgBin);
	clock_t end = clock();
	double delay = double((double)(end - start)/CLOCKS_PER_SEC);
	printf("processing time : %lf secondsn",delay);
	std::cout<<"Otsu Image "<< std::endl;

  }
}
