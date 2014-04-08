#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace cv;
using namespace std;
Mat ground_truth, program_output, mask;
int seed_false_positive = 0;
int seed_false_negative = 0;
int true_seed_pixel = 0;
int rows = 0;
int cols = 0;

/** @function main */
int main( int argc, char** argv )
{

	ground_truth = imread(argv[1], 1);
	program_output = imread(argv[2], 1);
	mask = imread(argv[3], 1);

	std::cout << "Ground Truth Rows start:  " << ground_truth.rows << std::endl;	
	std::cout << "Ground Truth Cols start:  " << ground_truth.cols << std::endl;

	namedWindow( "Ground Truth", CV_WINDOW_NORMAL);
	imshow( "Ground Truth", ground_truth);
	namedWindow( "Program Output", CV_WINDOW_NORMAL);
	imshow( "Program Output", program_output);
	namedWindow( "Mask", CV_WINDOW_NORMAL);
	imshow( "Mask", mask);

	Mat image( ground_truth.rows + 10, ground_truth.cols, ground_truth.type());
	namedWindow( "New Image", CV_WINDOW_NORMAL);

	waitKey(0);

	std::cout << "Ground Truth Rows:  " << ground_truth.rows << std::endl;	
	std::cout << "Ground Truth Cols:  " << ground_truth.cols << std::endl;

	std::cout << "image Rows:  " << image.rows << std::endl;	
	std::cout << "image Truth Cols:  " << image.cols << std::endl;	

	for(int j=0;j<ground_truth.rows;j++){
		for (int i=0;i<ground_truth.cols;i++){
			
			//image.at<uchar>(j,i) = 255;

			if(mask.at<uchar>(j,i) == 255){
	    			if( ground_truth.at<uchar>(j,i) == 255 && program_output.at<uchar>(j,i) == 255){  
					image.at<uchar>(j,i) = 255;
					true_seed_pixel++;
				}

				if( ground_truth.at<uchar>(j,i) == 255 && program_output.at<uchar>(j,i) == 0){  
					image.at<uchar>(j,i) = 100;
					seed_false_negative++;
				}

				if( ground_truth.at<uchar>(j,i) == 0 && program_output.at<uchar>(j,i) == 255){  
					image.at<uchar>(j,i) = 50;
					seed_false_positive++;
				}
			}
			cols++;
			
				
 		}
		rows++;
	}

	std::cout << "Rows:  " << rows << std::endl;	
	std::cout << "Cols:  " << cols << std::endl;	
	
	std::cout << "True Seed Pixels: " << true_seed_pixel << std::endl;
	std::cout << "False Negative Seed Pixels: " << seed_false_negative << std::endl;
	std::cout << "False Positive Seed Pixels: " << seed_false_positive << std::endl;

	imshow( "New Image", image);

	waitKey(0);
	return(0);
	

}
