#pragma once

#include <vector>

#include <seeta/FaceDetector.h>
#include <opencv2/opencv.hpp>

class FaceDetector
{
private:
	seeta::FaceDetector* m_face_detector;

public:
	FaceDetector();

	~FaceDetector();

	SeetaFaceInfoArray detect_face(const cv::Mat& image);
};
