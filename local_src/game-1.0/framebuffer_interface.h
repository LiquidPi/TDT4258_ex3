#ifndef FRAMEBUFFER_INTERFACE_
#define FRAMEBUFFER_INTERFACE_

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
#define TOTAL_BYTES 153600
#define BYTES_PER_PIXEL 2

#define WHITE 0xFFFF  // Default drawing color
#define BLACK 0x0000  // Default background color


/*  Opens framebuffer, maps it to memory
 *  Input:  none
 *  Output: int status: 0 for success, -1 for error
 */
int Initialize(void);

/*  Draws a singular pixel to the screen.
 *  Input:  int x: x-coordinate
 			int y: y-coordinate
 *  Output: none
 */
void SetPixel(int x, int y);

/*  Draws pixels from array to screen
 *  Input:  int x[]: array of x-coordinate
 			int y[]: array of y-coordinate
 			int size: size of both arrays
 *  Output: none
 */
void SetPixels(int x[], int y[], int size);

/*  Clears the whole screen to default background color (black).
 *  Input:  none
 *  Output: none
 */
void ClearAll(void);

/*  Clears a limited area (rectangle) to default background color (black), defined by the parameters.
 *  Input:  int dx: bottom-left corner position (x-coord)
 			int dy: bottom-left corner position (y-coord)
 			int width: width of the rectangle
 			int heigth: height of the rectangle
 *  Output: none
 */
void ClearArea(int dx, int dy, int width, int height);

/*  Signal the framebuffer to update the whole screen
 *  Input:  none
 *  Output: none
 */
void RefreshAll(void);

/*  Signal the framebuffer to update a limited area (rectangle), defined by the parameters.
 *  Input:  int dx: bottom-left corner position (x-coord)
 			int dy: bottom-left corner position (y-coord)
 			int width: width of the rectangle
 			int heigth: height of the rectangle
 *  Output: none
 */
void RefreshArea(int dx, int dy, int width, int height);

/*  Dealocate memory and closes framebuffer
 *  Input:  none
 *  Output: int status: 0 for success, -1 for error
 */
int Destroy(void);

#endif
