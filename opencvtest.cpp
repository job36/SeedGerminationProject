#include<opencv2/highgui/highgui.hpp>
using namespace cv;

int main()
{

    Mat img = imread("/home/birdy/Documents/OpenCV/opencv-2.4.8/samples/cpp/board.jpg",CV_LOAD_IMAGE_COLOR);
    imshow("opencvtest",img);
    waitKey(0);

    return 0;
}
