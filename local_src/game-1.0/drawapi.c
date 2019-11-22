#include "drawapi.h"

int r = 0;
int g = 0;
int b = 0;

void drawRectangle(int x, int y, int width, int height) {
	int yp, xp;
	for(yp = y; yp < height+y; yp++) {
		for(xp = x; xp < width+x; xp++) {
			SETPIXEL(xp, yp);
		}
	}
	int xb = x-NAIVE_BORDER;
	int yb = y-NAIVE_BORDER;
	int wb = width+NAIVE_BORDER+NAIVE_BORDER;
	int hb = height+NAIVE_BORDER+NAIVE_BORDER;

	if(xb < 0) {
		xb = 0;
	}
	if(yb < 0) {
		yb = 0;
	}
	if(wb+xb > WINDOW_W) {
		wb = WINDOW_W-xb-1;
	}
	if(hb+yb > WINDOW_H) {
		hb = WINDOW_H-yb-1;
	}
}
