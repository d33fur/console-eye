#include <iostream>
#include <ostream>
//#include <istream>
#include <vector>
#include "VecMath.h"

#if defined(_WIN32)
#define WIN32_LEAN_AND_MEAN
#define VC_EXTRALEAN
#include <Windows.h>
#elif defined(__linux__)
#include <unistd.h>
#include <sys/ioctl.h>

//#include <term.h>
#endif

void getTerminalSize(int& width, int& height) {
#if defined(_WIN32)
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    width = (int)(csbi.srWindow.Right-csbi.srWindow.Left+1);
    height = (int)(csbi.srWindow.Bottom-csbi.srWindow.Top+1);
#elif defined(__linux__)
    struct winsize w;
    ioctl(fileno(stdout), TIOCGWINSZ, &w);
    width = (int)(w.ws_col);
    height = (int)(w.ws_row);
#endif
    std::cout << width << " " << height << std::endl;
}

char gradient[] = " .:!/r(l1Z4H9W8$@";
int gradientSize = std::size(gradient) - 2;


void ballFunction(int& width, int& height) {
    float consoleSizeRatio = (float)(width / height);
    float pixelRatio = 11.0f / 24.0f;
    char* buf = new char[width * height];

    std::ostream& os = std::cout;
    //std::array<char, 128> buffer;
    //setbuf(buf, sizeof(buf));
    //GetStdHandle(STD_OUTPUT_HANDLE);
    //HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    //SetConsoleActiveScreenBuffer(hConsole);
    //DWORD dwBytesWritten = 0;

    vec3 light = norm(vec3(-0.5, 0.5, -1.0));
    vec3 spherePos = vec3(0, 3, 0);
    for (int t = 0; t < 10000; t++) {
        vec3 light = norm(vec3(-0.5, 0.5, -1.0));
        vec3 spherePos = vec3(0, 3, 0);
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                vec2 uv = vec2(i, j) / vec2(width, height) * 2.0f - 1.0f;
                uv.x *= consoleSizeRatio * pixelRatio;
                vec3 ro = vec3(-6, 0, 0);
                vec3 rd = norm(vec3(2, uv));
                ro = rotateY(ro, 0.25);
                rd = rotateY(rd, 0.25);
                ro = rotateZ(ro, t * 0.01);
                rd = rotateZ(rd, t * 0.01);
                float diff = 1;
                for (int k = 0; k < 5; k++) {
                    float minIt = 99999;
                    vec2 intersection = sphere(ro - spherePos, rd, 1);
                    vec3 n = 0;
                    float albedo = 1;
                    if (intersection.x > 0) {
                        vec3 itPoint = ro - spherePos + rd * intersection.x;
                        minIt = intersection.x;
                        n = norm(itPoint);
                    }
                    vec3 boxN = 0;
                    intersection = box(ro, rd, 1, boxN);
                    if (intersection.x > 0 && intersection.x < minIt) {
                        minIt = intersection.x;
                        n = boxN;
                    }
                    intersection = plane(ro, rd, vec3(0, 0, -1), 1);
                    if (intersection.x > 0 && intersection.x < minIt) {
                        minIt = intersection.x;
                        n = vec3(0, 0, -1);
                        albedo = 0.5;
                    }
                    if (minIt < 99999) {
                        diff *= (dot(n, light) * 0.5 + 0.5) * albedo;
                        ro = ro + rd * (minIt - 0.01);
                        rd = reflect(rd, n);
                    } else break;
                }
                int color = (int) (diff * 20);
                color = clamp(color, 0, gradientSize);
                char pixel = gradient[color];
                buf[i + j * width] = pixel;
            }

        }
        buf[width * height - 1] = '\0';
        os << buf << "\r";
        //WriteConsoleOutputCharacter(hConsole, buf, width * height, { 0, 0 }, &dwBytesWritten);
    }

    //os <<  << "\r";
    //struct winsize w;
    //ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    /*
    for(int i = 0; i < 100; i++) {

        os << i << "\r";
        os.flush();
        sleep(1);
    }
     */
}

void cubeFunction() {

}

void donutFunction() {

}

void picOrVidFunction() {

}

int main() {
    std::cout << "Hello, this is a console viewer!" << std::endl;
    std::cout << "Choose an object: 1 - ball, 2 - cube, 3 - donut, 4 - picture or video" << std::endl;
    std::cout << "Write the object number: " << std::endl;
    int width, height, answer;
    getTerminalSize(width, height);
    std::cin >> answer;
    switch(answer) {
        case 1:
            ballFunction(width, height);
            break;
        case 2:
            cubeFunction();
            break;
        case 3:
            donutFunction();
            break;
        case 4:
            picOrVidFunction();
            break;
    }
    return 0;
}
