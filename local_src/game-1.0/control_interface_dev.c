#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <curses.h>
#include <stdbool.h>

#include "control_interface_dev.h"

struct gamepad GetCurrentInput (void)
{
	struct gamepad gamepad_instance = {false, false, false, false, false};
	initscr();
	timeout(10); //For how long to wait for input
	cbreak();
    keypad(stdscr, TRUE);
    int i;
	for (i = 0; i < 3; i++)
	{
		int c = getch();
		switch (c) {
			case 'w':
				gamepad_instance.up_1 = true;
				break;
			case 's':
				gamepad_instance.down_1 = true;
				break;
			case KEY_UP:
				gamepad_instance.up_2 = true;
				break;
			case KEY_DOWN:
				gamepad_instance.down_2 = true;
				break;
			case 'e':
				gamepad_instance.start = true;
				break;
		}
		endwin();
	}
	return gamepad_instance;	
}
