#include<highgui.h>
#include<cv.h>
#include<stdio.h>
#define h 280
#define w 320
int main()
{
//Image variables
IplImage* img=cvLoadImage("seedStuff/FirstSeedDataSet/1.jpg");
IplImage* rimg=cvCreateImage(cvSize(w,h),8,3);
//Image variables for R,G,B components
IplImage* r=cvCreateImage(cvSize(w,h),8,1);
IplImage* g=cvCreateImage(cvSize(w,h),8,1);
IplImage* b=cvCreateImage(cvSize(w,h),8,1);
//Image variables for thresholds
IplImage* rt=cvCreateImage(cvSize(w,h),8,1);
IplImage* gt=cvCreateImage(cvSize(w,h),8,1);
IplImage* bt=cvCreateImage(cvSize(w,h),8,1);
IplImage* temp=cvCreateImage(cvSize(w,h),8,1);
IplImage* final=cvCreateImage(cvSize(w,h),8,1);
//Windows
cvNamedWindow("Image",CV_WINDOW_AUTOSIZE);
cvNamedWindow("Red",CV_WINDOW_AUTOSIZE);
cvNamedWindow("Green",CV_WINDOW_AUTOSIZE);
cvNamedWindow("Blue",CV_WINDOW_AUTOSIZE);
cvNamedWindow("Final",CV_WINDOW_AUTOSIZE);
//Variables for trackbar
int rv=0;int gv=0;int bv=0;
//Creating the trackbars
cvCreateTrackbar("R","Red",&rv,255,0);
cvCreateTrackbar("G","Green",&gv,255,0);
cvCreateTrackbar("B","Blue",&bv,255,0);
 
//Resizing the image
cvResize(img,rimg,CV_INTER_LINEAR);
//Splitting the image into R,G,B components
cvSplit(rimg,r,g,b,NULL);
 
while(1)
{
 
//Thresholding the R frame
cvThreshold(r,rt,rv,255,CV_THRESH_BINARY_INV);
//Thresholding the G frame
cvThreshold(g,gt,gv,255,CV_THRESH_BINARY_INV);
//Thresholding the B frame
cvThreshold(b,bt,bv,255,CV_THRESH_BINARY_INV);
//Perforimg AND operation
cvAnd(rt,gt,temp);
cvAnd(temp,bt,final);
//Showing the images
cvShowImage("Image",rimg);
cvShowImage("Red",rt);
cvShowImage("Green",gt);
cvShowImage("Blue",bt);
cvShowImage("Final",final);
//Escape Sequence
char c=cvWaitKey(33);
if(c==27)
break;
}
//Showing the image
cvShowImage("Image",rimg);
//Waiting for user to press any key
cvWaitKey(0);
//Cleanup
cvReleaseImage(&img);
cvReleaseImage(&rimg);
cvReleaseImage(&r);
cvReleaseImage(&g);
cvReleaseImage(&b);
cvReleaseImage(&rt);
cvReleaseImage(&gt);
cvReleaseImage(&bt);
cvReleaseImage(&final);
cvDestroyAllWindows();

}
