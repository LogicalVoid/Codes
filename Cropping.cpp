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
	uchar pixValue = 255;
	//Left Image Cropping
	for (int i = 0; i < imgs[0].cols - (imgs[0].cols/2-50); i++) {
		for (int j = 0; j < imgs[0].rows; j++) {
			Vec3b &intensity = imgs[0].at<Vec3b>(j, i);
			for (int k = 0; k < imgs[0].channels(); k++) {
				// calculate pixValue
				intensity.val[k] = pixValue;
			}
		}
	}
	//Top side
	for (int i = imgs[0].cols - (imgs[0].cols/2 - 50); i < imgs[0].cols; i++) {
		for (int j = 0; j < 975; j++) {
			Vec3b &intensity = imgs[0].at<Vec3b>(j, i);
			for (int k = 0; k < imgs[0].channels(); k++) {
				// calculate pixValue
				intensity.val[k] = pixValue;
			}
		}
	}
	//Bottom side
	for (int i = imgs[0].cols - (imgs[0].cols/2 - 50); i < imgs[0].cols; i++) {
		for (int j = imgs[0].rows - 525; j < imgs[0].rows; j++) {
			Vec3b &intensity = imgs[0].at<Vec3b>(j, i);
				for (int k = 0; k < imgs[0].channels(); k++) {
					// calculate pixValue
					intensity.val[k] = pixValue;
				}
		}
	}
	//Left Image Cropping

	//Right Image Cropping
	for (int i = imgs[1].cols - 1200; i < imgs[1].cols; i++) {
		for (int j = 0; j < imgs[1].rows; j++) {
			Vec3b &intensity = imgs[1].at<Vec3b>(j, i);
			for (int k = 0; k < imgs[1].channels(); k++) {
				// calculate pixValue
				intensity.val[k] = pixValue;
			}
		}
	}
	//Top Side
	for (int i = 0; i < imgs[1].cols - 1200; i++) {
		for (int j = 0; j < 900; j++) {
			Vec3b &intensity = imgs[1].at<Vec3b>(j, i);
			for (int k = 0; k < imgs[1].channels(); k++) {
				// calculate pixValue
				intensity.val[k] = pixValue;
			}
		}
	}
	//Bottom Side
	for (int i = 0; i < imgs[1].cols - 1200; i++) {
		for (int j = imgs[1].rows - 600; j < imgs[0].rows; j++) {
			Vec3b &intensity = imgs[1].at<Vec3b>(j, i);
			for (int k = 0; k < imgs[1].channels(); k++) {
				// calculate pixValue
				intensity.val[k] = pixValue;
			}
		}
	}
	
	Mat replacement_left(imgs[0].rows - 1450, imgs[0].cols / 2 - 50, CV_8UC3, Scalar(0, 0, 0));
	Mat replacement_right(imgs[1].rows - 1500, imgs[1].cols - 1200, CV_8UC3, Scalar(0,0,0));
	
	int left_rows = imgs[0].rows - 1500;
	int left_cols = imgs[0].cols / 2 - 50;
	int left_end = imgs[0].cols - (imgs[0].cols / 2 - 50);
	int left_topbeg = 950;

	int right_rows = imgs[1].rows - 1500;
	int right_cols = imgs[1].cols - 1200;
	int right_topbeg = 900;
	int right_end = 0;

	for (int i = 0; i < left_cols; i++) {
		for (int j = 0; j < left_rows; j++) {
			Vec3b &intensity = imgs[0].at<Vec3b>(left_topbeg + j, left_end + i);
			Vec3b &intensity_left = replacement_left.at<Vec3b>(j, i);
			for (int k = 0; k < imgs[0].channels(); k++) {
				intensity_left.val[k] = intensity.val[k];
			}
		}
	}

	for (int i = 0; i < right_cols; i++) {
		for (int j = 0; j < right_rows; j++) {
			Vec3b &intensity = imgs[1].at<Vec3b>(right_topbeg + j, right_end + i);
			Vec3b &intensity_right = replacement_right.at<Vec3b>(j, i);
			for (int k = 0; k < imgs[1].channels(); k++) {
				intensity_right.val[k] = intensity.val[k];
			}
		}
	}
	cout << 

	imwrite("Left.jpg", imgs[0]);
	imwrite("Right.jpg", imgs[1]);
	imwrite("Left_cropped.jpg", replacement_left);
	imwrite("Right_cropped.jpg", replacement_right);
	cout << "finished cropping images";
	
	return 0;
}