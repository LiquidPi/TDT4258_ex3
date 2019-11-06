#ifndef FRAMEBUFFER_INTERFACE_
#define FRAMEBUFFER_INTERFACE_

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
#define BYTES_PER_PIXEL 2
#define COLOR_WHITE 0xFF //Check this value!


/*  Initialization of module
 *  Input:  none
 *  Output: none
 */
void InitInterface(void);

/*  Draws a singular (white) pixel to the screen.
 *  (Note: call 'UpdateScreen' for changes to show.)
 *  Input:  int x: x-coordinate
 			int y: y-coordinate
 *  Output: none
 */
void DrawPixel(int x, int y);

/*  Clear screen to default color (black).
 *  (Note: call 'UpdateScreen' for changes to show.)
 *  Input:  none
 *  Output: none
 */
void ClearScreen(void);

/*  Termination of module (clean exit).
 *  Input:  none
 *  Output: none
 */
void TerminateInterface(void);

#endif
