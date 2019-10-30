#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h> //OpenGL

#include "gwint.h"

const int WINDOW_W = 320; //pixels
const int WINDOW_H = 240; //pixels

void SetupOfWindow(int* argc, char** argv, struct color default_clear_color)
{
	glutInit(argc, argv);
	glutCreateWindow("Development Screen");
	glutInitWindowSize(WINDOW_W, WINDOW_H);
	glutInitWindowPosition(50, 50);
	glClearColor(default_clear_color.red,   \
				 default_clear_color.green, \
				 default_clear_color.blue,  \
				 default_clear_color.alpha);
	glutDisplayFunc(ClearWindow);
	UpdateWindow();
}

void ClearWindow(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void Draw(struct pixel p[], int size)
{
	glBegin(GL_POINTS);
		int i;
		for (i = 0; i < size; i++)
		{
			//Set colour
			/*glColor3f(p[i].color_of_pixel.red,   \
					  p[i].color_of_pixel.green, \
					  p[i].color_of_pixel.blue);*/
			glColor3f(1.0f, 1.0f, 1.0f); //Defult white
			
			//Convert to OpenGL coordinates
			float x = -1.0f + ((float)p[i].xpos * 2) / (float)WINDOW_W;
			float y = -1.0f + ((float)p[i].ypos * 2) / (float)WINDOW_H;
			
			//Draw
			glVertex2f(x, y);
		}
	glEnd();
}

void UpdateWindow(void)
{
	glFlush();
}
