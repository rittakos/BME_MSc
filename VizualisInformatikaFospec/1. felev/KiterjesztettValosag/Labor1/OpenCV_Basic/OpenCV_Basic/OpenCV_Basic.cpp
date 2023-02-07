#include <iostream>
#include <chrono>

#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

int main(int argc, char* argv[]) {
	cv::VideoCapture capture;
	capture.open("C:\\BME\\1.felev\\Kiterjesztett valosag\\Labor1\\OpenCV_Basic\\catvideos\\cat_640x360.mp4");

	//bool success = true;
	//if (argc < 2) {
	//	// webcam with index 0
	//	success = capture.open(0);
	//}
	//else {
	//	// video file
	//	success = capture.open(argv[1]);
	//}
	//if (!success) {
	//	std::cerr << "Unable to open video capture" << std::endl;
	//	return 0;
	//}

	// folyt kov.
}
