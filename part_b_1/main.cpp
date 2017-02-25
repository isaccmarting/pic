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

     glPolygonMode(GL_FRONT, GL_FILL); // 设置正面为填充模式

     glPolygonMode(GL_BACK, GL_LINE);   // 设置反面为线形模式

     // CCW, CW
	 glFrontFace(GL_CW/*GL_CCW*/);               // 设置逆时针方向为正面

     glBegin(GL_POLYGON);               // 按逆时针绘制一个正方形，在左下方

         glVertex2f(-0.5f, -0.5f);

         glVertex2f(0.0f, -0.5f);

         glVertex2f(0.0f, 0.0f);

         glVertex2f(-0.5f, 0.0f);

     glEnd();

     glBegin(GL_POLYGON);               // 按顺时针绘制一个正方形，在右上方

         glVertex2f(0.0f, 0.0f);

         glVertex2f(0.0f, 0.5f);

         glVertex2f(0.5f, 0.5f);

         glVertex2f(0.5f, 0.0f);

     glEnd();

     glFlush();

}

/* 
 * 使用glEnable(GL_CULL_FACE);来启动剔除功能（使用glDisable(GL_CULL_FACE)可以关闭之）
 *
 * glCullFace的参数可以是GL_FRONT，GL_BACK或者GL_FRONT_AND_BACK，分别表示剔除正面、
 * 剔除反面、剔除正反两面的多边形。
 *
 */

int main(int argc, char *argv[])

{

     glutInit(&argc, argv);

     glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);

     glutInitWindowPosition(100, 100);

     glutInitWindowSize(400, 400);

     glutCreateWindow("第一个OpenGL程序");

     glutDisplayFunc(&myPMDisplay/*myDisplay*/);

     glutMainLoop();

     return 0;

}
