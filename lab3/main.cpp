#include <windows.h>
#include <GL/glut.h>

bool bPersp = false;			// �Ƿ���͸��
bool bWire = false;				// �Ƿ���
bool bAnim = false;				// ���Ӻ�ˮ���Ƿ���ת
bool bPotRot = false;			// ˮ���Ƿ���ת

int wHeight = 0, wWidth = 0;	// ���ڵĸ߶ȺͿ��

GLfloat fRotate = 0.0f;			// ���Ӻ�ˮ������ת�Ƕ�
GLfloat fPotRot = 0.0f;			// ˮ������ת�Ƕ�

// �۲���λ��
GLfloat eye[] = {0.0f, 0.0f, 8.0f}; 
// �۲����ĵ�����
GLfloat center[] = {0.0f, 0.0f, 0.0f}; 
// ˮ��������
GLfloat Teapot_Center[] = {0.0f, 0.0f, 5.0f}; 

// ʵ��͸��ͶӰ����ͶӰ���л�
void updateView(int width, int height)
{
	glViewport(0, 0, width, height); 

	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity(); 

	GLfloat whRatio = (GLfloat) width / height; 

	if(bPersp)
        // ͸��ͶӰ
	    gluPerspective(45, whRatio, 1, 100); 
	else
        // ��ͶӰ
	    glOrtho(-3, 3, -3, 3, -100, 100); 

	glMatrixMode(GL_MODELVIEW); 
}

// �����ڴ�С�ı��¼�
void reshape(int width, int height)
{
	if(height == 0)
		height = 1; 

	wHeight = height; 
	wWidth = width; 

	updateView(wHeight, wWidth); 
}

// CPU����ʱ���к���
void idle()
{
	Sleep(10); 
	glutPostRedisplay(); 
}

// ���̰�������
void key(unsigned char k, int x, int y)
{
	switch(k)
	{
	case 27: // �˳�
	case 'q': {exit(0); break; }
	case 'p': {bPersp = !bPersp; updateView(wHeight, wWidth);break; }

	// ���Ӻ�ˮ����ת
	case ' ': {bAnim = !bAnim; break;}
	// ����
	case 'o': {bWire = !bWire; break;}

	// ��������
	case 'a': {
		eye[0] += 0.1f; 
		center[0] += 0.1f; 
		break;
			  }
	// ��������
	case 'd': {
		eye[0] -= 0.1f; 
		center[0] -= 0.1f; 
		break;
			  }
	// ��������
	case 'w': {
		eye[1] -= 0.1f; 
		center[1] -= 0.1f; 
		break;
			  }
	// ��������
	case 's': {
		eye[1] += 0.1f; 
		center[1] += 0.1f; 
		break;
			  }
	// �ӽ�����
	case 'z': {
		eye[2] -= 0.1f; 
		break;
			  }
	// Զ������
	case 'c': {
		eye[2] += 0.1f; 
		break;
			  }
	
//    case 'f': {
//		center[0] -=0.1f; 
//		break; 
//	          }
//	case 'h': {
//		center[0] +=0.1f; 
//		break; 
//	          }
//	case 't': {
//		center[1] +=0.1f; 
//		break; 
//	          }
//	case 'g': {
//		center[1] -=0.1f; 
//		break; 
//	          }

			  //�����ز���
	// ˮ������
	case 'l': {
		if(Teapot_Center[0] == 2.5f) break; 
		Teapot_Center[0] += 0.5f; 
		break;
			  }
	// ˮ������
	case 'j': {
		if(Teapot_Center[0] == -2.5f) break; 
		Teapot_Center[0] -= 0.5f; 
		break;
			  }
	// ˮ������
	case 'i': {
		if(Teapot_Center[1] == 2.0f) break; 
		Teapot_Center[1] += 0.5f; 
		break;
			  }
	// ˮ��ǰ��
	case 'k': {
		if(Teapot_Center[1] == -2.0f) break; 
		Teapot_Center[1] -= 0.5f; 
		break;
			  }
	// ˮ����ת
	case 'e': {
		bPotRot = !bPotRot; 
		break;
			  }
	}
}

// ������
void Draw_Leg()
{
	glScalef(1.0f, 1.0f, 3.0f); 
	glutSolidCube(1.0f); 
}

// �����Ӻ�ˮ��
void Draw_Scene()
{
	// teapot 
	glPushMatrix(); 
	// �Ƶ�ˮ��������
	glTranslatef(Teapot_Center[0], Teapot_Center[1], Teapot_Center[2]); 
	// ������ˮ������
	glRotatef(90, 1, 0, 0); 
	// ��תˮ����ת���ĽǶ�
	glRotatef(fPotRot, 0, 1, 0); 
	glutSolidTeapot(1.0f); 
	glPopMatrix(); 

	// table face 
	glPushMatrix(); 
	glTranslatef(0.0f, 0.0f, 3.5f); 
	glScalef(5.0f, 4.0f, 1.0f); 
	glutSolidCube(1.0f); 
	glPopMatrix(); 

	// leg (right top)
	glPushMatrix(); 
	glTranslatef(1.5f, 1.0f, 1.5f); 
	Draw_Leg(); 
	glPopMatrix(); 
	// leg (left top)
	glPushMatrix(); 
	glTranslatef(-1.5f, 1.0f, 1.5f); 
	Draw_Leg(); 
	glPopMatrix(); 
	// leg (left bottom)
	glPushMatrix(); 
	glTranslatef(-1.5f, -1.0f, 1.5f); 
	Draw_Leg(); 
	glPopMatrix(); 
	// leg (right bottom)
	glPushMatrix(); 
	glTranslatef(1.5f, -1.0f, 1.5f); 
	Draw_Leg(); 
	glPopMatrix(); 
}

// ��Ҫ�Ļ�ͼ����
void redraw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
    glLoadIdentity(); 

	// �ӵ㡢�۲�����͹۲���Ϸ���
	gluLookAt(eye[0], eye[1], eye[2], 
		center[0], center[1], center[2], 
		0, 1, 0); 
    
	// �Ƿ���
	if(bWire)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); 
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); 

	glEnable(GL_DEPTH_TEST); 
	// �����Դ
	glEnable(GL_LIGHTING); 
	GLfloat white[] = {1.0f, 1.0f, 1.0f, 1.0f}; 
	GLfloat light_pos[] = {5.0f, 5.0f, 5.0f, 1.0f}; 

	glLightfv(GL_LIGHT0, GL_POSITION, light_pos); 
	glLightfv(GL_LIGHT0, GL_AMBIENT, white); 
	glEnable(GL_LIGHT0); 

	// ��ת���Ӻ�ˮ������ת���ĽǶ�
	glRotatef(fRotate, 0.0f, 1.0f, 0.0f); 
	glRotatef(-90, 1, 0, 0); 
	glScalef(0.2f, 0.2f, 0.2f); 
	Draw_Scene(); 

	// �����ת����������Ӧ�ĽǶ�
	if(bAnim) fRotate += 0.5f; 
	if(bPotRot) fPotRot += 0.5f; 

	glutSwapBuffers(); 
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv); 
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE); 
	glutInitWindowSize(480, 480); 
	int windowHandler = glutCreateWindow("Ex 3"); 

	glutDisplayFunc(redraw); 
	glutReshapeFunc(reshape); 
	glutIdleFunc(idle); 
	glutKeyboardFunc(key); 

	glutMainLoop(); 
	return 0; 
}
