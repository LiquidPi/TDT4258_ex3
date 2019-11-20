#ifndef CONTROL_INTERFACE_
#define CONTROL_INTERFACE_

#include <stdbool.h>

#define BUTTON_UP_0 (1<<1)
#define BUTTON_DOWN_0 (1<<3)
#define BUTTON_UP_1 (1<<5)
#define BUTTON_DOWN_1 (1<<7)
#define BUTTON_START (1<<0)

struct gamepad {
	bool up_0;
	bool down_0;
	bool up_1;
	bool down_1;
	bool start;
};

/*  Initialize the gamepad interface
 *  Input:  none
 *  Output: status code; 0 for successful, -1 for error.
 */
int InitializeControl (void);

/*  Get input from gamepad 
 *  Input:  none
 *  Output: struct gamepad, collection of various inputs signals from gamepad
 */
struct gamepad GetCurrentInput (void);

/*  Destroy the gamepad interface
 *  Input:  none
 *  Output: status code; 0 for successful, -1 for error.
 */
int DestroyController(void);

#endif
