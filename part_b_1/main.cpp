// !!! math.h is placed before <GL/glut.h> 
#include <math.h>
#include <GL/glut.h>

void myDisplay(void)

{

     glClear(GL_COLOR_BUFFER_BIT);

     /*glPointSize(5.0f);

     glBegin(GL_POINTS);

         glVertex2f(0.0f, 0.0f);

         glVertex2f(0.5f, 0.5f);*/
	 
	 /*glLineWidth(5.0f); 
	 glBegin(GL_LINES); 
	     glVertex2f(0.0f, 0.0f); 
		 glVertex2f(0.5f, 0.5f); */
	 
	 glEnable(GL_LINE_STIPPLE); 
	 glLineStipple(2, 0x0F0F); 
	 glLineWidth(10.0f); 
	 glBegin(GL_LINE); 
	     glVertex2f(0.0f, 0.0f); 
		 glVertex2f(0.5f, 0.5f); 

     glEnd();

     glFlush();

}

// Polygon Mode
void myPMDisplay(void)

{

     glClear(GL_COLOR_BUFFER_BIT);

     glPolygonMode(GL_FRONT, GL_FILL); // ��������Ϊ���ģʽ

     glPolygonMode(GL_BACK, GL_LINE);   // ���÷���Ϊ����ģʽ

     // CCW, CW
	 glFrontFace(GL_CW/*GL_CCW*/);               // ������ʱ�뷽��Ϊ����

     glBegin(GL_POLYGON);               // ����ʱ�����һ�������Σ������·�

         glVertex2f(-0.5f, -0.5f);

         glVertex2f(0.0f, -0.5f);

         glVertex2f(0.0f, 0.0f);

         glVertex2f(-0.5f, 0.0f);

     glEnd();

     glBegin(GL_POLYGON);               // ��˳ʱ�����һ�������Σ������Ϸ�

         glVertex2f(0.0f, 0.0f);

         glVertex2f(0.0f, 0.5f);

         glVertex2f(0.5f, 0.5f);

         glVertex2f(0.5f, 0.0f);

     glEnd();

     glFlush();

}

/* 
 * ʹ��glEnable(GL_CULL_FACE);�������޳����ܣ�ʹ��glDisable(GL_CULL_FACE)���Թر�֮��
 *
 * glCullFace�Ĳ���������GL_FRONT��GL_BACK����GL_FRONT_AND_BACK���ֱ��ʾ�޳����桢
 * �޳����桢�޳���������Ķ���Ρ�
 *
 */

int main(int argc, char *argv[])

{

     glutInit(&argc, argv);

     glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);

     glutInitWindowPosition(100, 100);

     glutInitWindowSize(400, 400);

     glutCreateWindow("��һ��OpenGL����");

     glutDisplayFunc(&myPMDisplay/*myDisplay*/);

     glutMainLoop();

     return 0;

}
