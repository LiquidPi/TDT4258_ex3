#include "drawapi.h"

int r = 0;
int g = 0;
int b = 0;
void drawRectangle(int x, int y, int width, int height) {
	for(int yp = y; yp < height+y; yp++) {
		for(int xp = x; xp < width+x; xp++) {
			SETPIXEL(xp, yp, 0);
		}
	}
}
void drawLine(int x1, int y1, int x2, int y2) {
	//Do nothing for now
}
void blitImage(uint16_t* imageData, int width, int height) {
	//Do nothing for now
}