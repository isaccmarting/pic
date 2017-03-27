#include <windows.h>
#include <math.h>
#include <gl/glut.h>

#define WIDTH 400
#define HEIGHT 400

void myDisplay(void)
{
     glClear(GL_COLOR_BUFFER_BIT);

     glEnable(GL_BLEND);
     glBlendFunc(GL_ONE, GL_ZERO);
	 // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	 // glBlendFunc(GL_ONE, GL_ONE);

     glColor4f(1, 0, 0, 0.5);
     glRectf(-1, -1, 0.5, 0.5);
     glColor4f(0, 1, 0, 0.5);
     glRectf(-0.5, -0.5, 1, 1);

     glutSwapBuffers();
}

int main(int argc, char* argv[])
{
     glutInit(&argc, argv);
     glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
     glutInitWindowPosition(200, 200);
     glutInitWindowSize(WIDTH, HEIGHT);
     glutCreateWindow("OpenGL ´°¿Ú");
     glutDisplayFunc(&myDisplay);
     glutMainLoop();
     return 0;
}

