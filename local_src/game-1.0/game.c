// CURRENTLY FUNCTIONS AS A TESTBENCH FOR GWINT.C

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //For sleep function; debug

#include "gwint.h"

int main(int argc, char** argv) {

	Setup(&argc, argv);
	
	struct pixel box[] = {
		{3,3},
		{4,3},
		{5,3},
		{3,4},
		{5,4},
		{3,5},
		{4,5},
		{5,5}};
	int size = 8;
	Draw(box, size);
	while(1)
	{
		//nothing
	}
    return 0;
}
