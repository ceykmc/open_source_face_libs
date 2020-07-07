#include "Struct_cv.h"
#include "face_detector.h"

FaceDetector::FaceDetector()
{
    seeta::ModelSetting::Device device = seeta::ModelSetting::CPU;
    int id = 0;
    seeta::ModelSetting FD_model("./models/face_detector.csta", device, id);

	m_face_detector = new seeta::FaceDetector(FD_model);
	m_face_detector->set(seeta::FaceDetector::PROPERTY_MIN_FACE_SIZE, 20);
	m_face_detector->set(seeta::FaceDetector::PROPERTY_THRESHOLD, 0.2);
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
