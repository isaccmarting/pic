#include <GL/glut.h>

typedef struct __point__ {
     GLfloat position[3];
    int      id;
} Point;

Point vertex_list[] = {
     -0.5f, -0.5f, -0.5f, 1,
      0.5f, -0.5f, -0.5f, 2,
     -0.5f,   0.5f, -0.5f, 3,
      0.5f,   0.5f, -0.5f, 4,
     -0.5f, -0.5f,   0.5f, 5,
      0.5f, -0.5f,   0.5f, 6,
     -0.5f,   0.5f,   0.5f, 7,
      0.5f,   0.5f,   0.5f, 8,
};

static GLint index_list[][4] = {
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
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, sizeof(Point), vertex_list);  // Number; Type; Interval; Array; 
	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_INT, index_list); // Mode; Number; Type; Array; 

    /* 混合顶点数组 */
	/*
	GLfloat arr_c3f_v3f[] = {
		 1, 0, 0, 0, 1, 0,
		 0, 1, 0, 1, 0, 0,
		 0, 0, 1, -1, 0, 0,
	};
	GLuint index_list[] = {0, 1, 2};
	glInterleavedArrays(GL_C3F_V3F, 0, arr_c3f_v3f);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, index_list);
	*/

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
