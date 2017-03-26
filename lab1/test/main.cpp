#include <math.h>
#include <stdio.h>
#include "gl/glut.h"

const GLfloat PI = 3.1415926f;

void drawStar(GLfloat long_edge, GLfloat color[])
{
	GLfloat short_edge, r; 
	GLfloat theta = 0.5 * PI; 
	GLint i;  
	
	short_edge = long_edge * (sin(0.1*PI) / sin(0.7*PI)); 
	glColor3fv(color); 
	glBegin(GL_TRIANGLE_FAN); 
		glVertex3f(0.0f, 0.0f, 0.5f); 
		for(i = 0; i < 11; i ++)
	    {
			if(i % 2 == 0) r = long_edge; 
			else r = short_edge; 
			glVertex3f(r * cos(theta), r * sin(theta), 0.5f); 
			theta += 0.2 * PI; 
			// printf("%lf %lf\n", r * cos(theta), r * sin(theta)); 
	    }
	glEnd(); 
}

// r1, r2, a = 36`; 
// l, s
// s / sin(18`) = l / sin(126`)
// s = l * (sin(18`) / sin(126`))
// 
// (-0.25, 0.25) 
// for(i = 0; i < 11; i += 1)
// cos = cos(last + a) = coslast cosa - sinlast sina; 
// sin = sin(last + a) = sinlast cosa + coslast sina; 
void display()
{
	GLfloat long_edge, short_edge, r; 
	GLfloat a = 0.2*PI; 
	GLfloat sin_a = sin(a), cos_a = cos(a); 
	GLfloat sin_last, cos_last; 
	GLint i;  
	long_edge = 0.25; 
	short_edge = long_edge * (sin(0.1*PI) / sin(0.7*PI)); 
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1, 0, 0);
	glBegin(GL_QUADS);
	glVertex3f(-0.75, 0.5, 0.5);
	glVertex3f(0.75, 0.5, 0.5);
	glVertex3f(0.75, -0.5, 0.5);
	glVertex3f(-0.75, -0.5, 0.5);
	glEnd();

	GLfloat color[3] = {1.0f, 1.0f, 0.0f}; 
	// glRotatef(180.0f, 0.0f, 0.0f, -1.0f); 
	// glTranslatef(-0.0f, 0.0f, 0.0f); 
	// (-0.34, 0.25)
	glLoadIdentity(); 
	glTranslatef(-0.5f, 0.25f, 0.0f); 
	drawStar(0.15, color); 

	glLoadIdentity(); 
	glTranslatef(-0.5f, 0.25f, 0.0f); 
	glTranslatef(0.35f, -0.1f, 0.0f); 
	drawStar(0.05, color); 

	glLoadIdentity(); 
	glTranslatef(-0.5f, 0.25f, 0.0f); 
	glRotatef(atan(4.0/5)/PI * 180, 0.0f, 0.0f, -1.0f); 
	glTranslatef(sqrt(0.2 * 0.2 + 0.25 * 0.25), 0.0f, 0.0f); 
	drawStar(0.05, color); 

	glLoadIdentity(); 
	glTranslatef(-0.5f, 0.25f, 0.0f); 
	glRotatef(atan(1.0/7)/PI * 180, 0.0f, 0.0f, 1.0f); 
	glTranslatef(sqrt(0.35 * 0.35 + 0.05 * 0.05), 0.0f, 0.0f); 
	drawStar(0.05, color); 

	glLoadIdentity(); 
	glTranslatef(-0.5f, 0.25f, 0.0f); 
	glRotatef(atan(3.0/5)/PI * 180, 0.0f, 0.0f, 1.0f); 
	glTranslatef(sqrt(0.25 * 0.25 + 0.15 * 0.15), 0.0f, 0.0f); 
	drawStar(0.05, color); 

	glLoadIdentity(); 
//        sin_last = 1.0f; cos_last = 0.0f; 
//        glVertex3f(0.0f, 0.0f, 0.5f); 
//        for(i = 0; i < 11; i++)
//	    {
//			if(i % 2 == 0) r = long_edge; 
//			else r = short_edge; 
//			glVertex3f(r * cos_last, r * sin_last, 0.5f); 
//			sin_last = sin_last * cos_a + cos_last * sin_a; 
//			cos_last = cos_last * cos_a - sin_last * sin_a; 
//			printf("%lf %lf\n", r * cos_last, r * sin_last); 
//	    }

	glutSwapBuffers();
}

int main (int argc,  char *argv[])
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);
	glutInitWindowPosition(10, 10);
	glutInitWindowSize(400, 400);
	glutCreateWindow("Simple GLUT App");

	glutDisplayFunc(display);

	glutMainLoop();

	return 0;
}