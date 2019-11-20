#include <stdint.h>

#ifdef linux_build

#include "gwint.h"
#define COLORTYPE uint32_t
#define COLOR(r, g, b) (r << 16 | (g << 8) | (b << ) )
#define SETPIXEL(x, y, color) DrawPixel(x, y, color)

#else

#include "framebuffer_interface.h"
#define SETPIXEL(x, y) SetPixel(x, y)
#define INIT_DRAWING() Initialize()
#define DIRTY(x, y, w, h) RefreshArea(x, y, w, h);

#endif


#define WINDOW_W ((int)320) //Width of window
#define WINDOW_H ((int)240) //Hight of window


void drawRectangle(int x, int y, int width, int height);
void drawLine(int x1, int y1, int x2, int y2);
void blitImage(uint16_t* imageData, int width, int height);