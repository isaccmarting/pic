#include <stdio.h>
#include <GL/glut.h>

const GLuint index_list[] = {
	3, 2, 1, 0, // low 
	5, 4, 0, 1, // left 
	6, 5, 1, 2, // front 
	7, 6, 2, 3, // right 
	4, 7, 3, 0, // back 
	4, 5, 6, 7  // up 
}; 

// GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3, GLfloat v4, GLfloat v5, GLfloat v6, GLfloat v7 
// (x, y) (-1,  1) (-1, -1) ( 1, -1) ( 1,  1)
// z =  1 v4        v5      v6       v7
// z = -1 v0        v1      v2       v3
void drawCube(GLfloat vertex_list[])
{	
	glFrontFace(GL_CCW); 
	glCullFace(GL_BACK); 
	glEnable(GL_CULL_FACE); 
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); 

	glEnableClientState(GL_VERTEX_ARRAY); 
	glVertexPointer(3, GL_FLOAT, 0, vertex_list); 
	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_INT, index_list); 
	
	return ; 
}

void reshape(int width, int height)
{
	if(height == 0)
		height = 1; 

	glViewport(0, 0, width, height); 
	
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity(); 
	gluPerspective(45.0f, (GLfloat)width / height, 0.1f, 33.0f/*100.0f*/); 

	glMatrixMode(GL_MODELVIEW); 
	glLoadIdentity(); 
	gluLookAt(5.0f, 5.0f, 5.0f, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0f); 

	return ; 
}

void display()
{
	GLfloat vertex_list[24] = {
		-2.5f,  2.0f, -0.5f, 
		-2.5f, -2.0f, -0.5f, 
		 2.5f, -2.0f, -0.5f, 
         2.5f,  2.0f, -0.5f, 
		-2.5f,  2.0f,  0.5f, 
		-2.5f, -2.0f,  0.5f, 
		 2.5f, -2.0f,  0.5f, 
         2.5f,  2.0f,  0.5f, 
//        -0.5f,  0.5f, -0.5f, 
//		-0.5f, -0.5f, -0.5f, 
//		 0.5f, -0.5f, -0.5f, 
//         0.5f,  0.5f, -0.5f, 
//		-0.5f,  0.5f,  0.5f, 
//		-0.5f, -0.5f,  0.5f, 
//		 0.5f, -0.5f,  0.5f, 
//         0.5f,  0.5f,  0.5f, 
	}; 
	
	glClear(GL_COLOR_BUFFER_BIT); 

	glColor3f(1.0, 0.0f, 0.0f); 
	drawCube(vertex_list); 
	
	glutSwapBuffers(); 
	return ; 
}

void idle()
{
	glutPostRedisplay(); 
	return ; 
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv); 
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); 
	glutInitWindowPosition(10, 10); 
	glutInitWindowSize(400, 400); 
	glutCreateWindow("Draw Cube"); 

	glutDisplayFunc(display); 
	glutReshapeFunc(reshape); 
	glutIdleFunc(idle); 

	glutMainLoop(); 
	
	return 0; 
}
