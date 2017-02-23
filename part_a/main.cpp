// !!! math.h is placed before <GL/glut.h> 
#include <math.h>
#include <GL/glut.h>

void myDisplay(void)

{

     glClear(GL_COLOR_BUFFER_BIT);

     glRectf(-0.5f, -0.5f, 0.5f, 0.5f);

     glFlush();

}

// 另一方面，glBegin支持的方式除了GL_POINTS和GL_LINES，
// 还有GL_LINE_STRIP，GL_LINE_LOOP，GL_TRIANGLES，
// GL_TRIANGLE_STRIP，GL_TRIANGLE_FAN等 
void myTryDisplay(void)
{
	const int n = 3000;
	const GLfloat R = 0.5f;
	const GLfloat Pi = 3.1415926536f;
	int i; 

	glClear(GL_COLOR_BUFFER_BIT); 
	/*glBegin(GL_LINES); 
	glVertex2f(-0.1f, -0.1f); 
	glVertex2f(0.5f, 0.5f); */
	glBegin(GL_POINTS/*GL_LINE_LOOP*//*GL_POLYGON*/); // GL_POLYGON, GL_LINE_LOOP, GL_POINTS
     for(i=0; i<n; ++i)
         glVertex2f(R*cos(2*Pi/n*i), R*sin(2*Pi/n*i));
	glEnd(); 
	glFlush(); 
}

// Draw 5 jiaoxing 
void my5Display(void)
{
	const GLfloat Pi = 3.1415926536f; 
	GLfloat a = 1 / (2-2*cos(72*Pi/180));
    GLfloat bx = a * cos(18 * Pi/180);
    GLfloat by = a * sin(18 * Pi/180);
    GLfloat cy = -a * cos(18 * Pi/180);
	
	GLfloat PointA[2] = {0, a}; 
	GLfloat PointB[2] = {bx, by}; 
	GLfloat PointC[2] = {0.5, cy}; 
	GLfloat PointD[2] = {-0.5, cy}; 
	GLfloat PointE[2] = {-bx, by}; 

	glClear(GL_COLOR_BUFFER_BIT); 
	glBegin(GL_LINE_LOOP); 
	    glVertex2fv(PointA); 
		glVertex2fv(PointB); 
		glVertex2fv(PointC); 
		glVertex2fv(PointD); 
		glVertex2fv(PointE); 
	glEnd(); 
	glFlush(); 
}

// Draw sin or cos picture 
void mySinDisplay(void)
{
	const GLfloat factor = 0.01f; 
	GLfloat x; 

	glClear(GL_COLOR_BUFFER_BIT); 
	glBegin(GL_LINES); 
	    glVertex2f(-1.0f, 0.0f); 
		glVertex2f(1.0f, 0.0f); 
		glVertex2f(0.0f, -1.0f); 
		glVertex2f(0.0f, 1.0f); 
	glEnd(); 
	glBegin(GL_LINE_STRIP); 
	for(x = -1.0f/factor; x < 1.0f/factor; x += 0.01f)
		glVertex2f(x * factor, sin(x) * 0.1/*factor*/); 
	glEnd(); 
	glFlush(); 
}

int main(int argc, char *argv[])

{

     glutInit(&argc, argv);

     glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);

     glutInitWindowPosition(100, 100);

     glutInitWindowSize(400, 400);

     glutCreateWindow("第一个OpenGL程序");

     glutDisplayFunc(&mySinDisplay/*my5Display*//*myTryDisplay*//*myDisplay*/);

     glutMainLoop();

     return 0;

}
