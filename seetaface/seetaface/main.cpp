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
    std::ofstream& out_file,
    const std::string& image_path,
    const SeetaFaceInfoArray& faces,
    const cv::Size& img_size)
{
    out_file << image_path + "\n";

    for (int i = 0; i < faces.size; ++i) {
        const SeetaFaceInfo& detected_face_info = faces.data[i];
        out_file << detected_face_info.score << " ";
        out_file << detected_face_info.pos.x * 1.0f / img_size.width << " ";
        out_file << detected_face_info.pos.y * 1.0f / img_size.height << " ";
        out_file << detected_face_info.pos.width * 1.0f / img_size.width << " ";
        out_file << detected_face_info.pos.height * 1.0f / img_size.height << std::endl;
    }
}

int main(int argc, char** argv)
{
    if (argc < 4) {
        std::cout << "seetaface.exe image_path_list_file img_width img_height" << std::endl;
        return -1;
    }
    const char* image_path_list_file = argv[1];
    int img_width = atoi(argv[2]);
    int img_height = atoi(argv[3]);
    cv::Size img_size(img_width, img_height);

    FaceDetector face_detector;
    std::vector<std::string> image_paths = read_image_path(image_path_list_file);
    std::ofstream out_file("SeetaFace.txt");
    for (size_t i = 0; i < image_paths.size(); i++) {
        std::string image_path = image_paths[i];
        cv::Mat image = cv::imread(image_path);
        cv::resize(image, image, img_size);
        SeetaFaceInfoArray faces = face_detector.detect_face(image);
        write_detect_result(out_file, image_path, faces, img_size);
        std::cout << "progress: " << i + 1 << " / " << image_paths.size() << std::endl;
    }

    return 0;
}