#include<highgui.h>
#include<cv.h>
#include<stdio.h>
#include<string.h>
#include<fstream>

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


		const char* imagename = words.at(i).c_str();

		sprintf(strStartPath, "timelapse_201402201220/%s", imagename);

		IplImage* img=cvLoadImage(strStartPath);

		std::string str = imagename;
		size_t pos = str.find(".jpg");
		str.replace(pos,4,".png");
		std::cout << "str: " << str << std::endl;
		imagename = str.c_str();

		sprintf(strEndPath, "MasksStart/%s", imagename);

		cvSaveImage(strEndPath,img);
		cvReleaseImage(&img);


	}
}
