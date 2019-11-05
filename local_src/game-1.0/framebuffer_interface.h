#ifndef FRAMEBUFFER_INTERFACE_
#define FRAMEBUFFER_INTERFACE_

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

/*  Calls to framebuffer to process any changes made to the screen.
 *  Input:  none
 *  Output: none
 */
void UpdateScreen(void);

#endif
