#pragma once

#include <vector>
#include <opencv2/opencv.hpp>

struct Face
{
    int m_score;
    cv::Rect m_loc;
    std::vector<cv::Point> m_landmarks;
};

class FaceDetector
{
private:
    unsigned char* m_buffer;
public:
    FaceDetector();

    ~FaceDetector();

    std::vector<Face> detect(const cv::Mat& image, int threshold = 50);
};
