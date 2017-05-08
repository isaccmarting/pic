#include <stdio.h>
#include <string.h>
#include <GL/glut.h>

#include "stanford_bunny.h"

// �۲���λ��
GLfloat eye[] = {0, 4, 6}; 
// �۲����ĵ�����
GLfloat center[] = {0, 0, 0}; 
// ÿ���ӵ��ƶ��ľ���
GLfloat fDistance = 0.2f; 

// �Ƿ���ת
bool bAnim = false; 
// ����ת�ĽǶ�
GLfloat fRotate = 0; 

// �Ƿ�����ʾ�б�
bool bDrawList = false; 
GLint tableList, rabbitList; 

// �����Ƿ���ת
bool bRabbitAnim = false; 
// ��������ת�ĽǶ�
GLfloat fRabbitRotate = 0; 

// ���ӵ�����
GLint rabbitNum = 1; 
// ���ӵĿ��
GLfloat tableWidth = 6.0f; 

// ����֡��
void getFPS()
{
	static int frame = 0, time, timebase = 0;
	static char buffer[256];

	char mode[64];
	if (bDrawList)
		strcpy(mode, "display list");
	else
		strcpy(mode, "naive");

	frame++;
	time=glutGet(GLUT_ELAPSED_TIME);
	if (time - timebase > 1000) {
		sprintf(buffer,"FPS:%4.2f %s",
			frame*1000.0/(time-timebase), mode);
		timebase = time;		
		frame = 0;
	}

	char *c;
	glDisable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);  // ѡ��ͶӰ����
	glPushMatrix();               // ����ԭ����
	glLoadIdentity();             // װ�뵥λ����
	glOrtho(0,480,0,480,-1,1);    // λ����ͶӰ
	glMatrixMode(GL_MODELVIEW);   // ѡ��Modelview����
	glPushMatrix();               // ����ԭ����
	glLoadIdentity();             // װ�뵥λ����
	glRasterPos2f(10,10);
	for (c=buffer; *c != '\0'; c++) {		
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
	}
	glMatrixMode(GL_PROJECTION);  // ѡ��ͶӰ����
	glPopMatrix();                // ����Ϊԭ�������
	glMatrixMode(GL_MODELVIEW);   // ѡ��Modelview����
	glPopMatrix();                // ����Ϊԭ�������
	glEnable(GL_DEPTH_TEST);	
}

// ��������
// ��ʾ�б��ڲ��ܴ��붯̬����
// ����Ϊ����ʾ�б������������ӵĿ�ȣ��������Ҫ������ʾ�б���
void DrawTable()
{
	// ���ĸ�����
	glPushMatrix(); 
	// glTranslatef(1.5f, 1.5f, 1.0f); 
	glTranslatef(3.0f, 0.5f, /*tableWidth/2-0.5f*/2.5f); 
	// glScalef(1.0f, 3.0f, 1.0f); 
	glScalef(0.5f, 6.0f, 0.5f); 
	glutSolidCube(1.0f); 
	glPopMatrix(); 

	glPushMatrix(); 
	// glTranslatef(-1.5f, 1.5f, 1.0f); 
	glTranslatef(-3.0f, 0.5f, /*tableWidth/2-0.5f*/2.5f); 
	// glScalef(1.0f, 3.0f, 1.0f); 
	glScalef(0.5f, 6.0f, 0.5f); 
	glutSolidCube(1.0f); 
	glPopMatrix(); 

	glPushMatrix(); 
	// glTranslatef(-1.5f, 1.5f, -1.0f); 
	glTranslatef(-3.0f, 0.5f, -(/*tableWidth/2-0.5f*/2.5f)); 
	// glScalef(1.0f, 3.0f, 1.0f); 
	glScalef(0.5f, 6.0f, 0.5f); 
	glutSolidCube(1.0f); 
	glPopMatrix(); 

	glPushMatrix(); 
	// glTranslatef(1.5f, 1.5f, -1.0f); 
	glTranslatef(3.0f, 0.5f, -(/*tableWidth/2-0.5f*/2.5f)); 
	// glScalef(1.0f, 3.0f, 1.0f); 
	glScalef(0.5f, 6.0f, 0.5f); 
	glutSolidCube(1.0f); 
	glPopMatrix(); 
}

// ����������
void DrawScene()
{
	int i; 
	
	// ��������
	glPushMatrix(); 
	// ��һ�����ӵ�λ�ã����������ȶ�̬����
	glTranslatef(3.75f - 1.1f, 4.5f, tableWidth/2-0.7f/*2.3f*/); 
	glScalef(2.0f, 2.0f, 2.0f); 
	for(i = 0; i < rabbitNum; i++)
	{
		glPushMatrix(); 
		glRotatef(fRabbitRotate, 0, 1, 0); 
		DrawBunny(); 
		glPopMatrix(); 
		// ��һ�����ӵ�λ��
		glTranslatef(-0.9f, 0.0f, 0.0f); 
		// һ����������ỻ��
		if((i + 1) % 4 == 0) glTranslatef(3.6f, 0.0f, -0.75f); 
	}
	glPopMatrix(); 

	// �����ӵ��ĸ���
	DrawTable(); 
	// ������
	glPushMatrix(); 
	glTranslatef(0.0f, 3.5f, 0.0f); 
	//glScalef(5.0f, 1.0f, 4.0f); 
	glScalef(7.5f, 0.5f, tableWidth); 
	glutSolidCube(1.0f); 
	glPopMatrix(); 
}

// ���ɳ�����Ҫ��ȫ����ʾ�б�
void GenSceneList()
{
	tableList = glGenLists(2); 
	rabbitList = tableList + 1; 

	// ���ӵ���ʾ�б�
	glNewList(tableList, GL_COMPILE); 
	DrawTable(); 
	glEndList(); 

	// ���ӵ���ʾ�б�
	glNewList(rabbitList, GL_COMPILE); 
	DrawBunny(); 
	glEndList(); 

	return ; 
}

// ����ʾ�б�����
void Draw_Scene_List()
{
	int i; 
	
	glPushMatrix(); 
	// glTranslatef(2.2f, 4.5f, 1.8f); 
	// ��һ��ͼ���ӵ�λ�ã��������ӿ�ȶ�̬����
	glTranslatef(3.75f - 1.1f, 4.5f, tableWidth/2-0.7f/*2.3f*/); 
	glScalef(2.0f, 2.0f, 2.0f); 
	for(i = 0; i < rabbitNum; i++)
	{
		glCallList(rabbitList); 
		// glTranslatef(-0.75f, 0.0f, 0.0f); 
		// ��һ�����ӵ�λ��
		glTranslatef(-0.9f, 0.0f, 0.0f); 
		// һ����������ỻ��
		if((i + 1) % 4 == 0) glTranslatef(3.6f, 0.0f, -0.75f); // glTranslatef(3.0f, 0.0f, -0.6f); 
	}
	glPopMatrix(); 
	
	// �����ӵ��ĸ��� 
	glCallList(tableList); 
	// ������ 
	glPushMatrix(); 
	glTranslatef(0.0f, 3.5f, 0.0f); 
	//glScalef(5.0f, 1.0f, 4.0f); 
	glScalef(7.5f, 0.5f, tableWidth); 
	glutSolidCube(1.0f); 
	glPopMatrix(); 
}

// �������ڴ�Сʱ���������ӿڵ�
void reshape(int width, int height)
{
	if(height == 0) height = 1; 

	glViewport(0, 0, width, height); 

	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity(); 
	GLfloat whRatio = (GLfloat) width / height; 
	gluPerspective(45, whRatio, 1, 1000); 

	glMatrixMode(GL_MODELVIEW); 
}

// ����ʱ���õĺ���
void idle()
{
	glutPostRedisplay(); 
}

// ���̰��������� 
void key(unsigned char k, int x, int y)
{
	switch(k)
	{
		case 27: // �˳� 
		case 'q': {exit(0); break; }
		case 'a': // �������� 
		{
			eye[0] += fDistance; 
			center[0] += fDistance; 
			break; 
		}
		case 'd': // �������� 
		{
			eye[0] -= fDistance; 
			center[0] -= fDistance; 
			break; 
		}
		case 'w': // �������� 
		{
			eye[1] -= fDistance; 
			center[1] -= fDistance; 
			break; 
		}
		case 's': // �������� 
		{
			eye[1] += fDistance; 
			center[1] += fDistance; 
			break; 
		}
		case 'z': // �ӵ㿿������ 
		{
			eye[2] *= 0.95; 
			break; 
		}
		case 'c': // �ӵ�Զ������ 
		{
			eye[2] *= 1.05; 
			break; 
		}
		case 'l': // �Ƿ�ʹ����ʾ�б�
		{
			bDrawList = !bDrawList; 
			break; 
		}
		case ' ': // �Ƿ���ת 
		{
			bAnim = !bAnim; 
			break; 
		}
		case 'i': // ������������ 
		{
			// if(rabbitNum < 16) rabbitNum++; 
			// ��������������16����Ҫ����ʱ�����ӿ������ 
			if(rabbitNum >= 16 && rabbitNum % 4 == 0) tableWidth += 1.5f; 
			rabbitNum++; 
			break; 
		}
		case 'k': // ������������ 
		{
			if(rabbitNum > 1) rabbitNum--; 
			// ��������������16����Ҫ����ʱ�����ӿ�ȼ��� 
			if(rabbitNum >= 16 && rabbitNum % 4 == 0) tableWidth -= 1.5f; 
			break; 
		}
		default: break; 
	}
}

// ��갴��������
void mouse(int button, int state, int x, int y)
{
	switch(button)
	{
		case GLUT_LEFT_BUTTON: {   // ���
			if(state == GLUT_DOWN) // ����
				bRabbitAnim = true; 
			break; 
		}
		case GLUT_MIDDLE_BUTTON: {
			break; 
		}
		case GLUT_RIGHT_BUTTON: {  // �Ҽ�
			if(state == GLUT_DOWN) // ����
				bRabbitAnim = false; 
			break; 
		}
		default: break; 
	}
}

// ��Ҫ����ʾ���� 
void redraw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	// �����ɫ����ɫ 
	glClearColor(0.0f, 0.5f, 0.0f, 1.0f); 
	glLoadIdentity(); 

	// �ӵ㡢�۲�����͹۲���Ϸ��� 
	gluLookAt(eye[0], eye[1], eye[2], 
		center[0], center[1], center[2], 
		0, 1, 0); 

	glEnable(GL_DEPTH_TEST); 
	glEnable(GL_LIGHTING); 
	// �����Դ 
	GLfloat gray[] = {0.4f, 0.4f, 0.4f, 1.0f}; 
	GLfloat light_pos[] = {10.0f, 10.0f, 10.0f, 1.0f}; 
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, gray); 
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos); 
	glLightfv(GL_LIGHT0, GL_AMBIENT, gray); 
	glEnable(GL_LIGHT0); 

	// �����ת����������Ӧ�ĽǶ� 
	if(bAnim) fRotate += 0.5f; 
	glRotatef(fRotate, 0.0f, 1.0f, 0.0f); 
	if(bRabbitAnim) fRabbitRotate += 0.5f; 

	glScalef(0.4f, 0.4f, 0.4f); 
	// ѡ���Ƿ�����ʾ�б� 
	if(!bDrawList) DrawScene(); 
	else Draw_Scene_List(); 

	// �õ�֡�� 
	getFPS(); 
	glutSwapBuffers(); 
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv); 
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE); 
	glutInitWindowSize(480, 480); 
	int windowHandler = glutCreateWindow("Exercise 4"); 

	glutDisplayFunc(redraw); 
	glutReshapeFunc(reshape); 
	glutKeyboardFunc(key); 
	glutMouseFunc(mouse); 
	glutIdleFunc(idle); 

	GenSceneList(); 
	glutMainLoop(); 
	return 0; 
}
