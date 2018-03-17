// CPP program to Stitch
// input images (panorama) using OpenCV 
#include <iostream>
#include <fstream>

// Include header files from OpenCV directory
// required to stitch images.
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/stitching.hpp"

using namespace std;
using namespace cv;

// Define mode for stitching as panoroma 
// (One out of many functions of Stitcher)
Stitcher::Mode mode = Stitcher::PANORAMA;

// Array for pictures
vector<Mat> imgs;

int main(int argc, char* argv[])
{

	// Get all the images that need to be 
	// stitched as arguments from command line 
	for (int i = 1; i < argc; ++i)
	{
		// Read the ith argument or image 
		// and push into the image array
		Mat img = imread(argv[i]);
		if (img.empty())
		{
			// Exit if image is not present
			cout << "Can't read image '" << argv[i] << "'\n";
			return -1;
		}
		imgs.push_back(img);
	}

	// Define object to store the stitched image
	Mat pano;
	Mat sobelx, sobelx2;
	Mat inverted, inverted2;
	Mat grey, grey2;
	Mat inversion, inversion2;
	Mat image, image2;
	//Sobelx Filter
	Sobel(imgs[0], sobelx, CV_64F, 1, 0, 5);
	imwrite("sobelx.jpg", sobelx);
	Sobel(imgs[1], sobelx2, CV_64F, 1, 0, 5);
	imwrite("sobelx2.jpg", sobelx2);

	image = imread("sobelx.jpg", 1);
	bitwise_not(image, inverted);
	imwrite("inverted.jpg", inverted);
	image = imread("sobelx2.jpg", 1);
	bitwise_not(image, inverted2);
	imwrite("inverted2.jpg", inverted2);



	medianBlur(imread("inverted.jpg", 0), image, 5);
	imwrite("medianblur.jpg", image);
	medianBlur(imread("inverted2.jpg", 0), image, 5);
	imwrite("medianblur2.jpg", image);

	image = imread("medianblur.jpg", 1);
	threshold(image, image2, 170, 255, 0);
	imwrite("Fingerprint_Left.jpg", image2);
	image = imread("medianblur2.jpg", 1);
	threshold(image, image2, 220, 255, 0);
	imwrite("Fingerprint_Right.jpg", image2);



	cout << "Finished filtering images" << endl;

	return 0;
}