#include <iostream>
#include <chrono>

#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>


cv::RNG rng(12345);

cv::Mat detectEllipses(const cv::Mat& src,
	const std::vector<std::vector<cv::Point>>& contours,
	std::vector<cv::RotatedRect>& minRect,
	std::vector<cv::RotatedRect>& minEllipse) {
	cv::Mat result;

	minRect.resize(contours.size());
	minEllipse.resize(contours.size());

	for (int i = 0; i < contours.size(); i++) {
		minRect[i] = cv::minAreaRect(cv::Mat(contours[i]));
		if (contours[i].size() > 5) {
			minEllipse[i] = cv::fitEllipse(cv::Mat(contours[i]));
		}
	}

	result = src.clone();
	for (int i = 0; i < contours.size(); i++) {
		cv::Scalar color = cv::Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		cv::drawContours(result, contours, i, color, 1, 8, std::vector<cv::Vec4i>(), 0, cv::Point());
		cv::ellipse(result, minEllipse[i], color, 2, 8);
		cv::Point2f rect_points[4]; minRect[i].points(rect_points);
		for (int j = 0; j < 4; j++) cv::line(result, rect_points[j], rect_points[(j + 1) % 4], color, 1, 8);
	}
	return result;
}


cv::Mat detectHoughCircles(const cv::Mat& src) {
	cv::Mat result, gray;

	cv::cvtColor(src, gray, CV_BGR2GRAY);

	// opcionális zajszűrés
	cv::GaussianBlur(gray, gray, cv::Size(5, 5), 2, 2);

	std::vector<cv::Vec3f> circles;
	cv::HoughCircles(gray, circles, CV_HOUGH_GRADIENT,
		2, gray.rows / 8, 100, 20, 0, 50);

	src.copyTo(result);
	for (size_t i = 0; i < circles.size(); i++)
	{
		cv::Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);
		// középpont
		cv::circle(result, center, 3, cv::Scalar(0, 255, 0), -1, 8, 0);
		// körvonal
		cv::circle(result, center, radius, cv::Scalar(0, 0, 255), 3, 8, 0);
	}
	return result;
}

//std::vector<std::vector<cv::Point>> contours;

cv::Mat detectContours(const cv::Mat& src, std::vector<std::vector<cv::Point>>& contours) {
	cv::Mat result, canny_output;

	int thresh = 100;
	cv::Mat src_gray;
	cv::cvtColor(src, src_gray, CV_BGR2GRAY);

	std::vector<cv::Vec4i> hierarchy;
	cv::Canny(src_gray, canny_output, thresh, thresh * 2, 3);
	cv::findContours(canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));

	result = cv::Mat::zeros(canny_output.size(), CV_8UC3);
	for (int i = 0; i < contours.size(); i++) {
		cv::Scalar color = cv::Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		cv::drawContours(result, contours, i, color, 2, 8, hierarchy, 0, cv::Point());
	}
	return result;
}

cv::Mat detectHoughLines_v2(const cv::Mat& src)
{
	cv::Mat edgeImage, result;
	cv::Canny(src, edgeImage, 50, 200, 3);
	cv::cvtColor(edgeImage, result, CV_GRAY2BGR);

	std::vector<cv::Vec4i> lines;
	cv::HoughLinesP(edgeImage, lines, 1, CV_PI / 180, 50, 20, 10);
	for (size_t i = 0; i < lines.size(); i++) {
		cv::Vec4i l = lines[i];
		line(result, cv::Point(l[0], l[1]), cv::Point(l[2], l[3]),
			cv::Scalar(0, 0, 255), 2, CV_AA);
	}

	return result;
}

cv::Mat detectHoughLines(const cv::Mat& src)
{
	cv::Mat edgeImage, result;
	cv::Canny(src, edgeImage, 50, 200, 3);
	cv::cvtColor(edgeImage, result, CV_GRAY2BGR);

	std::vector<cv::Vec2f> lines;
	cv::HoughLines(edgeImage, lines, 1, CV_PI / 180, 100, 0, 0);

	for (size_t i = 0; i < lines.size(); i++) {
		float rho = lines[i][0], theta = lines[i][1];
		cv::Point pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a * rho, y0 = b * rho;
		pt1.x = cvRound(x0 + 1000 * (-b));
		pt1.y = cvRound(y0 + 1000 * (a));
		pt2.x = cvRound(x0 - 1000 * (-b));
		pt2.y = cvRound(y0 - 1000 * (a));
		line(result, pt1, pt2, cv::Scalar(0, 0, 255), 2, CV_AA);
	}
	return result;
}

int main(int argc, char* argv[]) {
	cv::VideoCapture capture;
	bool success = true;

	//success = capture.open(0);
	//success = capture.open("C:/BME/1.felev/KiterjesztettValosag/labor3/catvideos/cat_640x360.mp4");
	//success = capture.open("C:\\BME\\1.felev\\KiterjesztettValosag\\labor3\\03_Marker_videos\\ARmarker.avi");
	success = capture.open("C:\\BME\\1.felev\\KiterjesztettValosag\\labor3\\03_Marker_videos\\BlueRedCircles2.mp4");

	if (!success) {
		std::cerr << "Unable to open video capture" << std::endl;
		return 0;
	}


	cv::namedWindow("Input");
	cv::namedWindow("Processed");

	cv::Mat frame;
	cv::Mat resized;
	cv::Mat processed;
	cv::Mat gray;
	cv::Mat x;
	cv::Mat a;
	cv::Mat mask;
	cv::Mat overlay = cv::imread("C:\\BME\\1.felev\\KiterjesztettValosag\\labor3\\03_Marker_images\\marker.bmp");
	resize(overlay, overlay, cv::Size(640, 480));

	std::vector<cv::Point2f> inputPoints = {
			cv::Point2f(0, 0),
			cv::Point2f(overlay.cols - 1, 0),
			cv::Point2f(overlay.cols - 1, overlay.rows - 1),
			cv::Point2f(0, overlay.rows - 1),
	};

	std::vector<cv::RotatedRect> minRect;
	std::vector<cv::RotatedRect> minEllipse;


	while (capture.read(frame))
	{
		//test_xxx(frame); // itt hívjuk a képfeldolgozó függvényeket
		resize(frame, resized, cv::Size(640, 480));
		//processed = detectHoughLines_v2(resized);
		//processed = detectHoughCircles(resized);

		cv::cvtColor(resized, gray, CV_BGR2GRAY);
		cv::threshold(gray, x, 100, 110, cv::ThresholdTypes::THRESH_BINARY);
		mask = resized.clone();
		a = resized.clone();
		mask.setTo(cv::Scalar(0.0, 0.0, 0.0));
		a.setTo(cv::Scalar(0.0, 0.0, 0.0));
		/*mask = resized.clone();
		cv::circle(mask, cv::Point(100, 100), 100, cv::Scalar(255, 255, 255), -1);*/

		//cv::inRange(x, 100, 110, mask);
		//cv::bitwise_not(x, x);
		//cv::cvtColor(mask, mask, CV_GRAY2BGR);
		//cv::cvtColor(overlay, overlay, CV_GRAY2BGR);
		//processed = ~mask & resized;

		std::vector<std::vector<cv::Point>> contours;
		detectContours(resized, contours);

		//processed = detectContours(resized, contours);
		processed = detectEllipses(resized, contours, minRect, minEllipse);

		std::vector< std::vector<cv::Point> > polygons;
		//polygons.push_back({ cv::Point(0, 0), cv::Point(0, 100), cv::Point(100, 100), cv::Point(100, 0) });
		int i = 0;
		for (cv::RotatedRect r : minRect)
		{
			++i;
			if (i % 2 == 0)
				continue;
			cv::Point2f pts[4];
			r.points(pts);
			std::vector<cv::Point> vs;
			vs.push_back(cv::Point((int)pts[0].x, (int)pts[0].y));
			vs.push_back(cv::Point((int)pts[1].x, (int)pts[1].y));
			vs.push_back(cv::Point((int)pts[2].x, (int)pts[2].y));
			vs.push_back(cv::Point((int)pts[3].x, (int)pts[3].y));

			polygons.push_back(vs);
		}
		cv::fillPoly(mask, polygons, cv::Scalar(255, 255, 255));

		processed = ~mask & resized;

		std::vector < std::vector<cv::Point>> v2;
		//cv::Mat(polygons).convertTo(v2, cv::Mat(v2).type());

		v2.push_back(polygons[9]);

		for (auto p : polygons)
		{
			cv::Mat y;
			std::vector<cv::Point2f> outputPoints = {
			cv::Point2f(p[0].x, p[0].y),
			cv::Point2f(p[1].x, p[1].y),
			cv::Point2f(p[2].x, p[2].y),
			cv::Point2f(p[3].x, p[3].y),
			};
			cv::Mat transformMat = cv::getPerspectiveTransform(inputPoints, outputPoints);
			cv::warpPerspective(overlay, y, transformMat, overlay.size());
			//cv::cvtColor(y, y, CV_GRAY2BGR);
			a = a + y;
			//a = y;
		}
		
		processed = (~mask & resized) +(a & mask);
		


		cv::imshow("Input", frame);
		cv::imshow("Processed", processed);

		char key = static_cast<char>(cv::waitKey(1));
		if (key == 27) { std::cout << "Exiting..." << std::endl; break; }
	}

	return 0;
}
