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
	int xb = x-20;
	int yb = y-20;
	int wb = width+20;
	int hb = height+20;

	if(xb < 0) {
		xb = 0;
	}
	if(yb < 0) {
		yb = 0;
	}
	if(wb+xb > WINDOW_W) {
		wb = WINDOW_W-xb;
	}
	if(hb+yb > WINDOW_H) {
		hb = WINDOW_H-yb;
	}

	DIRTY(xb, yb, wb, hb);
}
void drawLine(int x1, int y1, int x2, int y2) {
	//Do nothing for now
}
void blitImage(uint16_t* imageData, int width, int height) {
	//Do nothing for now
}
