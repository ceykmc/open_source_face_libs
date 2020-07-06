#include "utility.h"

void draw_tracked_faces(
	const cv::Mat& image,
	const SeetaTrackingFaceInfoArray& tracked_faces)
{
	for (int i = 0; i < tracked_faces.size; ++i) {
		const SeetaTrackingFaceInfo& track_face_info = tracked_faces.data[i];
		cv::Rect rect = {
			track_face_info.pos.x,
			track_face_info.pos.y,
			track_face_info.pos.width,
			track_face_info.pos.height
		};
		cv::rectangle(image, rect, cv::Scalar(0, 0, 255), 2);
		std::string info = \
			std::string("id: ") + std::to_string(track_face_info.PID) + " " + \
			std::string("s: ") + std::to_string(int(track_face_info.score * 100));
		cv::putText(
			image, info, cv::Point(rect.x, rect.y - 10),
            cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 255, 255)
		);
	}
}

void draw_detected_faces(
	const cv::Mat& image,
	const SeetaFaceInfoArray& detected_faces)
{
	for (int i = 0; i < detected_faces.size; ++i) {
		const SeetaFaceInfo& detected_face_info = detected_faces.data[i];
		cv::Rect rect = {
			detected_face_info.pos.x,
			detected_face_info.pos.y,
			detected_face_info.pos.width,
			detected_face_info.pos.height
		};
		cv::rectangle(image, rect, cv::Scalar(0, 0, 255), 2);
		std::string info =
			std::string("s: ") + std::to_string(int(detected_face_info.score * 100));
		cv::putText(
			image, info, cv::Point(rect.x, rect.y - 10),
            cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 255, 255)
		);
	}
}

void draw_face_landmarkers(
	const cv::Mat& image,
	const std::vector<SeetaPointF>& landmarkers)
{
	for (const SeetaPointF& marker : landmarkers) {
		cv::Point p(int(marker.x), int(marker.y));
		cv::circle(image, p, 3, cv::Scalar(0, 0, 255), -1);
	}
}

void draw_face_quality(
	const cv::Mat& image,
	const SeetaRect& face_rect,
	float quality)
{
	cv::putText(image,
		std::string("q: ") + std::to_string(int(quality * 100)),
		cv::Point(face_rect.x, face_rect.y + face_rect.height + 20),
        cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 255, 255));
}
