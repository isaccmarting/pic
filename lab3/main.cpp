#include <windows.h>
#include <GL/glut.h>

bool bPersp = false; 
bool bWire = false; 
bool bAnim = false; 
bool bPotRot = false; // 

int wHeight = 0, wWidth = 0; 

GLfloat fRotate = 0.0f; 
GLfloat fPotRot = 0.0f; 

GLfloat eye[] = {0.0f, 0.0f, 8.0f}; 
GLfloat center[] = {0.0f, 0.0f, 0.0f}; 
GLfloat Teapot_Center[] = {0.0f, 0.0f, 5.0f}; 

void updateView(int width, int height)
{
	glViewport(0, 0, width, height); 

	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity(); 

	GLfloat whRatio = (GLfloat) width / height; 

	if(bPersp)
        gluPerspective(45, whRatio, 1, 100); 
	else
        glOrtho(-3, 3, -3, 3, -100, 100); 

	glMatrixMode(GL_MODELVIEW); 
}

void reshape(int width, int height)
{
	if(height == 0)
		height = 1; 

	wHeight = height; 
	wWidth = width; 

	updateView(wHeight, wWidth); 
}

void idle()
{
	Sleep(10); 
	glutPostRedisplay(); 
}

void key(unsigned char k, int x, int y)
{
	switch(k)
	{
	case 27:
	case 'q': {exit(0); break; }
	case 'p': {bPersp = !bPersp; updateView(wHeight, wWidth);break; }

	case ' ': {bAnim = !bAnim; break;}
	case 'o': {bWire = !bWire; break;}

	case 'a': {//todo, hint: eye[] and center[] are the keys to solve the problems
		eye[0] += 0.1f; 
		center[0] += 0.1f; 
		break;
			  }
	case 'd': {//todo
		eye[0] -= 0.1f; 
		center[0] -= 0.1f; 
		break;
			  }
	case 'w': {//todo
		eye[1] -= 0.1f; 
		center[1] -= 0.1f; 
		break;
			  }
	case 's': {//todo
		eye[1] += 0.1f; 
		center[1] += 0.1f; 
		break;
			  }
	case 'z': {//todo
		eye[2] -= 0.1f; 
		break;
			  }
	case 'c': {//todo
		eye[2] += 0.1f; 
		break;
			  }

			  //²èºøÏà¹Ø²Ù×÷
	case 'l': {//todo, hint:use the ARRAY that you defined, and notice the teapot can NOT be moved out the range of the table.
		if(Teapot_Center[0] == 2.5f) break; 
		Teapot_Center[0] += 0.5f; 
		break;
			  }
	case 'j': {//todo
		if(Teapot_Center[0] == -2.5f) break; 
		Teapot_Center[0] -= 0.5f; 
		break;
			  }
	case 'i': {//todo
		if(Teapot_Center[1] == 2.0f) break; 
		Teapot_Center[1] += 0.5f; 
		break;
			  }
	case 'k': {//todo
		if(Teapot_Center[1] == -2.0f) break; 
		Teapot_Center[1] -= 0.5f; 
		break;
			  }
	case 'e': {//todo
		bPotRot = !bPotRot; 
		break;
			  }
	}
}

void Draw_Leg()
{
	glScalef(1.0f, 1.0f, 3.0f); 
	glutSolidCube(1.0f); 
}

void Draw_Scene()
{
	// teapot 
	glPushMatrix(); 
	// 
	glTranslatef(Teapot_Center[0], Teapot_Center[1], Teapot_Center[2]); 
	glRotatef(90, 1, 0, 0); 
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

	glEnable(GL_DEPTH_TEST); 
	glEnable(GL_LIGHTING); 
	GLfloat white[] = {1.0f, 1.0f, 1.0f, 1.0f}; 
	GLfloat light_pos[] = {5.0f, 5.0f, 5.0f, 1.0f}; 

	glLightfv(GL_LIGHT0, GL_POSITION, light_pos); 
	glLightfv(GL_LIGHT0, GL_AMBIENT, white); 
	glEnable(GL_LIGHT0); 

	glRotatef(fRotate, 0.0f, 1.0f, 0.0f); 
	glRotatef(-90, 1, 0, 0); 
	glScalef(0.2f, 0.2f, 0.2f); 
	Draw_Scene(); 

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
