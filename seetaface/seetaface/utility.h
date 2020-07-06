#pragma once

#include <opencv2/opencv.hpp>
#include <seeta/CTrackingFaceInfo.h>
#include <seeta/CFaceInfo.h>

void draw_tracked_faces(
	const cv::Mat& image,
	const SeetaTrackingFaceInfoArray& tracked_faces);

void draw_detected_faces(
	const cv::Mat& image,
	const SeetaFaceInfoArray& detected_faces);

void draw_face_landmarkers(
	const cv::Mat& image,
	const std::vector<SeetaPointF>& landmarkers);

void draw_face_quality(
	const cv::Mat& image,
	const SeetaRect& face_rect,
	float quality);
