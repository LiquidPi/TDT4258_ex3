#ifndef GWINT_H_   
#define GWINT_H_

const int WINDOW_W; //Width of window
const int WINDOW_H; //Hight of window

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
 			colour default_clear_colour: Sets the default colour used when clearing the window (function Clear).
 *  Output: none
 */
void SetupOfWindow(int* argc, char** argv, struct color default_clear_color);

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

/*  Updates the window, applying any changes made by Draw and ClearWindow.
 *  Input:  none
 *  Output: none
 */
void UpdateWindow(void);

#endif
