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

	ofstream myfile;
	myfile.open("Fingerprint_Binary.txt");
	for (int i = 0; i < imgs[0].rows; i++) {
		for (int j = 0; j < imgs[0].cols; j++) {
			myfile << imgs[0].at<Vec3b>(i, j);
		}
		myfile << endl;
	}
	myfile.close();
	return 0;

}