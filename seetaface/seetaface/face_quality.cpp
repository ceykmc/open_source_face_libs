#include "Struct_cv.h"
#include "face_quality.h"

FaceQuality::FaceQuality()
{
	m_quality_assessor = new seeta::QualityAssessor();
}

FaceQuality::~FaceQuality()
{
	if (m_quality_assessor) {
		delete m_quality_assessor;
		m_quality_assessor = nullptr;
	}
}

float FaceQuality::evaluate(
	const cv::Mat& image,
	const SeetaRect& face_rect,
	const std::vector<SeetaPointF>& face_landmarkers)
{
	seeta::cv::ImageData seeta_image = image;
	float score = m_quality_assessor->evaluate(
		seeta_image, face_rect, face_landmarkers.data());
	return score;
}