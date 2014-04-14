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
int seed_true_positive = 0;
int seed_true_negative = 0;
int shoot_false_positive = 0;
int shoot_false_negative = 0;
int shoot_true_negative = 0;
int shoot_true_positive = 0;
int rows = 0;
int cols = 0;

/** @function main */
int main( int argc, char** argv )
{

	ground_truth = imread(argv[1], CV_LOAD_IMAGE_COLOR);
	program_output = imread(argv[2], CV_LOAD_IMAGE_COLOR);
	mask = imread(argv[3], CV_LOAD_IMAGE_COLOR);

	namedWindow( "Ground Truth", CV_WINDOW_NORMAL);
	imshow( "Ground Truth", ground_truth);
	namedWindow( "Program Output", CV_WINDOW_NORMAL);
	imshow( "Program Output", program_output);
	namedWindow( "Mask", CV_WINDOW_NORMAL);
	imshow( "Mask", mask);

	//Mat image( ground_truth.rows, ground_truth.cols, CV_8UC3);
	Mat image= program_output.clone();
	image.setTo(Scalar(0,0,0));

	Mat dst;
	cvtColor(image, image, CV_BGR2GRAY);
	cvtColor(ground_truth, ground_truth, CV_BGR2GRAY);
	cvtColor(program_output, program_output, CV_BGR2GRAY);
	cvtColor(mask, mask, CV_BGR2GRAY);
	
	namedWindow( "New Image", CV_WINDOW_NORMAL);

	waitKey(0);

	for(int i=0;i<program_output.rows;i++){

		for (int j=0;j<program_output.cols;j++){

			//imshow( "New Image", dst);
			//waitKey(0);
			
			//dst.at<uchar>(i,j) = 255;

			if(mask.at<uchar>(i,j) == 255){

	    			if( (ground_truth.at<uchar>(i,j) == 255) && (program_output.at<uchar>(i,j) == 255)){  
					image.at<uchar>(i,j) = 255;
					seed_true_positive++;
				}

				if( (ground_truth.at<uchar>(i,j) == 255) && (program_output.at<uchar>(i,j) == 0)){  
					image.at<uchar>(i,j) = 100;
					seed_false_negative++;
				}

				if( (ground_truth.at<uchar>(i,j) == 0) && (program_output.at<uchar>(i,j) == 255)){  
					image.at<uchar>(i,j) = 50;
					seed_false_positive++;
				}

				if( (ground_truth.at<uchar>(i,j) == 0) && (program_output.at<uchar>(i,j) == 0)){  
					image.at<uchar>(i,j) = 0;
					seed_true_negative++;
				}

				if( (ground_truth.at<uchar>(i,j) == 200) && (program_output.at<uchar>(i,j) == 255)){  
					image.at<uchar>(i,j) = 255;
					shoot_true_positive++;
				}


				/*if( (program_output.at<uchar>(i,j) != 255) && (program_output.at<uchar>(i,j) !=0) ){
					//std::cout << "not white or black " << ground_truth.at<uchar>(i,j) << std::endl;
					    uchar val;
    						val = program_output.at<uchar>(i,j);

    						cout << (int)val << endl;


				}*/


			}
			cols++;
			
				
 		}
		rows++;
	}

	
	std::cout << "Seed True Positive: " << seed_true_positive << std::endl;
	std::cout << "Seed True Negative: " << seed_true_negative << std::endl;
	std::cout << "False Negative Seed Pixels: " << seed_false_negative << std::endl;
	std::cout << "False Positive Seed Pixels: " << seed_false_positive << std::endl;

	std::cout << "Shoot True Positive: " << shoot_true_positive << std::endl;

	imshow( "New Image", image);

	waitKey(0);
	return(0);
	

}
