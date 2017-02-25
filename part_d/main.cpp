// !!! ld: -lglu32 
#include <GL/glut.h>

// ̫�������������
// ����ÿ���¶���30��
// һ��12���£�����360��
void myDisplay(void)
{
     static int day = 200; // day�ı仯����0��359

	 // ??? glEnable(GL_DEPTH_TEST);
     glClear(GL_COLOR_BUFFER_BIT/* | GL_DEPTH_BUFFER_BIT*/);

     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();
     gluPerspective(75, 1, 1, 400000000);
     glMatrixMode(GL_MODELVIEW);
     glLoadIdentity();
     gluLookAt(0, -200000000, 200000000, 0, 0, 0, 0, 0, 1);

     // ���ƺ�ɫ�ġ�̫����
     glColor3f(1.0f, 0.0f, 0.0f);
     glutSolidSphere(69600000, 20, 20);
     // ������ɫ�ġ�����
     glColor3f(0.0f, 0.0f, 1.0f);
     glRotatef(day/360.0*360.0, 0.0f, 0.0f, -1.0f);
     glTranslatef(150000000, 0.0f, 0.0f);
     glutSolidSphere(15945000, 20, 20);
     // ���ƻ�ɫ�ġ�������
     glColor3f(1.0f, 1.0f, 0.0f);
     glRotatef(day/30.0*360.0 - day/360.0*360.0, 0.0f, 0.0f, -1.0f);
     glTranslatef(38000000, 0.0f, 0.0f);
     glutSolidSphere(4345000, 20, 20);

	 glFlush();

}

int main(int argc, char *argv[])

{

     glutInit(&argc, argv);

     glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);

     glutInitWindowPosition(100, 100);

     glutInitWindowSize(400, 400);

     glutCreateWindow("��һ��OpenGL����");

     glutDisplayFunc(&myDisplay);

     glutMainLoop();

     return 0;

}