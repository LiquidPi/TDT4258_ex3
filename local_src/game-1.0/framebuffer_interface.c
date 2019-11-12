#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <linux/fb.h>
#include <string.h>

#include "framebuffer_interface.h"

int fbfd;
uint16_t* memory_map = 0;
struct fb_copyarea screen;
struct fb_var_screeninfo vinfo;

int Initialize(void)
{
	//Open framebuffer
	fbfd = open("dev/fb0", O_RDWR);
	if (fbfd < 0)
	{
		printf("Error, couldn't open frame buffer.\n");
		return -1;
	}
	
	//Get Screen Info
	if (ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo) == -1)
	{
		printf("Error, couldn't retrieve screen info.\n");
		return -1;
	}
	screen.dx = 0;
    screen.dy = 0;
    screen.width = vinfo.xres;
    screen.height = vinfo.yres;
    
    //Map to memory
	memory_map = mmap(NULL, TOTAL_BYTES, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0);
	if ((int)memory_map == -1)
	{
		printf("Error, couldn't map memory to frame buffer.\n");
		return -1;
	}
	
	return 0;
}

void SetPixel(int x, int y)
{
	memory_map[getOffset(x,y)] = WHITE;
}

void SetPixels(int x[], int y[], int size)
{
	int i;
	for (i = 0; i < size; i++)
		memory_map[getOffset(x,y)] = WHITE;
}

void ClearScreen(void)
{
	int i;
	for (i = 0; i < (TOTAL_BYTES / BYTES_PER_PIXEL); i++)
		memory_map[i] = BLACK;
}

void Refresh(void)
{
	ioctl(fbfd, 0x4680, &screen);
}

int Destroy(void)
{
	//Close memory map
	munmap(memory_map, TOTAL_BYTES);
	//Close framebuffer	
	int error = close(fbfd);
	if (error < 0)
	{
		printf("Error, couldn't close frame buffer.\n");
		return -1;
	}
	return 0;
}

int getOffset (int x, int y)
{
	return ((SCREEN_HEIGHT - y) * SCREEN_WIDTH + x);
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
