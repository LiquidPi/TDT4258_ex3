#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fqcntl.h>
#include <unistd.h>

#include "control_interface.h"

struct gamepad GetCurrentInput (void)
{
	int gd = open("/dev/gamepad", O_RDONLY);
	if (gd < 0)
		printf("Error, could not open gamepad driver!\n");
		
	char gdmap;
	int err = read(gd, &gdmap, 1);
	if (err < 0)
		printf("Error, couldn't read gamepad driver!\n");
		
	struct gamepad gamepad_instance = {
		gdmap & BUTTON_UP_0, 
		gdmap & BUTTON_DOWN_0, 
		gdmap & BUTTON_UP_1, 
		gdmap & BUTTON_DOWN_1, 
		gdmap & BUTTON_START
	};
	
	err = close(gd);
	if (err < 0)
		printf("Error, couldn't close gamepad driver!\n");
	
	return gamepad_instance;
}
