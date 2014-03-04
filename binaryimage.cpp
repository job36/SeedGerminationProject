Mat im_gray = imread("backSub.jpg",CV_LOAD_IMAGE_GRAYSCALE); // You can directly read a RGB image as grayscale 
Mat img_bw = im_gray > 128;
