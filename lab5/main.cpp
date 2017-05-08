#include <GL/glut.h>

// GLfloat fTranslate; 
GLfloat fRotate; 

GLfloat eye[] = {0.0f, 0.0f, 8.0f}; 
GLfloat center[] = {0.0f, 0.0f, 0.0f}; 

GLfloat light_pos[] = {5.0f, 5.0f, 5.0f, 1.0f}; 
GLfloat *light_color; 

GLfloat light1_pos[] = {0.0f, 18.0f, 0.0f, 1.0f}; 
GLfloat light1_dir[] = {0.0f, -100.0f, 0.0f}; 
GLfloat light1_angle = 1.125f; 

bool bPersp = false; 
bool bAnim = false; 
bool bWire = false; 
bool bLightColor = false; 

GLint wWidth = 0, wHeight = 0; 

void Draw_Leg()
{
	glScalef(1.0f, 1.0f, 3.0f); 
	glutSolidCube(1.0f); 
}

void Draw_Triangle()
{
	GLfloat teapot_amb[] = {0.92f, 0.89f, 0.41f, 1.0f}; // 0.92f, 0.89f, 0.41f, 1.0f
	GLfloat teapot_dif[] = {0.6f, 0.6f, 0.0f, 1.0f}; 
	GLfloat teapot_spe[] = {0.006f, 0.006f, 0.006f, 1.0f}; 
	GLfloat table_face_amb[] = {1.0f, 0.0f, 0.0f, 1.0f}; 
	GLfloat table_face_dif[] = {1.0f, 0.0f, 0.0f, 1.0f}; 
	GLfloat table_leg_amb1[] = {0.0f, 1.0f, 0.0f, 1.0f}; 
	GLfloat table_leg_dif1[] = {0.0f, 1.0f, 0.0f, 1.0f}; 
	GLfloat table_leg_amb2[] = {1.0f, 1.0f, 0.0f, 1.0f}; 
	GLfloat table_leg_dif2[] = {1.0f, 1.0f, 0.0f, 1.0f}; 
	GLfloat table_leg_amb3[] = {0.0f, 1.0f, 1.0f, 1.0f}; 
	GLfloat table_leg_dif3[] = {0.0f, 1.0f, 1.0f, 1.0f}; 
	GLfloat table_leg_amb4[] = {0.0f, 0.0f, 1.0f, 1.0f}; 
	GLfloat table_leg_dif4[] = {0.0f, 0.0f, 1.0f, 1.0f}; 
	
	glFrontFace(GL_CW); 
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

	glMaterialf(GL_FRONT, GL_SHININESS, 0.0f); 

	glMaterialfv(GL_FRONT, GL_AMBIENT, table_face_amb); 
	glMaterialfv(GL_FRONT, GL_DIFFUSE, table_face_dif); 
	glMaterialfv(GL_FRONT, GL_SPECULAR, table_face_dif); 
	glPushMatrix(); 
	glTranslatef(0.0f, 0.0f, 3.5f); 
	glScalef(5.0f, 4.0f, 1.0f); 
	glutSolidCube(1.0f); 
	glPopMatrix(); 

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

void updateView(int width, int height)
{
	glViewport(0, 0, width, height); 

	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity(); 
	GLfloat whRatio = (GLfloat) width/height; 
	if(bPersp) 
		gluPerspective(45.0f, whRatio, 0.1f, 100.0f); 
	else
		glOrtho(-3, 3, -3, 3, -100, 100); 

	glMatrixMode(GL_MODELVIEW); 
}

void reshape(int width, int height)
{
	if(height == 0)
		height = 1; 
	wWidth = width; 
	wHeight = height; 

	updateView(wWidth, wHeight); 
}

void idle()
{
	glutPostRedisplay(); 
}

void key(unsigned char k, int x, int y)
{
	switch(k)
	{
		case 27: 
		case 'q': {exit(0); break; }
		case 'p': {bPersp = !bPersp; break; }
		case 'o': {bWire = !bWire; break; }
		case ' ': {bAnim = !bAnim; break; }

		case 'a': {
			eye[0] += 0.2f; 
			center[0] += 0.2f; 
			break; 
		}
		case 'd': {
			eye[0] -= 0.2f; 
			center[0] -= 0.2f; 
			break; 
		}
		case 'w': {
			eye[1] -= 0.2f; 
			center[1] -= 0.2f; 
			break; 
		}
		case 's': {
			eye[1] += 0.2f; 
			center[1] += 0.2f; 
			break; 
		}
		case 'z': {
			eye[2] -= 0.2f; 
			center[2] -= 0.2f; 
			break; 
		}
		case 'c': {
			eye[2] += 0.2f; 
			center[2] += 0.2f; 
			break; 
		}

		case 'j': {
			light_pos[0] -= 0.2f; 
			break; 
		}
		case 'l': {
			light_pos[0] += 0.2f; 
			break; 
		}
		case 'i': {
			light_pos[1] += 0.2f; 
			break; 
		}
		case 'k': {
			light_pos[1] -= 0.2f; 
			break; 
		}
		case 'n': {
			light_pos[2] -= 0.2f; 
			break; 
		}
		case 'm': {
			light_pos[2] += 0.2f; 
			break; 
		}
		case 'u': {
			bLightColor = !bLightColor; 
			break; 
		}

		case 'f': {
			light1_dir[0] -= 1.0f; 
			break; 
		}
		case 'h': {
			light1_dir[0] += 1.0f; 
			break; 
		}
		case 't': {
			light1_dir[1] += 1.0f; 
			break; 
		}
		case 'g': {
			light1_dir[1] -= 1.0f; 
			break; 
		}
		case 'v': {
			light1_dir[2] -= 1.0f; 
			break; 
		}
		case 'b': {
			light1_dir[2] += 1.0f; 
			break; 
		}
		case 'r': {
			if(light1_angle < 3.14f) light1_angle += 3.14f / 16; 
			break; 
		}
		case 'y': {
			if(light1_angle > 3.14f / 16) light1_angle -= 3.14f / 16; 
			break; 
		}
	}
	updateView(wWidth, wHeight); 
}

void redraw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	glLoadIdentity(); 
	gluLookAt(eye[0], eye[1], eye[2], 
		center[0], center[1], center[2], 
		0, 1, 0); 

	if(bWire) 
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); 
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); 

	glFrontFace(GL_CCW); 
	glEnable(GL_CULL_FACE); 
	glCullFace(GL_BACK); 
	glDepthFunc(GL_LESS); 
	glEnable(GL_DEPTH_TEST); 
	glEnable(GL_LIGHTING); 
	GLfloat white[] = {1.0f, 1.0f, 1.0f, 1.0f}; 
	GLfloat blue[] = {0.0f, 0.0f, 1.0f, 1.0f}; 
	GLfloat red[] = {1.0f, 0.0f, 0.0f, 1.0f}; 
	GLfloat black[] = {0.0f, 0.0f, 0.0f, 1.0f}; 
	if(bLightColor)
		light_color = red; 
	else
		light_color = white; 
	// GLfloat light_amb[] = {0.0f, 0.0f, 0.0f, 1.0f}; 
	// GLfloat light_dif[] = {0.0f, 0.0f, 0.0f, 1.0f}; 
	// GLfloat light_spe[] = {0.0f, 0.0f, 0.0f, 1.0f}; 
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos); 
	glLightfv(GL_LIGHT0, GL_AMBIENT, black); 
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_color); 
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_color); 
	glEnable(GL_LIGHT0); 

	glLightfv(GL_LIGHT1, GL_POSITION, light1_pos); 
	glLightfv(GL_LIGHT1, GL_AMBIENT, black); 
	glLightfv(GL_LIGHT1, GL_DIFFUSE, blue); 
	glLightfv(GL_LIGHT1, GL_SPECULAR, blue); 
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, light1_angle); 
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, light1_dir); 
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 6.0f); 
	glEnable(GL_LIGHT1); 

	glRotatef(fRotate, 0, 1, 0); 
	glRotatef(-90, 1, 0, 0); 
	glScalef(0.2f, 0.2f, 0.2f); 
	Draw_Triangle(); 

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
