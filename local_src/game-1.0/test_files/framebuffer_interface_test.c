#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //For sleep function; debug

#include "framebuffer_interface.h"

void PrintTestPattern (void)
{
	int x;
	int y;
	for (x = 135; x < 185; x++)
	{
		for (y = 95; y < 145; y++)
		{
			SetPixel(x, y);
		}
	}
	
	for (x = 0; x < 50; x++)
	{
		for (y = 0; y < 50; y++)
		{
			SetPixel(x, y);
		}
	}
	
	for (x = 270; x < 320; x++)
	{
		for (y = 0; y < 50; y++)
		{
			SetPixel(x, y);
		}
	}
	
	for (x = 0; x < 50; x++)
	{
		for (y = 190; y < 240; y++)
		{
			SetPixel(x, y);
		}
	}
	
	for (x = 270; x < 320; x++)
	{
		for (y = 190; y < 240; y++)
		{
			SetPixel(x, y);
		}
	}
}

void Test2 (void)
{
	while(1)
	{
		PrintTestPattern();
		Refresh();
		sleep(1);
		ClearScreen();
		Refresh();
		sleep(1);
	}
}

int main(int argc, char** argv) {
	printf("Start game!\n");

	Initialize();
	//PrintTestPattern();
	//Refresh();
	Test2();
	Destroy();
	
	printf("All pixels drawn\n");
	printf("Goodbye!\n");
    return 0;
}



