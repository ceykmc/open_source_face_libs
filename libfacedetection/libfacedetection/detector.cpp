#include "detector.h"
#include <facedetection/facedetectcnn.h>

constexpr auto DETECT_BUFFER_SIZE = 0x20000;

FaceDetector::FaceDetector()
{
    m_buffer = (unsigned char *)malloc(DETECT_BUFFER_SIZE);
}

FaceDetector::~FaceDetector()
{
    if (m_buffer) {
        free(m_buffer);
        m_buffer = nullptr;
    }
}

std::vector<Face> FaceDetector::detect(const cv::Mat& image, int threshold)
{
    std::vector<Face> results;
    int* p_results = nullptr;
    p_results = facedetect_cnn(
        m_buffer, (unsigned char*)(image.ptr(0)),
        image.cols, image.rows, (int)image.step);
    if (p_results) {
        for (int i = 0; i < *p_results; i++) {
            short * p = ((short*)(p_results + 1)) + 142 * i;
            int score = p[0];
            if (score < threshold) {
                continue;
            }
            struct Face face;
            face.m_score = score;
            face.m_loc = cv::Rect(p[1], p[2], p[3], p[4]);
            for (int j = 0; j < 10; j += 2) {
                cv::Point landmark(p[5 + j], p[5 + j + 1]);
                face.m_landmarks.push_back(landmark);
            }
            results.push_back(face);
        }
    }
    return results;
}
