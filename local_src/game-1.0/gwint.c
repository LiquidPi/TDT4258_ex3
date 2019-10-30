#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h> //OpenGL

#include "gwint.h"
#include "drawapi.h"

void SetupOfWindow(int* argc, char** argv)
{
	glutInit(argc, argv);
	glutCreateWindow("Development Screen");
	glutInitWindowSize(WINDOW_W, WINDOW_H);
	glutInitWindowPosition(50, 50);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
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

void DrawPixel(int x, int y, uint32_t color) {
	glBegin(GL_POINTS);
	glColor3f(1.0f, 1.0f, 1.0f);

	float xf = -1.0f + ((float)x * 2) / (float)WINDOW_W;
	float yf = -1.0f + ((float)y * 2) / (float)WINDOW_H;
	
	//Draw
	glVertex2f(xf, yf);

	glEnd();
}

void UpdateWindow(void)
{
	glFlush();
}
