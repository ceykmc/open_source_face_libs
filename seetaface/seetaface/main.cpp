#include <string>
#include <fstream>
#include "face_detector.h"
#include "utility.h"


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
    std::ofstream& out_file, const std::string& image_path, const SeetaFaceInfoArray& faces)
{
    out_file << image_path + "\n";

    for (int i = 0; i < faces.size; ++i) {
        const SeetaFaceInfo& detected_face_info = faces.data[i];
        out_file << int(detected_face_info.score * 100) << " ";
        out_file << detected_face_info.pos.x << " ";
        out_file << detected_face_info.pos.y << " ";
        out_file << detected_face_info.pos.width << " ";
        out_file << detected_face_info.pos.height << std::endl;
    }
}

int main()
{
    FaceDetector face_detector;

    const char* image_file = "F:\\data\\monitor\\monitor_face_val_outdoor_scene1.txt";
    std::vector<std::string> image_paths = read_image_path(image_file);

    std::ofstream out_file("SeetaFace.txt");
    for (size_t i = 0; i < image_paths.size(); i++) {
        std::string image_path = image_paths[i];
        cv::Mat image = cv::imread(image_path);
        cv::resize(image, image, cv::Size(960, 480));
        SeetaFaceInfoArray faces = face_detector.detect_face(image);
        write_detect_result(out_file, image_path, faces);
        std::cout << "progress: " << i + 1 << " / " << image_paths.size() << std::endl;
    }

    return 0;
}