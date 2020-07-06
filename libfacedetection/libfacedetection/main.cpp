#include <string>
#include <fstream>
#include "detector.h"

void draw_faces(cv::Mat &image, const std::vector<Face>& faces)
{
    for (const Face& face : faces) {
        cv::rectangle(image, face.m_loc, cv::Scalar(255, 0, 0), 2);
        for (const cv::Point& landmark : face.m_landmarks) {
            cv::circle(image, landmark, 1, cv::Scalar(0, 0, 255), -1);
        }
    }
    cv::namedWindow("faces", cv::WINDOW_AUTOSIZE);
    cv::imshow("faces", image);
    cv::waitKey();
    cv::destroyWindow("faces");
}

std::vector<std::string> read_image_path(const char* image_file)
{
    std::vector<std::string> image_paths;

    std::ifstream in_file(image_file);
    std::string path;
    while (std::getline(in_file, path, '\n')) {
        image_paths.push_back(path);
    }
    return image_paths;
}

void write_detect_result(
    std::ofstream& out_file, const std::string& image_path, const std::vector<Face>& faces)
{
    out_file << image_path + "\n";
    for (const Face& face : faces) {
        out_file << face.m_score << " ";
        out_file << face.m_loc.x << " " << face.m_loc.y << " " 
                 << face.m_loc.width << " " << face.m_loc.height << " ";
        for (size_t i = 0; i < face.m_landmarks.size(); i++) {
            const cv::Point& point = face.m_landmarks[i];
            if (i < face.m_landmarks.size() - 1) {
                out_file << point.x << " " << point.y << " ";
            }
            else {
                out_file << point.x << " " << point.y;
            }
        }
        out_file << "\n";
    }
}

int main()
{
    FaceDetector detector;

    const char* image_file = "F:\\data\\monitor\\monitor_face_val_outdoor_scene1.txt";
    std::vector<std::string> image_paths = read_image_path(image_file);

    std::ofstream out_file("libfacedetection.txt");
    for (size_t i = 0; i < image_paths.size(); i++) {
        std::string image_path = image_paths[i];
        cv::Mat image = cv::imread(image_path);
        cv::resize(image, image, cv::Size(960, 480));
        std::vector<Face> faces = detector.detect(image, 20);
        write_detect_result(out_file, image_path, faces);
        std::cout << "progress: " << i + 1 << " / " << image_paths.size() << std::endl;
    }

    return 0;
}
