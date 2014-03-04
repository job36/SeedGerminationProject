#include<highgui.h>
#include<cv.h>
#include<stdio.h>
#define h 280
#define w 320
int main(int argc, char** argv)
{
//Image variables
char* imageName = argv[1];
IplImage* img=cvLoadImage(imageName);
IplImage* rimg=cvCreateImage(cvSize(w,h),8,3);
IplImage* hsvimg=cvCreateImage(cvSize(w,h),8,3);
IplImage* thresh=cvCreateImage(cvSize(w,h),8,1);
//Windows
cvNamedWindow("Original Image",CV_WINDOW_AUTOSIZE);
cvNamedWindow("Thresholded Image",CV_WINDOW_AUTOSIZE);
cvNamedWindow("cnt",CV_WINDOW_AUTOSIZE);
 
//Variables for trackbar
int h1=0;int s1=0;int v1=6;
int h2=100;int s2=255;int v2=255;
//Creating the trackbars
cvCreateTrackbar("H1","cnt",&h1,255,0);
cvCreateTrackbar("H2","cnt",&h2,255,0);
cvCreateTrackbar("S1","cnt",&s1,255,0);
cvCreateTrackbar("S2","cnt",&s2,255,0);
cvCreateTrackbar("V1","cnt",&v1,255,0);
cvCreateTrackbar("V2","cnt",&v2,255,0);
 
//Resizing the image
cvResize(img,rimg,CV_INTER_LINEAR);
//Changing into HSV plane
cvCvtColor(rimg,hsvimg,CV_BGR2HSV);
while(1)
{
//Thresholding the image
cvInRangeS(hsvimg,cvScalar(h1,s1,v1),cvScalar(h2,s2,v2),thresh);
//Showing the images
cvShowImage("Original Image",rimg);
cvShowImage("Thresholded Image",thresh);
//Escape Sequence
char c=cvWaitKey(33);
if(c==27)
break;
}
//Showing the image
cvShowImage("Original Image",rimg);
cvShowImage("Thresholded Image",thresh);
//Waiting for user to press any key
cvWaitKey(0);
cvSaveImage("backSub.png",thresh);


//Cleanup
cvReleaseImage(&img);
cvReleaseImage(&thresh);
cvReleaseImage(&rimg);
cvReleaseImage(&hsvimg);
cvDestroyAllWindows();
 
}
