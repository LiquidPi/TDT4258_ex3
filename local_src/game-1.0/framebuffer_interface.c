#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "framebuffer_interface.h"

void DrawPixel(int x, int y)
{
	
	int fb = open("dev/fb0", O_RDWR);
	if (fb < 0)
		printf("Error, couldn't open frame buffer (fb0).");
	//Calculate offset based on coordinates
	int offset = ((SCREEN_HEIGHT - y) * SCREEN_WIDTH + x) * BYTES_PER_PIXEL;
	//Go to word repesenting the pixel
	lseek(fb, offset, SEEK_CUR);
	//Color it white
	write(fb, WHITE, BYTES_PER_PIXEL);
	//Go back to the beginning of the file.
	lseek(fb, (-1)*offset, SEEK_CUR);
	
	int error = close(fb);
	if (error < 0)
		printf("Error, couldn't close frame buffer.");
}

/*

	---------> y
	|
	|
	|	Coordinate system from landscape perspective.
	|
	v
	x
	
*/
