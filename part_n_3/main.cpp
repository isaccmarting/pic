#include <stdio.h>
#include "Glee.h"
#include <GL/glut.h>

static GLfloat vertex_list[][3] = {
     -0.5f, -0.5f, -0.5f,
      0.5f, -0.5f, -0.5f,
     -0.5f,   0.5f, -0.5f,
      0.5f,   0.5f, -0.5f,
     -0.5f, -0.5f,   0.5f,
      0.5f, -0.5f,   0.5f,
     -0.5f,   0.5f,   0.5f,
      0.5f,   0.5f,   0.5f,
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
	glClear(GL_COLOR_BUFFER_BIT); 
	glColor3f(1.0f, 0.0f, 0.0f); 

	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
	if( GLEE_ARB_vertex_buffer_object ) {
		 // ���֧�ֶ��㻺��������
		static int isFirstCall = 1;
		static GLuint vertex_buffer;
		static GLuint index_buffer;
		printf("GLEE_ARB_vertex_buffer_object is supported!\n"); 
		if( isFirstCall ) {
			 // ��һ�ε���ʱ����ʼ��������
			 isFirstCall = 0;

			 // ����һ����������������������ָ��������
			 glGenBuffersARB(1, &vertex_buffer);
			 glBindBufferARB(GL_ARRAY_BUFFER_ARB, vertex_buffer);
			 glBufferDataARB(GL_ARRAY_BUFFER_ARB,
				sizeof(vertex_list), vertex_list, GL_STATIC_DRAW_ARB);

			 // ����һ���������������������ָ��������
			 glGenBuffersARB(1, &index_buffer);
			 glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, index_buffer);
			 glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER_ARB,
				sizeof(index_list), index_list, GL_STATIC_DRAW_ARB);
		 }
		 glBindBufferARB(GL_ARRAY_BUFFER_ARB, vertex_buffer);
		 glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, index_buffer);

		 // ʵ��ʹ��ʱ�붥������ǳ����ƣ�ֻ����ָ������ʱ����ָ��ʵ�ʵ����飬��Ϊָ��NULL����
		 glEnableClientState(GL_VERTEX_ARRAY);
		 glVertexPointer(3, GL_FLOAT, 0, NULL);
		 glDrawElements(GL_QUADS, 24, GL_UNSIGNED_INT, NULL);
	} else {
		 printf("GLEE_ARB_vertex_buffer_object is not supported!\n"); 
		 // ��֧�ֶ��㻺��������
		 // ʹ�ö�������
		 glEnableClientState(GL_VERTEX_ARRAY);
		 glVertexPointer(3, GL_FLOAT, 0, vertex_list);
		 glDrawElements(GL_QUADS, 24, GL_UNSIGNED_INT, index_list);
	}

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
