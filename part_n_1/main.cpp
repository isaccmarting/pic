#include <GL/glut.h>

// ��������İ˸����㱣�浽һ����������
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

// ��Ҫʹ�õĶ������ű��浽һ����������
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

	// ���Ƶ�ʱ�����ܼ�
	glBegin(GL_QUADS);
	for(i=0; i<6; ++i)          // �������棬ѭ������
		for(j=0; j<4; ++j)      // ÿ�������ĸ����㣬ѭ���Ĵ�
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

     glutCreateWindow("OpenGL����");

     glutDisplayFunc(&myDisplay);

     glutMainLoop();

     return 0;

}
