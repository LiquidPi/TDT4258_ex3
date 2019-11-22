#ifndef GWINT_H_   
#define GWINT_H_

struct color
{
	float red;
	float green;
	float blue;
	float alpha;
};

struct pixel 
{
	//Position of pixel (with origo in bottom-left corner)
	int xpos;
	int ypos;
	/*struct color color_of_pixel;*/
};

/*  Setup of a OpenGL window, as a development screen. 
 *  Input:  int* argc:   Passed from int argc of int main
 *		    char** argv: Passed from char** argv of int main
 *  Output: none
 */
void SetupOfWindow(int* argc, char** argv);

/*  Clears the window, setting every pixel to default color defined in SetupOfWindow.
 *  Input:  none
 *  Output: none
 */
void ClearWindow(void);

/*  Draws pixels based on a list of coordinates.
 *  Input:  struct pixel p[]:  array of points(pixels) to be drawn.
 *			int size: 		   size of array p[].
 *  Output: none
 */
void Draw(struct pixel p[], int size);

/*  Draws a singular pixel
 *  Input:  int x:          The x coordinate of the pixel
 *          int y:          The y coordinate of the pixel
 *          uint32_t color: The color of the pixel
 *  Output: none
 */
void DrawPixel(int x, int y, uint32_t color);

/*  Updates the window, applying any changes made by Draw and ClearWindow.
 *  Input:  none
 *  Output: none
 */
void UpdateWindow(void);

#endif
