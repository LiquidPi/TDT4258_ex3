###################################### README ################################################

Using 'control_interface_dev.c' :
---------------------------------
	+ It uses the curses/ncurses libraries for keyboard input:
		+ sudo apt-get install libncurses5-dev libncursesw5-dev
	+ Call 'GetCurrentInput' every time one wants to update input (polling).
	+ Uses a struct spesifically for gamepad/game.
	+ Not that good at multiple inputs at the same time, but good enough for testing purposes.
	+ Check 'control_interface_dev_test.c' for sample usage.
	+ Compile with '-lncurses' flag in gcc.
