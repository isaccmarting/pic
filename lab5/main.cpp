#include <GL/glut.h>

// ��������ת�ĽǶ�
GLfloat fRotate; 

// �ӵ�����
GLfloat eye[] = {0.0f, 0.0f, 8.0f}; 
// �۲�����
GLfloat center[] = {0.0f, 0.0f, 0.0f}; 

// light0������
GLfloat light_pos[] = {5.0f, 5.0f, 5.0f, 1.0f}; 
// light0����ɫ��Ϣ
GLfloat *light_color; 

// �۹��light1������
GLfloat light1_pos[] = {0.0f, 18.0f, 0.0f, 1.0f}; 
// �۹��light1�ĳ���
GLfloat light1_dir[] = {0.0f, -100.0f, 0.0f}; 
// �۹��light1�ſ��ĽǶ�
GLfloat light1_angle = 1.125f; 

bool bPersp = false;		// �Ƿ�͸��ͶӰ
bool bAnim = false;			// �Ƿ���ת
bool bWire = false;			// �Ƿ���
bool bLightColor = false;	// ѡ��ƹ����ɫ

GLint wWidth = 0, wHeight = 0; 

// ������
void Draw_Leg()
{
	glScalef(1.0f, 1.0f, 3.0f); 
	glutSolidCube(1.0f); 
}

// ���������������������
void Draw_Triangle()
{
	// ����Ĳ�����Ϣ
	GLfloat teapot_amb[] = {0.92f, 0.89f, 0.41f, 1.0f}; // 0.92f, 0.89f, 0.41f, 1.0f
	GLfloat teapot_dif[] = {0.6f, 0.6f, 0.0f, 1.0f}; 
	GLfloat teapot_spe[] = {0.006f, 0.006f, 0.006f, 1.0f}; 
	// ����Ĳ�����Ϣ
	GLfloat table_face_amb[] = {1.0f, 0.0f, 0.0f, 1.0f}; 
	GLfloat table_face_dif[] = {1.0f, 0.0f, 0.0f, 1.0f}; 
	// �ĸ����ǵĲ�����Ϣ
	GLfloat table_leg_amb1[] = {0.0f, 1.0f, 0.0f, 1.0f}; 
	GLfloat table_leg_dif1[] = {0.0f, 1.0f, 0.0f, 1.0f}; 
	GLfloat table_leg_amb2[] = {1.0f, 1.0f, 0.0f, 1.0f}; 
	GLfloat table_leg_dif2[] = {1.0f, 1.0f, 0.0f, 1.0f}; 
	GLfloat table_leg_amb3[] = {0.0f, 1.0f, 1.0f, 1.0f}; 
	GLfloat table_leg_dif3[] = {0.0f, 1.0f, 1.0f, 1.0f}; 
	GLfloat table_leg_amb4[] = {0.0f, 0.0f, 1.0f, 1.0f}; 
	GLfloat table_leg_dif4[] = {0.0f, 0.0f, 1.0f, 1.0f}; 
	
	// �����
	glFrontFace(GL_CW); 
	// ���ò��ʣ������߹�
	glMaterialfv(GL_FRONT, GL_AMBIENT, teapot_amb); 
	glMaterialfv(GL_FRONT, GL_DIFFUSE, teapot_dif); 
	glMaterialfv(GL_FRONT, GL_SPECULAR, teapot_spe); 
	glMaterialf(GL_FRONT, GL_SHININESS, 3.0f); 
	glPushMatrix(); 
	glTranslatef(0.0f, 0.0f, 4.0f+1.0f); 
	glRotatef(90, 1, 0, 0); 
	glutSolidTeapot(1.0f); 
	glPopMatrix(); 
	glFrontFace(GL_CCW); 

	// ȡ���߹�
	glMaterialf(GL_FRONT, GL_SHININESS, 0.0f); 

	// ������
	glMaterialfv(GL_FRONT, GL_AMBIENT, table_face_amb); 
	glMaterialfv(GL_FRONT, GL_DIFFUSE, table_face_dif); 
	glMaterialfv(GL_FRONT, GL_SPECULAR, table_face_dif); 
	glPushMatrix(); 
	glTranslatef(0.0f, 0.0f, 3.5f); 
	glScalef(5.0f, 4.0f, 1.0f); 
	glutSolidCube(1.0f); 
	glPopMatrix(); 

	// ���ĸ�����
	glMaterialfv(GL_FRONT, GL_AMBIENT, table_leg_amb1); 
	glMaterialfv(GL_FRONT, GL_DIFFUSE, table_leg_dif1); 
	glMaterialfv(GL_FRONT, GL_SPECULAR, table_leg_dif1); 
	glPushMatrix(); 
	glTranslatef(1.5f, 1.0f, 1.5f); 
	Draw_Leg(); 
	glPopMatrix(); 

	glMaterialfv(GL_FRONT, GL_AMBIENT, table_leg_amb2); 
	glMaterialfv(GL_FRONT, GL_DIFFUSE, table_leg_dif2); 
	glMaterialfv(GL_FRONT, GL_SPECULAR, table_leg_dif2); 
	glPushMatrix(); 
	glTranslatef(-1.5f, 1.0f, 1.5f); 
	Draw_Leg(); 
	glPopMatrix(); 

	glMaterialfv(GL_FRONT, GL_AMBIENT, table_leg_amb3); 
	glMaterialfv(GL_FRONT, GL_DIFFUSE, table_leg_dif3); 
	glMaterialfv(GL_FRONT, GL_SPECULAR, table_leg_dif3); 
	glPushMatrix(); 
	glTranslatef(-1.5f, -1.0f, 1.5f); 
	Draw_Leg(); 
	glPopMatrix(); 

	glMaterialfv(GL_FRONT, GL_AMBIENT, table_leg_amb4); 
	glMaterialfv(GL_FRONT, GL_DIFFUSE, table_leg_dif4); 
	glMaterialfv(GL_FRONT, GL_SPECULAR, table_leg_dif4); 
	glPushMatrix(); 
	glTranslatef(1.5f, -1.0f, 1.5f); 
	Draw_Leg(); 
	glPopMatrix(); 
}

// ����ͶӰ��ʽ��
void updateView(int width, int height)
{
	glViewport(0, 0, width, height); 

	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity(); 
	GLfloat whRatio = (GLfloat) width/height; 
	// ͸��ͶӰ������ͶӰ
	if(bPersp) 
		gluPerspective(45.0f, whRatio, 0.1f, 100.0f); 
	else
		glOrtho(-3, 3, -3, 3, -100, 100); 

	glMatrixMode(GL_MODELVIEW); 
}

// ���ڴ�С�ı�ص�����
void reshape(int width, int height)
{
	if(height == 0)
		height = 1; 
	wWidth = width; 
	wHeight = height; 

	updateView(wWidth, wHeight); 
}

// CPU���ûص�����
void idle()
{
	glutPostRedisplay(); 
}

// �����ص�����
void key(unsigned char k, int x, int y)
{
	switch(k)
	{
		case 27: // �˳�
		case 'q': {exit(0); break; }
		// ͸��ͶӰ����ͶӰ���л�
		case 'p': {bPersp = !bPersp; break; }
		// �Ƿ���
		case 'o': {bWire = !bWire; break; }
		// �Ƿ���ת
		case ' ': {bAnim = !bAnim; break; }

		case 'a': { // �൱��Ŀ������
			eye[0] += 0.2f; 
			center[0] += 0.2f; 
			break; 
		}
		case 'd': { // �൱��Ŀ������
			eye[0] -= 0.2f; 
			center[0] -= 0.2f; 
			break; 
		}
		case 'w': { // �൱��Ŀ������
			eye[1] -= 0.2f; 
			center[1] -= 0.2f; 
			break; 
		}
		case 's': { // �൱��Ŀ������
			eye[1] += 0.2f; 
			center[1] += 0.2f; 
			break; 
		}
		case 'z': { // �ӽ�Ŀ��
			eye[2] -= 0.2f; 
			center[2] -= 0.2f; 
			break; 
		}
		case 'c': { // Զ��Ŀ��
			eye[2] += 0.2f; 
			center[2] += 0.2f; 
			break; 
		}

		case 'j': { // ��Դ����
			light_pos[0] -= 0.2f; 
			break; 
		}
		case 'l': { // ��Դ����
			light_pos[0] += 0.2f; 
			break; 
		}
		case 'i': { // ��Դ����
			light_pos[1] += 0.2f; 
			break; 
		}
		case 'k': { // ��Դ����
			light_pos[1] -= 0.2f; 
			break; 
		}
		case 'n': { // ��ԴԶ����Ļ
			light_pos[2] -= 0.2f; 
			break; 
		}
		case 'm': { // ��Դ�ӽ���Ļ
			light_pos[2] += 0.2f; 
			break; 
		}
		case 'u': { // �л���Դ��ɫ
			bLightColor = !bLightColor; 
			break; 
		}

		case 'f': { // �۹�Ƴ�������
			light1_dir[0] -= 1.0f; 
			break; 
		}
		case 'h': { // �۹�Ƴ�������
			light1_dir[0] += 1.0f; 
			break; 
		}
		case 't': { // �۹�Ƴ�������
			light1_dir[1] += 1.0f; 
			break; 
		}
		case 'g': { // �۹�Ƴ�������
			light1_dir[1] -= 1.0f; 
			break; 
		}
		case 'v': { // �۹�Ƴ���Զ����Ļ
			light1_dir[2] -= 1.0f; 
			break; 
		}
		case 'b': { // �۹�Ƴ���ӽ���Ļ
			light1_dir[2] += 1.0f; 
			break; 
		}
		case 'r': { // �۹�ƵĽǶȱ��
			if(light1_angle < 3.14f) light1_angle += 3.14f / 16; 
			break; 
		}
		case 'y': { // �۹�ƵĽǶȱ�С
			if(light1_angle > 3.14f / 16) light1_angle -= 3.14f / 16; 
			break; 
		}
	}
	updateView(wWidth, wHeight); 
}

// ��ͼ�ص�����
void redraw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	glLoadIdentity(); 
	// �趨�ӵ㡢�۲�����͹۲�������
	gluLookAt(eye[0], eye[1], eye[2], 
		center[0], center[1], center[2], 
		0, 1, 0); 

	if(bWire) // �Ƿ���
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); 
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); 

	// ��ȥ����
	glFrontFace(GL_CCW); 
	glEnable(GL_CULL_FACE); 
	glCullFace(GL_BACK); 
	// ������Ӱ
	glDepthFunc(GL_LESS); 
	glEnable(GL_DEPTH_TEST); 
	// ��������
	glEnable(GL_LIGHTING); 
	GLfloat white[] = {1.0f, 1.0f, 1.0f, 1.0f}; 
	GLfloat blue[] = {0.0f, 0.0f, 1.0f, 1.0f}; 
	GLfloat red[] = {1.0f, 0.0f, 0.0f, 1.0f}; 
	GLfloat black[] = {0.0f, 0.0f, 0.0f, 1.0f}; 
	if(bLightColor) // �л���Դ��ɫ
		light_color = red; 
	else
		light_color = white; 
	// ���ù�Դlight0
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos); 
	glLightfv(GL_LIGHT0, GL_AMBIENT, black); 
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_color); 
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_color); 
	glEnable(GL_LIGHT0); 

	// ���ù�Դlight1�ɾ۹��
	glLightfv(GL_LIGHT1, GL_POSITION, light1_pos); 
	glLightfv(GL_LIGHT1, GL_AMBIENT, black); 
	glLightfv(GL_LIGHT1, GL_DIFFUSE, blue); 
	glLightfv(GL_LIGHT1, GL_SPECULAR, blue); 
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, light1_angle); 
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, light1_dir); 
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 6.0f); 
	glEnable(GL_LIGHT1); 

	// ��ת����ת�ĽǶȣ�����ͼ
	glRotatef(fRotate, 0, 1, 0); 
	glRotatef(-90, 1, 0, 0); 
	glScalef(0.2f, 0.2f, 0.2f); 
	Draw_Triangle(); 

	// �����ת��������ת�ĽǶ�����
	if(bAnim) fRotate += 0.5f; 
	glutSwapBuffers(); 
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv); 
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE); 
	glutInitWindowSize(480, 480); 
	int windowHandle = glutCreateWindow("Simple GLUT App"); 

	glutDisplayFunc(redraw); 
	glutReshapeFunc(reshape); 
	glutKeyboardFunc(key); 
	glutIdleFunc(idle); 

	glutMainLoop(); 
	return 0; 
}
