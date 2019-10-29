#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h> //OpenGL

#include "gwint.h"

const int WINDOW_W = 320;
const int WINDOW_H = 240;

void Setup(int* argc, char** argv)
{
	//Setup openGL window
	glutInit(argc, argv);
	glutCreateWindow("game");
	glutInitWindowSize(WINDOW_W, WINDOW_H);
	glutInitWindowPosition(50, 50);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); //Black and opaque
	glutDisplayFunc(Clear);
}

void Clear(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}

void Draw(struct pixel p[], int size)
{
	//Clear screen
	glClear(GL_COLOR_BUFFER_BIT);
	//Draw the list
	glBegin(GL_POINTS);
		glColor3f(1.0f, 1.0f, 1.0f); //White
		int i;
		for (i = 0; i < size; i++)
		{
			//Convert to OpenGL coords and draw
			float x = -1.0f + ((float)p[i].xpos * 2) / (float)WINDOW_W;
			float y = -1.0f + ((float)p[i].ypos * 2) / (float)WINDOW_H;
			glVertex2f(x, y);
		}
	glEnd();
	glFlush();
}
