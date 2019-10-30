// CURRENTLY FUNCTIONS AS A TESTBENCH FOR GWINT.C

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //For sleep function; debug

#include "gwint.h"

//Function for debugging the gwint module
void dbg_gwint(int argc, char** argv)
{
	struct color background_color = {0.0f, 0.0f, 0.0f, 1.0f};
	SetupOfWindow(&argc, argv, background_color);
	
	struct pixel box[] = {
		{3,3},
		{4,3},
		{5,3},
		{3,4},
		{5,4},
		{3,5},
		{4,5},
		{5,5}};
	struct pixel box2[] = {
		{13,13},
		{14,13},
		{15,13},
		{13,14},
		{15,14},
		{13,15},
		{14,15},
		{15,15}};	
	struct pixel box3[] = {
		{23,23},
		{24,23},
		{25,23},
		{23,24},
		{25,24},
		{23,25},
		{24,25},
		{25,25}};
		
	int size = 8;
	while(1)
	{
		Draw(box, size);
		UpdateWindow();
		sleep(1);
		Draw(box2, size);
		UpdateWindow();
		sleep(1);
		Draw(box3, size);
		UpdateWindow();
		sleep(1);
		ClearWindow();
		UpdateWindow();
		sleep(1);
	}
}


int main(int argc, char** argv) {
	dbg_gwint(argc, argv);
	while(1)
	{
		//nothing
	}
    return 0;
}

