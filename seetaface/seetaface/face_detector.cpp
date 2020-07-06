#include "Struct_cv.h"
#include "face_detector.h"

FaceDetector::FaceDetector()
{
	std::string fd_model_path = "./model/fd_2_00.dat";
	seeta::ModelSetting::Device device = seeta::ModelSetting::CPU;
	int id = 0;
	seeta::ModelSetting fd_model_setting(fd_model_path, device, id);
	m_face_detector = new seeta::FaceDetector(fd_model_setting, 640, 480);
	m_face_detector->set(seeta::FaceDetector::PROPERTY_MIN_FACE_SIZE, 10);
	m_face_detector->set(seeta::FaceDetector::PROPERTY_VIDEO_STABLE, 1);
}

FaceDetector::~FaceDetector()
{
	if (m_face_detector) {
		delete m_face_detector;
		m_face_detector = nullptr;
	}
}

SeetaFaceInfoArray FaceDetector::detect_face(const cv::Mat& image)
{
	seeta::cv::ImageData seeta_image = image;
	return m_face_detector->detect(seeta_image);
}
