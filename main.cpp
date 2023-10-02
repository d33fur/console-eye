#include <iostream>
#include <stdio.h>
#include <libavutil/imgutils.h>
#include <libavcodec/avcodec.h>
#include <libswscale/swscale.h>
#include <opencv2/opencv.hpp>
#include <ncurses.h>

using namespace cv;
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

WINDOW *create_newwin(int height, int width, int starty, int startx);
void destroy_win(WINDOW *local_win);

int main(int argc, char *argv[]) {
	

if (argc != 2) {
	printf("usage: DisplayImage.out <Image_Path//Vid_Path>\n");
	return -1;
}
else
	printf("\neverything is ok!\n\n\n\n");


	

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

