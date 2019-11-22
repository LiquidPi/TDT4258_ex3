#ifndef DRAWAPI_
#define DRAWAPI_

#include <stdint.h>
#include "framebuffer_interface.h"

#define WINDOW_W ((int)320) //Width of window
#define WINDOW_H ((int)240) //Hight of window
#define NAIVE_BORDER 10

#define SETPIXEL(x, y) SetPixel(x, y)
#define INIT_DRAWING() Initialize()
#define DIRTY(x, y, w, h) RefreshArea(x, y, w, h);

/*  Draw a rectangle on screen.
 *  Input:  int x: x-coordinate of the bottom-left corner
 *			int y: y-coordinate of the bottom-left corner
 *          int width: the width of the rectangle
 *			int height: the height of the rectangle
 *  Output: none
 */
void drawRectangle(int x, int y, int width, int height);

#endif
