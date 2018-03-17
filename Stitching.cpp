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
	int trials = 1;
	int permutation[3] = { 0 };
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

	// Create a Stitcher class object with mode panoroma
	Ptr<Stitcher> stitcher = Stitcher::create(mode, false);

	// Command to stitch all the images present in the image array
	Stitcher::Status status = stitcher->stitch(imgs, pano);

	do {
		for (int i = 0; i < 2; i++) {
			Mat img = imread(argv[permutation[i] + 1]);
		}
		Ptr<Stitcher> stitcher = Stitcher::create(mode, true);
		Stitcher::Status status = stitcher->stitch(imgs, pano);	// Command to stitch all the images present in the image array
		if (status == Stitcher::OK) {
			imwrite("result.jpg", pano);
			cout << "Image Stitched, Trials" << trials << endl;
			return 0;
		}
		trials++;
	} while (next_permutation(permutation, permutation + 3));
	cout << " Cannot stitch image, trials: " << trials << endl;

	return 0;
}