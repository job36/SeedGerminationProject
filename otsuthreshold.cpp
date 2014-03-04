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
 
int GRAYLEVEL = 256;
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
(myu[GRAYLEVEL-1] - 2*myu[i]));
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
IplImage* image = 0;
IplImage* imgBin = 0;
clock_t start = clock();
(argc == 3) ? image = cvLoadImage(argv[1], CV_LOAD_IMAGE_GRAYSCALE) :
cout < < "Usage :n" << argv[0] << " [srcImagePath] [dstimagepath]" < < endl;
 
if ( image != NULL )
{
imgBin = cvCloneImage(image);
binarize_otsu(image,imgBin );
cvSaveImage(argv[2], imgBin);
cvReleaseImage(&image);
cvReleaseImage(&imgBin);
clock_t end = clock();
double delay = double((double)(end - start) / CLOCKS_PER_SEC);
printf("processing time : %lf secondsn",delay);
return EXIT_SUCCESS;
}

return EXIT_FAILURE;
}
