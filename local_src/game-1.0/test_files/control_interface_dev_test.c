#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "control_interface_dev.h"

int main(int argc, char *argv[])
{
	printf("Start test\n");
	bool runLoop = true;
	struct gamepad currentInput;
	while (runLoop)
	{
		currentInput = GetCurrentInput();
		if (currentInput.up_1)
			printf("UP 1       \n");
		if (currentInput.up_2)
			printf("UP 2       \n");
		if (currentInput.down_1)
			printf("DOWN 1     \n");
		if (currentInput.down_2)
			printf("DOWN 2     \n");
		if (currentInput.start)
		{
			runLoop = false;
			printf("START      \n");
		}
	};
	printf("Finised test\n");
	exit(EXIT_SUCCESS);
}
