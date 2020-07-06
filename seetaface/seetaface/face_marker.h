#pragma once

#include <vector>

#include <opencv2/opencv.hpp>
#include <seeta/FaceLandmarker.h>

class FaceMarker
{
private:
	seeta::FaceLandmarker* m_face_marker;
public:
	FaceMarker(int point_number = 5);

	~FaceMarker();

	std::vector<SeetaPointF> mark(
		const cv::Mat& image, const SeetaRect& face_rect);
};
