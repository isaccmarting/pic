#include <math.h>
#include <GL/glut.h>

/*
 * 注意：glColor系列函数，在参数类型不同时，表示“最大”颜色的值也不同。
 * 采用f和d做后缀的函数，以1.0表示最大的使用。
 * 采用b做后缀的函数，以127表示最大的使用。
 * 采用ub做后缀的函数，以255表示最大的使用。
 * 采用s做后缀的函数，以32767表示最大的使用。
 * 采用us做后缀的函数，以65535表示最大的使用。
 *
 */
void myDisplay(void)
{
     glClear(GL_COLOR_BUFFER_BIT);
     glColor3f(0.0f, 1.0f, 1.0f);
     glRectf(-0.5f, -0.5f, 0.5f, 0.5f);
     glFlush();
}

// glClearColor and glClearIndex 
void myCLDisplay(void)
{
     glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
     glClear(GL_COLOR_BUFFER_BIT);
     glFlush();
}

// glShade 
void mySDDisplay(void)
{
	const GLdouble Pi = 3.1415926536; 
	int i; 

	// glShadeModel: GL_FLAT, GL_SMOOTH(default) 
	glShadeModel(GL_FLAT); 
	glClear(GL_COLOR_BUFFER_BIT); 
	glBegin(GL_TRIANGLE_FAN); 
	glColor3f(1.0f, 1.0f, 1.0f); 
	glVertex2f(0.0f, 0.0f); 
	for(i = 0; i < 8; i++)
	{
		glColor3f(i & 0x04, i & 0x02, i & 0x01); 
		glVertex2f(cos(i * Pi/4), sin(i * Pi/4)); 
	}
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

     glutDisplayFunc(&mySDDisplay/*myCLDisplay*//*myDisplay*/);

     glutMainLoop();

     return 0;

}
