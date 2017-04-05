/*
author：fish1996
date:2016/03/24
*/

#define GLUT_DISABLE_ATEXIT_HACK    
#include "gl/glut.h"

float fTranslate; //平移因子
float fRotate; //旋转因子
float fScale = 1.0f; //缩放因子

//绘制正方体，它是由直线x = x1, x = x2, y = y1, y = y2, z = z1, z = z2 划分出的空间
void drawCube(GLfloat x1, GLfloat x2, GLfloat y1, GLfloat y2, GLfloat z1, GLfloat z2)
{
	int i, j;
	//指定六个面的四个顶点，每个顶点用3个坐标值表示
	GLfloat point[6][4][3] = {
		{ { x1,y1,z1 },{ x2,y1,z1 },{ x2,y2,z1 },{ x1,y2,z1 } },
		{ { x1,y1,z1 },{ x2,y1,z1 },{ x2,y1,z2 },{ x1,y1,z2 } },
		{ { x2,y1,z1 },{ x2,y2,z1 },{ x2,y2,z2 },{ x2,y1,z2 } },
		{ { x1,y1,z1 },{ x1,y2,z1 },{ x1,y2,z2 },{ x1,y1,z2 } },
		{ { x1,y2,z1 },{ x2,y2,z1 },{ x2,y2,z2 },{ x1,y2,z2 } },
		{ { x1,y1,z2 },{ x2,y1,z2 },{ x2,y2,z2 },{ x1,y2,z2 } }
	};
	//设置正方形绘制模式
	glBegin(GL_QUADS);
	for (i = 0; i < 6; i++) {
		for (j = 0; j < 4; j++) {
			glVertex3fv(point[i][j]);
		}
	}
	glEnd();
}

//绘制桌子
void drawTable()
{
	drawCube(0.0, 1.0, 0.0, 0.8, 0.6, 0.8);	//桌面	
	drawCube(0.1, 0.3, 0.1, 0.3, 0.0, 0.6); //四条腿
	drawCube(0.7, 0.9, 0.1, 0.3, 0.0, 0.6);
	drawCube(0.1, 0.3, 0.5, 0.7, 0.0, 0.6);
	drawCube(0.7, 0.9, 0.5, 0.7, 0.0, 0.6);
}

void reshape(int width, int height)
{
	if (height == 0)	
	{
		height = 1;	 //高度为0时，让高度为1
	}

	glViewport(0, 0, width, height);	//设置视窗大小

	glMatrixMode(GL_PROJECTION);	//设置矩阵模式为投影
	glLoadIdentity();			//初始化矩阵为单位矩阵
								
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);//设置投影方位

	glMatrixMode(GL_MODELVIEW);	  //设置矩阵模式为模型
	glLoadIdentity();	//初始化矩阵为单位矩阵
}

void idle()
{
	glutPostRedisplay();//调用当前绘制函数
}

void redraw()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//设置多边形绘制模式：正反面，线型
	glClear(GL_COLOR_BUFFER_BIT);//清除颜色缓冲
	glLoadIdentity();	//初始化矩阵为单位矩阵

	glPushMatrix(); //压入矩阵堆栈
	glTranslatef(-2.0f, 0.0f, -6.0f); //图形向左平移，同时向里平移
	glTranslatef(0.0f, fTranslate, 0.0f);	//y轴方向上平移
	drawTable();//画桌子
	glPopMatrix();//抛出矩阵堆栈

	glPushMatrix();//压入矩阵堆栈
	glTranslatef(0.5f, 0.0f, -6.0f); //旋转前向右平移，改变坐标轴，同时向里平移	
	glRotatef(fRotate, 0, 1.0f, 0);     //以y轴为坐标轴旋转
	glTranslatef(-0.5f, 0.0f, 0.0f); //旋转后向左平移，恢复位置
	drawTable();//画桌子
	glPopMatrix();//抛出矩阵堆栈

	glPushMatrix();//压入矩阵堆栈
	glTranslatef(2.0f, 0.4f, -6.0f); //图形向右，向里平移 + 缩放前向右，向上平移，改变缩放点 
	glScalef(fScale, fScale, fScale); //等比例缩放
	glTranslatef(-0.5f, -0.4f, 0.0f); //缩放后向左，向下平移，恢复位置
	drawTable();//画桌子
	glPopMatrix();//抛出矩阵堆栈

	fTranslate += 0.002f; //更新平移因子
	fRotate += 0.4f; //更新旋转因子
	fScale -= 0.002f; //更新缩放因子

	if (fTranslate > 0.5f) fTranslate = 0.0f; //移到一定位置从头开始移
	if (fScale < 0.6f)fScale = 1.0f; //缩放到一定程度恢复原状

	glutSwapBuffers(); //交换缓冲区
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);//对glut的初始化
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);//初始化显示模式:RGB颜色模型，双缓冲 
	glutInitWindowSize(640, 480);//设置窗口大小  
	glutCreateWindow("Exercise2");//设置窗口标题 

	glutDisplayFunc(redraw);//注册绘制回调函数  
	glutReshapeFunc(reshape);//注册重绘回调函数  
	glutIdleFunc(idle);//注册全局回调函数：空闲时调用

	glutMainLoop();// glut事件处理循环  

	return 0;
}

