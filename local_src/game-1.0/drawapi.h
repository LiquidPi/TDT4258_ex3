#include <stdint.h>
#include "gwint.h"

#ifdef linux
#define COLORTYPE uint32_t
#define COLOR(r, g, b) (r << 16 | (g << 8) | (b << ) )
#define SETPIXEL(x, y, color) DrawPixel(x, y, color)
#define INIT_DRAWING(argc, argv) SetupOfWindow(argc, argv)
#else
#error Only linux builds are supported
#endif


#define WINDOW_W ((int)320) //Width of window
#define WINDOW_H ((int)240) //Hight of window


void drawRectangle(int x, int y, int width, int height);
void drawLine(int x1, int y1, int x2, int y2);
void blitImage(uint16_t* imageData, int width, int height);