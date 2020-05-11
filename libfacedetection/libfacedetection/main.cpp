#include <iostream>
#include <facedetection/facedetectcnn.h>
#include <opencv2/opencv.hpp>

constexpr auto DETECT_BUFFER_SIZE = 0x20000;

void draw_detected_faces(
    const cv::Mat& image, const int* pResults, const int threshold = 80)
{
    if (!pResults) {
        return;
    }
    for (int i = 0; i < *pResults; i++) {
        short * p = ((short*)(pResults + 1)) + 142 * i;
        int confidence = p[0];

        if (p[0] < threshold) {
            continue;
        }

        int x = p[1];
        int y = p[2];
        int w = p[3];
        int h = p[4];

        //show the score of the face. Its range is [0-100]
        char sScore[256];
        snprintf(sScore, 256, "%d", confidence);
        cv::putText(
            image, sScore, cv::Point(x, y - 3),
            cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 255, 0), 1);
        //draw face rectangle
        rectangle(image, cv::Rect(x, y, w, h), cv::Scalar(0, 255, 0), 2);
        //draw five face landmarks in different colors
        cv::circle(image, cv::Point(p[5], p[5 + 1]), 1, cv::Scalar(255, 0, 0), 2);
        cv::circle(image, cv::Point(p[5 + 2], p[5 + 3]), 1, cv::Scalar(0, 0, 255), 2);
        cv::circle(image, cv::Point(p[5 + 4], p[5 + 5]), 1, cv::Scalar(0, 255, 0), 2);
        cv::circle(image, cv::Point(p[5 + 6], p[5 + 7]), 1, cv::Scalar(255, 0, 255), 2);
        cv::circle(image, cv::Point(p[5 + 8], p[5 + 9]), 1, cv::Scalar(0, 255, 255), 2);

        //print the result
        printf("face %d: confidence=%d, [%d, %d, %d, %d] (%d,%d) (%d,%d) (%d,%d) (%d,%d) (%d,%d)\n",
            i, confidence, x, y, w, h,
            p[5], p[6], p[7], p[8], p[9], p[10], p[11], p[12], p[13], p[14]);

    }
}

int main(int argc, char** argv)
{
    if (argc < 3) {
        std::cout << "need image or video path." << std::endl;
        system("pause");
        return -1;
    }
    std::string detect_type = argv[1];
    if (detect_type == "--image") {
        const char* image_path = argv[2];
        cv::Mat image = cv::imread(image_path);
        cv::resize(image, image, cv::Size(640, 480));

        int* pResults = NULL;
        //pBuffer is used in the detection functions.
        //If you call functions in multiple threads, please create one buffer for each thread!
        unsigned char * pBuffer = (unsigned char *)malloc(DETECT_BUFFER_SIZE);
        if (!pBuffer)
        {
            std::cerr << "Can not alloc buffer" << std::endl;
            return -1;
        }

        cv::TickMeter cvtm;
        for (int i = 0; i < 100; ++i) {
            cvtm.start();
            pResults = facedetect_cnn(
                pBuffer, (unsigned char*)(image.ptr(0)),
                image.cols, image.rows, (int)image.step);
            cvtm.stop();
        }
        std::cout << "average face detect time: "
            << cvtm.getTimeMilli() / cvtm.getCounter()
            << std::endl;

        cv::Mat result_image = image.clone();
        draw_detected_faces(result_image, pResults);
        cv::imshow("result", result_image);
        cv::waitKey();
        free(pBuffer);
    }
    else {
        std::cout << "unsupported detect type: " << detect_type << std::endl;
        system("pause");
        return -1;
    }
    return 0;
}
