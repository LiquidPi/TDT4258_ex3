#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //For sleep function; debug

#include "framebuffer_interface.h"

int main(int argc, char** argv) {
	printf("Start game!\n");
	int x;
	int y;
	for (x = 100; x < 150; x++)
	{
		for (y = 100; y < 150; y++)
		{
			DrawPixel(x, y);
		}
	}
	printf("All pixels drawn\n");
	printf("Goodbye!\n");
    return 0;
}

