#ifndef GWINT_H_   
#define GWINT_H_

const int WINDOW_W;
const int WINDOW_H;

struct pixel 
{
	int xpos;
	int ypos;
};

/*  Setup of a OpenGL window, for development
 *  Input:  int* argc:   Passed from int argc of int main
 *		    char** argv: Passed from char** argv of int main
 *  Output: none
 */
void Setup(int* argc, char** argv);

/*  Clears the window, setting every pixel to default colour (black)
 *  Input:  none
 *  Output: none
 */
void Clear(void);

/*  Draws pixels in white, based on a list of coordinates (origin at bottom-left)
 *  Input:  struct pixel p[]:  array of points(pixels) to be drawn.
 			int size: 		   size of array p[].
 *  Output: none
 */
void Draw(struct pixel p[], int size);

#endif
