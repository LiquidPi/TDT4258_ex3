#ifndef CONTROL_INTERFACE_DEV_
#define CONTROL_INTERFACE_DEV_

#include <stdbool.h>

struct gamepad {
	bool up_1;
	bool down_1;
	bool up_2;
	bool down_2;
	bool start;
};

/*  Get input from gamepad (keyboard)
 *	Currently bound to 'w', 's', 'Key_up', 'Key_down', and 'e'. 
 *  Input:  none
 *  Output: struct gamepad, collection of various inputs signals from gamepad
 */
struct gamepad GetCurrentInput (void);

#endif
