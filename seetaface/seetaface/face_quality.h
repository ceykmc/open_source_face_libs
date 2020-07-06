#pragma once

#include <vector>

#include <seeta/QualityAssessor.h>
#include <opencv2/opencv.hpp>

class FaceQuality
{
private:
	seeta::QualityAssessor* m_quality_assessor;
public:
	FaceQuality();

	~FaceQuality();

	float evaluate(
		const cv::Mat& image,
		const SeetaRect& face_rect,
		const std::vector<SeetaPointF>& face_landmarkers);
};
