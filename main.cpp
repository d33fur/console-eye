#include <iostream>
#include <stdio.h>
#include <fstream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "opencv2/core/utils/logger.hpp"
#include <ncurses.h>
#include <unistd.h>
#include <sys/ioctl.h>
using namespace cv;
using namespace std;
/*
int main(int argc, char** argv)
{
	    if (argc != 2) {
		            printf("usage: DisplayImage.out <Image_Path>\n");
			            return -1;
				        }
	        Mat image;
		    image = imread(argv[1], 1);
		        if (!image.data) {
				        printf("No image data \n");
					        return -1;
						    }
			    namedWindow("Display Image", WINDOW_AUTOSIZE);
			        imshow("Display Image", image);
				    waitKey(0);
				        return 0;
}

*/

WINDOW *create_newwin(int height, int width, int starty, int startx) {
	WINDOW *local_win;
	local_win = newwin(height, width, starty, startx);
	box(local_win, 0 , 0);
        wrefresh(local_win);
        return local_win;
}

void destroy_win(WINDOW *local_win) {
	wborder(local_win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
	wrefresh(local_win);
	delwin(local_win);
}


void getTerminalSize(int& width, int& height) {
	struct winsize w;
    ioctl(fileno(stdout), TIOCGWINSZ, &w);
    width = (int)(w.ws_col);
    height = (int)(w.ws_row);
}

void imageProcess(cv::Mat img, vector<int> grey_value) {
	// дописать адаптивный скейл
	ofstream ofile;
	//cout << "add contrast 1-2 (1-1.5 recommended): ";
	double c = 1; // вроде бы самый оптимальный контраст
	int width, height;
	getTerminalSize(width, height);
	float consoleSizeRatio = (float)(width / height);
    float pixelRatio = 11.0f / 24.0f;
	float rowRatio, colRatio, ratio = img.cols / img.rows;
	if(width < height) {
		rowRatio = height * ratio;
		colRatio = width;
	}
	else {
		rowRatio = height;
		colRatio = width * ratio;

	}
	Mat imgBW,imgC;
	cvtColor(img, imgBW, COLOR_BGR2GRAY);
	imgBW.convertTo(imgC, -1, c, 0);
 
	for (int r = 0, k = 0; r < imgC.rows && k < height-1; r+=img.rows/rowRatio, k++) {
		for (int c = 0, l = 0; c < imgC.cols && l < width; c+=img.cols/colRatio, l++) {
			if (imgC.at<uint8_t>(r, c) == 255) {
				cout << " ";
				continue;
			}
			int x = imgC.at<uint8_t>(r, c);
			int ci = 0;
			for (int a = 34; a <= 126; a++) { 
				if (abs(grey_value[ci] - x) > abs(grey_value[a - 33] - x))
					ci = a - 33;
			}
			cout << (char)(ci + 33);
		}
		cout << endl;
	}


}


int main(int argc, char *argv[]) {
	//cv::utils::logging::setLogLevel(cv::utils::logging::LogLevel::LOG_LEVEL_SILENT)
	if (argc != 2) {
		printf("usage: eye <Path>\n");
		return -1;
	}
	string path = argv[1];
	//переписать проверку на тип файла
	//сделать find '.' после нее записывать в переменную
	//потом создать map со всеми расширениями и просто
	//проверять наличие переменной в мапе

	ifstream ifile;
	ifile.open("values.txt");
	vector<int> grey_value;
	for (int i = 0; i < (126 - 33 + 1); i++) {
		int x; 
		ifile >> x >> x;
		grey_value.push_back(x);
	}

	cv::VideoCapture cap(path);
	if (!cap.isOpened()) {
		std::cerr << "ERROR: Could not open video " << path << std::endl;
		return 1;
	}
	WINDOW *my_win;
	int startx, starty, width, height;
	int ch;
	initscr();
	cbreak();
	keypad(stdscr, TRUE);
	height = 3;
	width = 10;
	starty = (LINES - height) / 2;
	startx = (COLS - width) / 2;
	printw("Press F1 to exit");
	refresh();
	//my_win = create_newwin(height, width, starty, startx);
	while((ch = getch()) != KEY_F(1)) {
		/*
		switch(ch) {
			case KEY_LEFT:
				destroy_win(my_win);
				my_win = create_newwin(height, width, starty,--startx);
				break;
			case KEY_RIGHT:
				destroy_win(my_win);
				my_win = create_newwin(height, width, starty,++startx);
				break;
			case KEY_UP:
				destroy_win(my_win);
				my_win = create_newwin(height, width, --starty,startx);
				break;
			case KEY_DOWN:
				destroy_win(my_win);
				my_win = create_newwin(height, width, ++starty,startx);
				break;
 	 		} */
		destroy_win(my_win);
		int frame_count = 0;
		bool should_stop = false;
		while(!should_stop) {
			cv::Mat frame;
			float scale = 1;
			cap >> frame;
			if (frame.empty()) {
			should_stop = true;
			continue;
			}
			imageProcess(frame, grey_value);
			//my_win = create_newwin(height, width, starty, startx);
			refresh();
			frame_count++;
		}

	}
	endwin();

/*
	WINDOW *my_win;
	int startx, starty, width, height;
	int ch;
	



	initscr();
	cbreak();
	keypad(stdscr, TRUE);
	height = 3;
	width = 10;
	starty = (LINES - height) / 2;
	startx = (COLS - width) / 2;
	printw("Press F1 to exit");
	refresh();
	my_win = create_newwin(height, width, starty, startx);
	while((ch = getch()) != KEY_F(1)) {
		switch(ch) {
			case KEY_LEFT:
				destroy_win(my_win);
				my_win = create_newwin(height, width, starty,--startx);
				break;
			case KEY_RIGHT:
				destroy_win(my_win);
				my_win = create_newwin(height, width, starty,++startx);
				break;
			case KEY_UP:
				destroy_win(my_win);
				my_win = create_newwin(height, width, --starty,startx);
				break;
			case KEY_DOWN:
				destroy_win(my_win);
				my_win = create_newwin(height, width, ++starty,startx);
				break;
 	 		}
        }
	endwin();
	return 0; */
}

