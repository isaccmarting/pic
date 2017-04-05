#include <windows.h>
#include <stdio.h>
#include <GL/glut.h>

// 顶点序号数组，是画六个面的顶点序号
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

// 用顶点数组画一个长方体
// GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3, GLfloat v4, GLfloat v5, GLfloat v6, GLfloat v7 
// (x, y) (-1,  1) (-1, -1) ( 1, -1) ( 1,  1)
// z =  1 v4       v5       v6       v7
// z = -1 v0       v1       v2       v3
void drawCube(GLfloat vertex_list[])
{	
	// 画出长方体的边
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); 

	// 使用顶点数组
	glEnableClientState(GL_VERTEX_ARRAY); 
	glVertexPointer(3, GL_FLOAT, 0, vertex_list); 
	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_INT, index_list); 
	
	return ; 
}

void reshape(int width, int height)
{
	// Prevent A Divide By Zero By
	if(height == 0)
		height = 1; 

	// Reset The Current Viewport
	glViewport(0, 0, width, height); 
	
	// Select The Projection Matrix
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity(); 
	// Calculate The Aspect Ratio Of The Window
	gluPerspective(75.0f, (GLfloat)width / height, 0.1f, 100.0f/*100.0f*/); 

	// Select The Modelview Matrix
	glMatrixMode(GL_MODELVIEW); 
	glLoadIdentity(); 
	gluLookAt(0.0f, 0.0f, 15.0f, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0f); 

	return ; 
}

// 画出桌子
void drawTable()
{
	// 桌面
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
	// 桌角
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
	
	// 画出桌面
	glPushMatrix(); 
	drawCube(vertex_list0); 
	glPopMatrix(); 
	// 画出左上的桌角
	glPushMatrix(); 
	glTranslatef(-1.5f, 1.0f, 0.0f); 
	drawCube(vertex_list1); 
	glPopMatrix(); 
	// 画出左下的桌角
	glPushMatrix(); 
	glTranslatef(-1.5f, -1.0f, 0.0f); 
	drawCube(vertex_list1); 
	glPopMatrix(); 
	// 画出右下的桌角
	glPushMatrix(); 
	glTranslatef(1.5f, -1.0f, 0.0f); 
	drawCube(vertex_list1); 
	glPopMatrix(); 
	// 画出右上的桌角
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
	
	// 画出左边向上移动的桌子
	glPushMatrix(); 
	glTranslatef(-7.5f, 0.0f, 0.0f); 
	glTranslatef(0.0f, left_y, 0.0f); 
	drawTable(); 
    glPopMatrix(); 

	// 画出中间旋转的桌子
	glPushMatrix(); 
	glRotatef(middle_rot_angle, 0.0f, 1.0f, 0.0f); 
	drawTable(); 
    glPopMatrix(); 

	// 画出右边缩小的桌子
	glPushMatrix(); 
	glTranslatef(7.5f, 0.0f, 0.0f); 
	glScalef(right_scale, right_scale, right_scale); 
	drawTable(); 
    glPopMatrix(); 

    // 桌子的位置或大小数据改变
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
