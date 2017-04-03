#include <GL/glut.h>

// 将立方体的八个顶点保存到一个数组里面
static const GLfloat vertex_list[][3] = {
     -0.5f, -0.5f, -0.5f,
      0.5f, -0.5f, -0.5f,
     -0.5f,   0.5f, -0.5f,
      0.5f,   0.5f, -0.5f,
     -0.5f, -0.5f,   0.5f,
      0.5f, -0.5f,   0.5f,
     -0.5f,   0.5f,   0.5f,
      0.5f,   0.5f,   0.5f,
};

// 将要使用的顶点的序号保存到一个数组里面
static const GLint index_list[][4] = {
     0, 2, 3, 1,
     0, 4, 6, 2,
     0, 1, 5, 4,
     4, 5, 7, 6,
     1, 3, 7, 5,
     2, 6, 7, 3,
};

void myDisplay(void)

{

	int i, j;

	glClear(GL_COLOR_BUFFER_BIT); 
	glColor3f(1.0f, 0.0f, 0.0f); 

	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// 绘制的时候代码很简单
	glBegin(GL_QUADS);
	for(i=0; i<6; ++i)          // 有六个面，循环六次
		for(j=0; j<4; ++j)      // 每个面有四个顶点，循环四次
			 glVertex3fv(vertex_list[index_list[i][j]]);
	glEnd();

	glutSwapBuffers(); 

}

int main(int argc, char *argv[])

{

     glutInit(&argc, argv);

     glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

     glutInitWindowPosition(100, 100);

     glutInitWindowSize(400, 400);

     glutCreateWindow("OpenGL程序");

     glutDisplayFunc(&myDisplay);

     glutMainLoop();

     return 0;

}
