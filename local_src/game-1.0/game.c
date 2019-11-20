#include <stdio.h>
#include <stdlib.h>

#include "control_interface.h"

int main(int argc, char *argv[])
{
	printf("Hello World, I'm game!\n");
	InitializeControl();
	struct gamepad g = GetCurrentInput();
	DestroyController();

	exit(EXIT_SUCCESS);
}
