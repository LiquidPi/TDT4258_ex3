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
	
Using 'framebuffer_interface.c' :
----------------------------------
	+ Call first "Initialize" to set up module
	+ To draw to screen, call "DrawPixel" or "DrawPixels".
	+ Apply changes (show on screen); call "Refresh" after drawing.
	+ When closing application, call "Destroy" to unmap memory and close files.
	+ Use coordinates x{0,320} and y{0,240}, with origo in the bottom-left corner.
	+ The current default color is white.
	+ Use "ClearScreen" to set every pixel to default background color (black)