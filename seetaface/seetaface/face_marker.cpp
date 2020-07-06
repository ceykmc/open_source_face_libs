#include "face_marker.h"
#include "Struct_cv.h"

FaceMarker::FaceMarker(int point_number)
{
	std::string point_model_path = "./model/pd_2_00_pts5.dat";
	if (point_number == 81) {
		point_model_path = "./model/pd_2_00_pts81.dat";
	}
	seeta::ModelSetting::Device device = seeta::ModelSetting::CPU;
	int id = 0;
	seeta::ModelSetting point_setting(point_model_path, device, id);

	m_face_marker = new seeta::FaceLandmarker(point_setting);
}

FaceMarker::~FaceMarker()
{
	if (m_face_marker) {
		delete m_face_marker;
		m_face_marker = nullptr;
	}
}

std::vector<SeetaPointF> FaceMarker::mark(
	const cv::Mat& image, const SeetaRect& face_rect)
{
	seeta::cv::ImageData seeta_image = image;
	return m_face_marker->mark(seeta_image, face_rect);
}
