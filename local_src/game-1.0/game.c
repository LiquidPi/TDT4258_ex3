#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //For sleep function; debug

#include "framebuffer_interface.h"

int main(int argc, char** argv) {
	printf("Start game!\n");
	int x;
	int y;
	
	//Middle
	for (x = 135; x < 185; x++)
	{
		for (y = 95; y < 145; y++)
		{
			DrawPixel(x, y);
		}
	}
	
	//Bottom-left
	for (x = 0; x < 50; x++)
	{
		for (y = 0; y < 50; y++)
		{
			DrawPixel(x, y);
		}
	}
	
	//Bottom-right
	for (x = 270; x < 320; x++)
	{
		for (y = 0; y < 50; y++)
		{
			DrawPixel(x, y);
		}
	}
	
	//Upper- left
	for (x = 0; x < 50; x++)
	{
		for (y = 190; y < 240; y++)
		{
			DrawPixel(x, y);
		}
	}
	
	//Upper-right
	for (x = 270; x < 320; x++)
	{
		for (y = 190; y < 240; y++)
		{
			DrawPixel(x, y);
		}
	}
	
	printf("All pixels drawn\n");
	printf("Goodbye!\n");
    return 0;
}

