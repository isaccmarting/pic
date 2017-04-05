#include <windows.h>
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

GLfloat left_y = 0; 
GLfloat middle_rot_angle = 0.0f; 
GLfloat right_scale = 1.0f; 

// GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3, GLfloat v4, GLfloat v5, GLfloat v6, GLfloat v7 
// (x, y) (-1,  1) (-1, -1) ( 1, -1) ( 1,  1)
// z =  1 v4        v5      v6       v7
// z = -1 v0        v1      v2       v3
void drawCube(GLfloat vertex_list[])
{	
//	glFrontFace(GL_CCW); 
//	glCullFace(GL_BACK); 
//	glEnable(GL_CULL_FACE); 
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
	gluPerspective(75.0f, (GLfloat)width / height, 0.1f, 100.0f/*100.0f*/); 

	glMatrixMode(GL_MODELVIEW); 
	glLoadIdentity(); 
	gluLookAt(0.0f, 0.0f, 15.0f, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0f); 

	return ; 
}

void drawTable()
{
	// ×ÀÃæ
	GLfloat vertex_list0[24] = {
		-2.5f,  2.0f, 0.0f, 
		-2.5f, -2.0f, 0.0f, 
		 2.5f, -2.0f, 0.0f, 
         2.5f,  2.0f, 0.0f, 
		-2.5f,  2.0f, 1.0f, 
		-2.5f, -2.0f, 1.0f, 
		 2.5f, -2.0f, 1.0f, 
         2.5f,  2.0f, 1.0f, 
	}; 
	// ×À½Ç
    GLfloat vertex_list1[24] = {
		-0.4f,  0.4f, -3.0f, 
		-0.4f, -0.4f, -3.0f, 
		 0.4f, -0.4f, -3.0f, 
         0.4f,  0.4f, -3.0f, 
		-0.4f,  0.4f,  0.0f, 
		-0.4f, -0.4f,  0.0f,
		 0.4f, -0.4f,  0.0f,
         0.4f,  0.4f,  0.0f,
	}; 
	
	glPushMatrix(); 
	drawCube(vertex_list0); 
	glPopMatrix(); 
	glPushMatrix(); 
	glTranslatef(-1.5f, 1.0f, 0.0f); 
	drawCube(vertex_list1); 
	glPopMatrix(); 
	glPushMatrix(); 
	glTranslatef(-1.5f, -1.0f, 0.0f); 
	drawCube(vertex_list1); 
	glPopMatrix(); 
	glPushMatrix(); 
	glTranslatef(1.5f, -1.0f, 0.0f); 
	drawCube(vertex_list1); 
	glPopMatrix(); 
	glPushMatrix(); 
	glTranslatef(1.5f, 1.0f, 0.0f); 
	drawCube(vertex_list1); 
	glPopMatrix(); 
	return ; 
}

void display()
{	
    glClear(GL_COLOR_BUFFER_BIT); 
	glColor3f(1.0, 1.0f, 1.0f); 
	
	glPushMatrix(); 
	glTranslatef(-7.5f, 0.0f, 0.0f); 
	glTranslatef(0.0f, left_y, 0.0f); 
	drawTable(); 
    glPopMatrix(); 

	glPushMatrix(); 
	glRotatef(middle_rot_angle, 0.0f, 1.0f, 0.0f); 
	drawTable(); 
    glPopMatrix(); 

	glPushMatrix(); 
	glTranslatef(7.5f, 0.0f, 0.0f); 
	glScalef(right_scale, right_scale, right_scale); 
	drawTable(); 
    glPopMatrix(); 

    left_y += 0.002f; 
	if(left_y >= 1.6f) left_y = 0.0f; 
	middle_rot_angle += 0.4f; 
	if(middle_rot_angle >= 360.0f) middle_rot_angle = 0.0f; 
	right_scale -= 0.001f; 
	if(right_scale <= 0.5f) right_scale = 1.0f; 

	glutSwapBuffers(); 
	return ; 
}

void idle()
{
	Sleep(1); 
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
