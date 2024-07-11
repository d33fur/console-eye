#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <unistd.h>
#include <sys/ioctl.h>

const std::vector<char> grayScaleChars = {'@', '#', '8', '&', 'o', ':', '*', '.', ' '};

void getTerminalSize(int &width, int &height) {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    width = w.ws_col;
    height = w.ws_row;
}

void imageToAscii(const std::string& imagePath) {
    std::cout << "Loading image: " << imagePath << std::endl;
    cv::Mat image = cv::imread(imagePath, cv::IMREAD_GRAYSCALE);
    if (image.empty()) {
        std::cerr << "Could not open or find the image: " << imagePath << std::endl;
        return;
    }
    std::cout << "Image loaded successfully." << std::endl;

    int terminalWidth, terminalHeight;
    getTerminalSize(terminalWidth, terminalHeight);

    cv::resize(image, image, cv::Size(terminalWidth, terminalHeight));

    for (int y = 0; y < image.rows; ++y) {
        for (int x = 0; x < image.cols; ++x) {
            int pixelValue = image.at<uchar>(y, x);
            char asciiChar = grayScaleChars[pixelValue * grayScaleChars.size() / 256];
            std::cout << asciiChar;
        }
        std::cout << std::endl;
    }
}

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <image_path>" << std::endl;
        return 1;
    }

    std::string imagePath = argv[1];
    std::cout << "Starting ASCII image conversion." << std::endl;
    imageToAscii(imagePath);
    std::cout << "Conversion finished." << std::endl;
    return 0;
}
