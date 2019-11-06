#ifndef FRAMEBUFFER_INTERFACE_
#define FRAMEBUFFER_INTERFACE_

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
#define BYTES_PER_PIXEL 2

/*  Draws a singular pixel to the screen.
 *  Input:  int x: x-coordinate
 			int y: y-coordinate
 *  Output: none
 */
void DrawPixel(int x, int y);

#endif
