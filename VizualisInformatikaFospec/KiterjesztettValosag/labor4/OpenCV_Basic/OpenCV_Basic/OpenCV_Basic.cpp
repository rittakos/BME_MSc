#include <iostream>
#include <chrono>

#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

struct Marker
{
	std::vector<cv::Point2f> points;
};

float perimeter(const Marker& marker)
{
	float P = 0.0f;
	for (int idx = 0; idx < marker.points.size() - 1; ++idx)
		P += cv::norm(marker.points[idx] - marker.points[idx + 1]);
	P += cv::norm(marker.points[marker.points.size() - 1] - marker.points[0]);

	return P;
}

void performThreshold(const cv::Mat& grayscale, cv::Mat& thresholdImg)
{
	cv::adaptiveThreshold(
		grayscale,
		thresholdImg,
		255,
		cv::ADAPTIVE_THRESH_GAUSSIAN_C,
		cv::THRESH_BINARY_INV,
		7,
		7
	);
}


void findContours(const cv::Mat& thresholdImg, std::vector<std::vector<cv::Point>>& contours, int minContourPointsAllowed)
{
	std::vector< std::vector<cv::Point> > allContours;
	cv::findContours(thresholdImg, allContours, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);
	contours.clear();
	for (size_t i = 0; i < allContours.size(); i++)
	{
		int contourSize = allContours[i].size();
		if (contourSize > minContourPointsAllowed)
		{
			contours.push_back(allContours[i]);
		}
	}
}


void findMarkerQuads(std::vector<std::vector<cv::Point>>& contours,
	std::vector<Marker>& markers,
	float minContourLengthAllowed)
{
	std::vector<cv::Point> approxCurve;

	for (size_t i = 0; i < contours.size(); i++)
	{
		// Approximate to a polygon
		double eps = contours[i].size() * 0.05;
		cv::approxPolyDP(contours[i], approxCurve, eps, true);
		// We interested only in polygons that contains only four points
		if (approxCurve.size() != 4)
			continue;
		// And they have to be convex
		if (!cv::isContourConvex(approxCurve))
			continue;
		// Ensure that the distance between consecutive points is large enough
		float minDist = std::numeric_limits<float>::max();
		for (int i = 0; i < 4; i++)
		{
			cv::Point side = approxCurve[i] - approxCurve[(i + 1) % 4];
			float squaredSideLength = side.dot(side);
			minDist = std::min(minDist, squaredSideLength);
		}
		// Check that distance is not very small
		if (minDist < minContourLengthAllowed)
			continue;
		// All tests are passed. Save marker candidate:
		Marker m;
		for (int i = 0; i < 4; i++)
			m.points.push_back(cv::Point2f(approxCurve[i].x, approxCurve[i].y));
		// Sort the points in anti-clockwise order
		// Trace a line between the first and second point.
		// If the third point is at the right side, then the pointsare anticlockwise
		cv::Point v1 = m.points[1] - m.points[0];
		cv::Point v2 = m.points[2] - m.points[0];
		double o = (v1.x * v2.y) - (v1.y * v2.x);
		if (o < 0.0) //if the third point is in the left side, then sort in anti - clockwise order
			std::swap(m.points[1], m.points[3]);
		markers.push_back(m);
	}
}

void removeMarkerDuplicates(std::vector<Marker>& markersIn,
	std::vector<Marker>& markersOut)
{
	// Remove these elements which corners are too close to each other.
	// First detect candidates for removal:
	std::vector< std::pair<int, int> > tooNearCandidates;
	for (size_t i = 0; i < markersIn.size(); i++)
	{
		const Marker& m1 = markersIn[i];
		//calculate the average distance of each corner to the nearest corner of the other marker candidate
		for (size_t j = i + 1; j < markersIn.size(); j++)
		{
			const Marker& m2 = markersIn[j];
			float distSquared = 0;
			for (int c = 0; c < 4; c++)
			{
				cv::Point v = m1.points[c] - m2.points[c];
				distSquared += v.dot(v);
			}
			distSquared /= 4;
			if (distSquared < 100)
			{
				tooNearCandidates.push_back(std::pair<int, int>(i, j));
			}
		}
	}
	// Mark for removal the element of the pair with smaller perimeter
	std::vector<bool> removalMask(markersIn.size(), false);
	for (size_t i = 0; i < tooNearCandidates.size(); i++)
	{
		float p1 = perimeter(markersIn[tooNearCandidates[i].first]);
		float p2 = perimeter(markersIn[tooNearCandidates[i].second]);
		size_t removalIndex;
		if (p1 > p2)
			removalIndex = tooNearCandidates[i].second;
		else
			removalIndex = tooNearCandidates[i].first;
		removalMask[removalIndex] = true;
	}
	// Return candidates
	markersOut.clear();
	for (size_t i = 0; i < markersIn.size(); i++)
	{
		if (!removalMask[i])
			markersOut.push_back(markersIn[i]);
	}
}


void removePerspective(const cv::Mat& image, std::vector<Marker>& markers, std::vector<cv::Mat>& canonicalMarkers)
{
	cv::Size markerSize(100, 100);
	std::vector<cv::Point2f> origPoints;
	origPoints.push_back(cv::Point2f(0, 0));
	origPoints.push_back(cv::Point2f(markerSize.width - 1, 0));
	origPoints.push_back(cv::Point2f(markerSize.width - 1, markerSize.height - 1));
	origPoints.push_back(cv::Point2f(0, markerSize.height - 1));

	cv::Mat canonicalMarker;

	for (size_t iMarker = 0; iMarker < markers.size(); ++iMarker)
	{
		Marker& marker = markers[iMarker];
		// getPerspectiveTransform requires points with floating point coordinates
		std::vector<cv::Point2f> points;
		for (int i = 0; i < marker.points.size(); ++i)
		{
			points.push_back(marker.points[i]);
		}

		// Find the perspective transfomation that brings current marker to rectangular form
		cv::Mat M = cv::getPerspectiveTransform(points, origPoints);
		// Transform image to get a canonical marker image
		cv::warpPerspective(image, canonicalMarker, M, markerSize);

		canonicalMarkers.push_back(canonicalMarker);
	}


}

void getValue(const cv::Mat& marker)
{
	//cv::rotate(marker, marker, cv::ROTATE_90_CLOCKWISE);
	//cv::rotate(marker, marker, cv::ROTATE_90_CLOCKWISE);
	//std::vector<std::string> result;
	std::string result = "";
	//std::cout << marker.at<cv::Vec3b>(cv::Point(34, 34)) << std::endl;
	int w0 = 5;
	int h0 = 10;
	int w = (marker.size().width / 3) / 8;
	int h = (marker.size().width / 3) / 7;
	int x = 0;
	int y = 0;
	for (int y = 0; y < 7; ++y)
	{
		if (y == 5 || y == 6)
			continue;
		//std::string line = "";
		for (int x = 0; x < 8; ++x)
		{
			if (x == 0 || x == 6 || x == 7)
				continue;

			if (x != 2 && x != 4)
				continue;

			//std::cout << marker.at<cv::Vec3b>(cv::Point(x * w + w0, y * h + h0)) << std::endl;
			if (marker.at<cv::Vec3b>(cv::Point(x * w + w0, y * h + h0)) == cv::Vec3b(0, 0, 0))
				result += "0";
			else
				result += "1";
		}
		//result.push_back(line);
	}

	std::cout << result << std::endl;
}

int main(int argc, char* argv[]) {
	cv::VideoCapture capture;
	bool success = true;

	success = capture.open("markers.jpg");

	if (!success) {
		std::cerr << "Unable to open video capture" << std::endl;
		return 0;
	}


	cv::namedWindow("Input");
	cv::namedWindow("Processed");

	cv::Mat frame;


	while (capture.read(frame))
	{
		cv::Mat resized;
		resize(frame, resized, cv::Size(640, 480));
		cv::Mat gray;
		cvtColor(resized, gray, CV_BGR2GRAY);

		cv::Mat bw;
		performThreshold(gray, bw);

		std::vector< std::vector<cv::Point> > contours;
		findContours(bw, contours, 100);

		cv::Mat contourImage = cv::Mat::zeros(bw.rows, bw.cols, CV_8UC3);
		cvtColor(contourImage, contourImage, CV_BGR2GRAY);
		/*for (int i = 0; i < contours.size(); ++i)
		{
			drawContours(contourImage, contours, i, cv::Scalar(255, 255, 255));
		}*/

		std::vector<Marker> markers;
		findMarkerQuads(contours, markers, 5.0f);
		std::vector<Marker> canonicalMarkers;
		removeMarkerDuplicates(markers, canonicalMarkers);

		//removePerspective()

		//cv::Mat contourImage2 = cv::Mat::zeros(bw.rows, bw.cols, CV_8UC3);
		std::vector< std::vector<cv::Point> > newContours;
		for (int i = 0; i < canonicalMarkers.size(); ++i)
		{
			std::vector<cv::Point> p;
			for (auto x : canonicalMarkers[i].points)
				p.push_back(cv::Point(x.x, x.y));
			newContours.push_back(p);
		}

		for (int i = 0; i < newContours.size(); ++i)
			drawContours(contourImage, newContours, i, cv::Scalar(255, 255, 255));

		std::vector<cv::Mat> canonicalMats;
		removePerspective(frame, canonicalMarkers, canonicalMats);

		for (size_t i = 0; i < canonicalMarkers.size(); ++i)
		{
			cvtColor(canonicalMats[i], canonicalMats[i], CV_BGR2GRAY);
			cv::threshold(canonicalMats[i], canonicalMats[i], 125, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
		}
		//cv::threshold(canonicalMats[0], canonicalMats[0], 125, 255, cv::THRESH_BINARY);

		getValue(canonicalMats[0]);

		imshow("Input", frame);
		//imshow("Processed", contourImage);
		imshow("Marker", canonicalMats[2]);

		while (true)
		{
			char key = static_cast<char>(cv::waitKey(1));
			if (key == 27) { printf("exit"); return 0; }
		}
	}


	return 0;
}
