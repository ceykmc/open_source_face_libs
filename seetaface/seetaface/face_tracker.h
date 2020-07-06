#pragma once

#include <opencv2/opencv.hpp>
#include <seeta/FaceTracker.h>

class FaceTracker
{
private:
	seeta::FaceTracker* m_face_tracker;
public:
	FaceTracker();

	~FaceTracker();

	SeetaTrackingFaceInfoArray track(const cv::Mat& image);
};
