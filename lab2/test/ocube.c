/*
author��fish1996
date:2016/03/24
*/

#define GLUT_DISABLE_ATEXIT_HACK    
#include "gl/glut.h"

float fTranslate; //ƽ������
float fRotate; //��ת����
float fScale = 1.0f; //��������

//���������壬������ֱ��x = x1, x = x2, y = y1, y = y2, z = z1, z = z2 ���ֳ��Ŀռ�
void drawCube(GLfloat x1, GLfloat x2, GLfloat y1, GLfloat y2, GLfloat z1, GLfloat z2)
{
	int i, j;
	//ָ����������ĸ����㣬ÿ��������3������ֵ��ʾ
	GLfloat point[6][4][3] = {
		{ { x1,y1,z1 },{ x2,y1,z1 },{ x2,y2,z1 },{ x1,y2,z1 } },
		{ { x1,y1,z1 },{ x2,y1,z1 },{ x2,y1,z2 },{ x1,y1,z2 } },
		{ { x2,y1,z1 },{ x2,y2,z1 },{ x2,y2,z2 },{ x2,y1,z2 } },
		{ { x1,y1,z1 },{ x1,y2,z1 },{ x1,y2,z2 },{ x1,y1,z2 } },
		{ { x1,y2,z1 },{ x2,y2,z1 },{ x2,y2,z2 },{ x1,y2,z2 } },
		{ { x1,y1,z2 },{ x2,y1,z2 },{ x2,y2,z2 },{ x1,y2,z2 } }
	};
	//���������λ���ģʽ
	glBegin(GL_QUADS);
	for (i = 0; i < 6; i++) {
		for (j = 0; j < 4; j++) {
			glVertex3fv(point[i][j]);
		}
	}
	glEnd();
}

//��������
void drawTable()
{
	drawCube(0.0, 1.0, 0.0, 0.8, 0.6, 0.8);	//����	
	drawCube(0.1, 0.3, 0.1, 0.3, 0.0, 0.6); //������
	drawCube(0.7, 0.9, 0.1, 0.3, 0.0, 0.6);
	drawCube(0.1, 0.3, 0.5, 0.7, 0.0, 0.6);
	drawCube(0.7, 0.9, 0.5, 0.7, 0.0, 0.6);
}

void reshape(int width, int height)
{
	if (height == 0)	
	{
		height = 1;	 //�߶�Ϊ0ʱ���ø߶�Ϊ1
	}

	glViewport(0, 0, width, height);	//�����Ӵ���С

	glMatrixMode(GL_PROJECTION);	//���þ���ģʽΪͶӰ
	glLoadIdentity();			//��ʼ������Ϊ��λ����
								
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);//����ͶӰ��λ

	glMatrixMode(GL_MODELVIEW);	  //���þ���ģʽΪģ��
	glLoadIdentity();	//��ʼ������Ϊ��λ����
}

void idle()
{
	glutPostRedisplay();//���õ�ǰ���ƺ���
}

void redraw()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//���ö���λ���ģʽ�������棬����
	glClear(GL_COLOR_BUFFER_BIT);//�����ɫ����
	glLoadIdentity();	//��ʼ������Ϊ��λ����

	glPushMatrix(); //ѹ������ջ
	glTranslatef(-2.0f, 0.0f, -6.0f); //ͼ������ƽ�ƣ�ͬʱ����ƽ��
	glTranslatef(0.0f, fTranslate, 0.0f);	//y�᷽����ƽ��
	drawTable();//������
	glPopMatrix();//�׳������ջ

	glPushMatrix();//ѹ������ջ
	glTranslatef(0.5f, 0.0f, -6.0f); //��תǰ����ƽ�ƣ��ı������ᣬͬʱ����ƽ��	
	glRotatef(fRotate, 0, 1.0f, 0);     //��y��Ϊ��������ת
	glTranslatef(-0.5f, 0.0f, 0.0f); //��ת������ƽ�ƣ��ָ�λ��
	drawTable();//������
	glPopMatrix();//�׳������ջ

	glPushMatrix();//ѹ������ջ
	glTranslatef(2.0f, 0.4f, -6.0f); //ͼ�����ң�����ƽ�� + ����ǰ���ң�����ƽ�ƣ��ı����ŵ� 
	glScalef(fScale, fScale, fScale); //�ȱ�������
	glTranslatef(-0.5f, -0.4f, 0.0f); //���ź���������ƽ�ƣ��ָ�λ��
	drawTable();//������
	glPopMatrix();//�׳������ջ

	fTranslate += 0.002f; //����ƽ������
	fRotate += 0.4f; //������ת����
	fScale -= 0.002f; //������������

	if (fTranslate > 0.5f) fTranslate = 0.0f; //�Ƶ�һ��λ�ô�ͷ��ʼ��
	if (fScale < 0.6f)fScale = 1.0f; //���ŵ�һ���̶Ȼָ�ԭ״

	glutSwapBuffers(); //����������
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);//��glut�ĳ�ʼ��
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);//��ʼ����ʾģʽ:RGB��ɫģ�ͣ�˫���� 
	glutInitWindowSize(640, 480);//���ô��ڴ�С  
	glutCreateWindow("Exercise2");//���ô��ڱ��� 

	glutDisplayFunc(redraw);//ע����ƻص�����  
	glutReshapeFunc(reshape);//ע���ػ�ص�����  
	glutIdleFunc(idle);//ע��ȫ�ֻص�����������ʱ����

	glutMainLoop();// glut�¼�����ѭ��  

	return 0;
}

