// CURRENTLY FUNCTIONS AS A TESTBENCH FOR GWINT.C

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //For sleep function; debug

#include "drawapi.h"

//Game state
int ballx = WINDOW_W/2;
int bally = WINDOW_H/2;

//Draw game components

void drawPaddle(int x, int y) {
	drawRectangle(x, y, 15, 100);
}

void drawLeftPaddle() {
	drawPaddle(10, WINDOW_H/2-50);
}

void drawRightPaddle() {
	drawPaddle(WINDOW_W-10-30, WINDOW_H/2-50);
}

void drawBall() {
	drawRectangle(ballx, bally, 20, 20);
}

//Function for debugging the gwint module
void dbg_gwint(int argc, char** argv)
{
	printf("gwinit\n");
	INIT_DRAWING(&argc, argv);
	int count = 0;
	printf("Drawing loop\n");
	while(1)
	{
		ClearWindow();

		drawLeftPaddle();
		drawRightPaddle();
		drawBall();

		UpdateWindow();
		usleep(1000*100);
		if(count > 100) {
			count = 0;
		}
		count++;
	}
}

int main(int argc, char** argv) {
	setbuf(stdout, NULL);
	printf("Hello, world");
	dbg_gwint(argc, argv);
	while(1)
	{
		//nothing
	}
    return 0;
}

