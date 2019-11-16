#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

#include "control_interface.h"

int gd;
char gdmap;

int InitializeControl (void)
{
	//Open driver file
	gd = open("/dev/gamepad", O_RDONLY);
	if (gd < 0)
	{
		printf("Error, could not open gamepad driver!\n");
		return -1;
	}
	//Map it to memory
	gdmap = mmap(NULL, 1, PROT_READ | PROT_WRITE, MAP_SHARED, gd, 0);
	if ((int)gdmap == -1)
	{
		printf("Error, couldn't map memory from gamepad driver.\n");
		return -1;
	}
	
	return 0;
}

struct gamepad GetCurrentInput (void)
{
	struct gamepad gamepad_instance = {
		gdmap[0] && BUTTON_UP_0, 
		gdmap[0] && BUTTON_DOWN_0, 
		gdmap[0] && BUTTON_UP_1, 
		gdmap[0] && BUTTON_DOWN_1, 
		gdmap[0] && BUTTON_START
	};
	
	return gamepad_instance;
}

int DestroyController(void)
{
	//Close memory map
	int err = munmap(gdmap, 1);
	//Close file
	int err2 = close(gd);
	if (err < 0 || err2 < 0)
	{
		printf("Error, DestroyController was unsuccessful!");
		return -1;
	}
	return 0;
}
