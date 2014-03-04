#include<stdio.h>
#include<highgui.h>
#include<cv.h>
#include<math.h>
#include<stdlib.h>
 
int main(int argc, char **argv)
 
{
 const char* imagename =argv[1];
 IplImage* img = 0;
 int h, w, step, channels, i, j, k;
 uchar *data, *trans;
 img = cvLoadImage(imagename, CV_LOAD_IMAGE_UNCHANGED);
 if(!img)
 printf("Could not load image file: %s\n", imagename);
 h = img->height;
 w = img->width;
 step = img->widthStep;
 channels = img->nChannels;
 data = (uchar *)img->imageData;
 
 IplImage* RGB = cvCreateImage(cvGetSize(img), 8, 1);
 trans = (uchar *)RGB->imageData;
 int trans_step;
 trans_step = RGB->widthStep;
 
//extracting necessary components
 int col = 2;
 for(i=0; i<h; i++)
 for(j=0; j<w; j++)
 trans[i*trans_step+j] = data[i*step+j*channels+col];
 
 cvNamedWindow("OpenCV", CV_WINDOW_AUTOSIZE);
 cvShowImage("OpenCV", RGB);
 cvWaitKey(0);
 cvReleaseImage(&img);
 cvReleaseImage(&RGB);
 
 return 0;
}
