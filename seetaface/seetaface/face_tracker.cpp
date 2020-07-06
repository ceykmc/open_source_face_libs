#include "face_tracker.h"
#include "Struct_cv.h"

FaceTracker::FaceTracker()
{
	std::string fd_model_path = "./model/fd_2_00.dat";
	seeta::ModelSetting::Device device = seeta::ModelSetting::CPU;
	int id = 0;
	seeta::ModelSetting fd_model_setting(fd_model_path, device, id);
	m_face_tracker = new seeta::FaceTracker(fd_model_setting, 1920, 1080);
	m_face_tracker->set(seeta::FaceTracker::PROPERTY_MIN_FACE_SIZE, 30);
	m_face_tracker->set(seeta::FaceTracker::PROPERTY_VIDEO_STABLE, 1);
}

FaceTracker::~FaceTracker()
{
	if (m_face_tracker) {
		delete m_face_tracker;
		m_face_tracker = nullptr;
	}
}

SeetaTrackingFaceInfoArray FaceTracker::track(const cv::Mat& image)
{
	seeta::cv::ImageData seeta_image = image;
	return m_face_tracker->track(seeta_image);
}
