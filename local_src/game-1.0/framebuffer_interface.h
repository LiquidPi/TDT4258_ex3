#ifndef FRAMEBUFFER_INTERFACE_
#define FRAMEBUFFER_INTERFACE_

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
#define TOTAL_BYTES 153600
#define BYTES_PER_PIXEL 2

#define WHITE 0xFFFF
#define BLACK 0x0000


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
void ClearScreen(void);

/*  Signal the framebuffer to update screen contents
 *  Note: should be called after every "draw" or "clear" action.
 *  Input:  none
 *  Output: none
 */
void Refresh(void);

/*  Dealocate memory and closes framebuffer
 *  Input:  none
 *  Output: int status: 0 for success, -1 for error
 */
int Destroy(void);

#endif
