#include <windows.h>
#include <GL/glut.h>

bool bPersp = false;			// 是否开启透视
bool bWire = false;				// 是否画线
bool bAnim = false;				// 桌子和水壶是否旋转
bool bPotRot = false;			// 水壶是否旋转

int wHeight = 0, wWidth = 0;	// 窗口的高度和宽度

GLfloat fRotate = 0.0f;			// 桌子和水壶的旋转角度
GLfloat fPotRot = 0.0f;			// 水壶的旋转角度

// 观察点的位置
GLfloat eye[] = {0.0f, 0.0f, 8.0f}; 
// 观察中心的坐标
GLfloat center[] = {0.0f, 0.0f, 0.0f}; 
// 水壶的坐标
GLfloat Teapot_Center[] = {0.0f, 0.0f, 5.0f}; 

// 实现透视投影和正投影的切换
void updateView(int width, int height)
{
	glViewport(0, 0, width, height); 

	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity(); 

	GLfloat whRatio = (GLfloat) width / height; 

	if(bPersp)
        // 透视投影
	    gluPerspective(45, whRatio, 1, 100); 
	else
        // 正投影
	    glOrtho(-3, 3, -3, 3, -100, 100); 

	glMatrixMode(GL_MODELVIEW); 
}

// 处理窗口大小改变事件
void reshape(int width, int height)
{
	if(height == 0)
		height = 1; 

	wHeight = height; 
	wWidth = width; 

	updateView(wHeight, wWidth); 
}

// CPU闲置时运行函数
void idle()
{
	Sleep(10); 
	glutPostRedisplay(); 
}

// 键盘按键处理
void key(unsigned char k, int x, int y)
{
	switch(k)
	{
	case 27: // 退出
	case 'q': {exit(0); break; }
	case 'p': {bPersp = !bPersp; updateView(wHeight, wWidth);break; }

	// 桌子和水壶旋转
	case ' ': {bAnim = !bAnim; break;}
	// 画线
	case 'o': {bWire = !bWire; break;}

	// 桌子左移
	case 'a': {
		eye[0] += 0.1f; 
		center[0] += 0.1f; 
		break;
			  }
	// 桌子右移
	case 'd': {
		eye[0] -= 0.1f; 
		center[0] -= 0.1f; 
		break;
			  }
	// 桌子上移
	case 'w': {
		eye[1] -= 0.1f; 
		center[1] -= 0.1f; 
		break;
			  }
	// 桌子下移
	case 's': {
		eye[1] += 0.1f; 
		center[1] += 0.1f; 
		break;
			  }
	// 接近桌子
	case 'z': {
		eye[2] -= 0.1f; 
		break;
			  }
	// 远离桌子
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

			  //茶壶相关操作
	// 水壶右移
	case 'l': {
		if(Teapot_Center[0] == 2.5f) break; 
		Teapot_Center[0] += 0.5f; 
		break;
			  }
	// 水壶左移
	case 'j': {
		if(Teapot_Center[0] == -2.5f) break; 
		Teapot_Center[0] -= 0.5f; 
		break;
			  }
	// 水壶后移
	case 'i': {
		if(Teapot_Center[1] == 2.0f) break; 
		Teapot_Center[1] += 0.5f; 
		break;
			  }
	// 水壶前移
	case 'k': {
		if(Teapot_Center[1] == -2.0f) break; 
		Teapot_Center[1] -= 0.5f; 
		break;
			  }
	// 水壶旋转
	case 'e': {
		bPotRot = !bPotRot; 
		break;
			  }
	}
}

// 画桌腿
void Draw_Leg()
{
	glScalef(1.0f, 1.0f, 3.0f); 
	glutSolidCube(1.0f); 
}

// 画桌子和水壶
void Draw_Scene()
{
	// teapot 
	glPushMatrix(); 
	// 移到水壶的中心
	glTranslatef(Teapot_Center[0], Teapot_Center[1], Teapot_Center[2]); 
	// 调整好水壶方向
	glRotatef(90, 1, 0, 0); 
	// 旋转水壶已转过的角度
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

// 主要的画图函数
void redraw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
    glLoadIdentity(); 

	// 视点、观察坐标和观察的上方向
	gluLookAt(eye[0], eye[1], eye[2], 
		center[0], center[1], center[2], 
		0, 1, 0); 
    
	// 是否画线
	if(bWire)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); 
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); 

	glEnable(GL_DEPTH_TEST); 
	// 定义光源
	glEnable(GL_LIGHTING); 
	GLfloat white[] = {1.0f, 1.0f, 1.0f, 1.0f}; 
	GLfloat light_pos[] = {5.0f, 5.0f, 5.0f, 1.0f}; 

	glLightfv(GL_LIGHT0, GL_POSITION, light_pos); 
	glLightfv(GL_LIGHT0, GL_AMBIENT, white); 
	glEnable(GL_LIGHT0); 

	// 旋转桌子和水壶已旋转过的角度
	glRotatef(fRotate, 0.0f, 1.0f, 0.0f); 
	glRotatef(-90, 1, 0, 0); 
	glScalef(0.2f, 0.2f, 0.2f); 
	Draw_Scene(); 

	// 如果旋转，则增加相应的角度
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
