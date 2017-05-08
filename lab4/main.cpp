#include <stdio.h>
#include <string.h>
#include <GL/glut.h>

#include "stanford_bunny.h"

// 观察点的位置
GLfloat eye[] = {0, 4, 6}; 
// 观察中心的坐标
GLfloat center[] = {0, 0, 0}; 
// 每次视点移动的距离
GLfloat fDistance = 0.2f; 

// 是否旋转
bool bAnim = false; 
// 已旋转的角度
GLfloat fRotate = 0; 

// 是否用显示列表
bool bDrawList = false; 
GLint tableList, rabbitList; 

// 兔子是否旋转
bool bRabbitAnim = false; 
// 兔子已旋转的角度
GLfloat fRabbitRotate = 0; 

// 兔子的数量
GLint rabbitNum = 1; 
// 桌子的宽度
GLfloat tableWidth = 6.0f; 

// 计算帧数
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
	glMatrixMode(GL_PROJECTION);  // 选择投影矩阵
	glPushMatrix();               // 保存原矩阵
	glLoadIdentity();             // 装入单位矩阵
	glOrtho(0,480,0,480,-1,1);    // 位置正投影
	glMatrixMode(GL_MODELVIEW);   // 选择Modelview矩阵
	glPushMatrix();               // 保存原矩阵
	glLoadIdentity();             // 装入单位矩阵
	glRasterPos2f(10,10);
	for (c=buffer; *c != '\0'; c++) {		
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
	}
	glMatrixMode(GL_PROJECTION);  // 选择投影矩阵
	glPopMatrix();                // 重置为原保存矩阵
	glMatrixMode(GL_MODELVIEW);   // 选择Modelview矩阵
	glPopMatrix();                // 重置为原保存矩阵
	glEnable(GL_DEPTH_TEST);	
}

// 画出桌子
// 显示列表内不能传入动态数据
// 所以为了显示列表下能增加桌子的宽度，画桌面就要放在显示列表外
void DrawTable()
{
	// 画四个桌腿
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

// 画整个场景
void DrawScene()
{
	int i; 
	
	// 画出兔子
	glPushMatrix(); 
	// 第一个兔子的位置，根据桌面宽度动态调整
	glTranslatef(3.75f - 1.1f, 4.5f, tableWidth/2-0.7f/*2.3f*/); 
	glScalef(2.0f, 2.0f, 2.0f); 
	for(i = 0; i < rabbitNum; i++)
	{
		glPushMatrix(); 
		glRotatef(fRabbitRotate, 0, 1, 0); 
		DrawBunny(); 
		glPopMatrix(); 
		// 下一个兔子的位置
		glTranslatef(-0.9f, 0.0f, 0.0f); 
		// 一行兔子满后会换行
		if((i + 1) % 4 == 0) glTranslatef(3.6f, 0.0f, -0.75f); 
	}
	glPopMatrix(); 

	// 画桌子的四个腿
	DrawTable(); 
	// 画桌面
	glPushMatrix(); 
	glTranslatef(0.0f, 3.5f, 0.0f); 
	//glScalef(5.0f, 1.0f, 4.0f); 
	glScalef(7.5f, 0.5f, tableWidth); 
	glutSolidCube(1.0f); 
	glPopMatrix(); 
}

// 生成场景需要的全部显示列表
void GenSceneList()
{
	tableList = glGenLists(2); 
	rabbitList = tableList + 1; 

	// 桌子的显示列表
	glNewList(tableList, GL_COMPILE); 
	DrawTable(); 
	glEndList(); 

	// 兔子的显示列表
	glNewList(rabbitList, GL_COMPILE); 
	DrawBunny(); 
	glEndList(); 

	return ; 
}

// 用显示列表画场景
void Draw_Scene_List()
{
	int i; 
	
	glPushMatrix(); 
	// glTranslatef(2.2f, 4.5f, 1.8f); 
	// 第一个图兔子的位置，根据桌子宽度动态调整
	glTranslatef(3.75f - 1.1f, 4.5f, tableWidth/2-0.7f/*2.3f*/); 
	glScalef(2.0f, 2.0f, 2.0f); 
	for(i = 0; i < rabbitNum; i++)
	{
		glCallList(rabbitList); 
		// glTranslatef(-0.75f, 0.0f, 0.0f); 
		// 下一个兔子的位置
		glTranslatef(-0.9f, 0.0f, 0.0f); 
		// 一行兔子满后会换行
		if((i + 1) % 4 == 0) glTranslatef(3.6f, 0.0f, -0.75f); // glTranslatef(3.0f, 0.0f, -0.6f); 
	}
	glPopMatrix(); 
	
	// 画桌子的四个腿 
	glCallList(tableList); 
	// 画桌面 
	glPushMatrix(); 
	glTranslatef(0.0f, 3.5f, 0.0f); 
	//glScalef(5.0f, 1.0f, 4.0f); 
	glScalef(7.5f, 0.5f, tableWidth); 
	glutSolidCube(1.0f); 
	glPopMatrix(); 
}

// 调整窗口大小时重新设置视口等
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

// 闲置时调用的函数
void idle()
{
	glutPostRedisplay(); 
}

// 键盘按键处理函数 
void key(unsigned char k, int x, int y)
{
	switch(k)
	{
		case 27: // 退出 
		case 'q': {exit(0); break; }
		case 'a': // 桌子左移 
		{
			eye[0] += fDistance; 
			center[0] += fDistance; 
			break; 
		}
		case 'd': // 桌子右移 
		{
			eye[0] -= fDistance; 
			center[0] -= fDistance; 
			break; 
		}
		case 'w': // 桌子上移 
		{
			eye[1] -= fDistance; 
			center[1] -= fDistance; 
			break; 
		}
		case 's': // 桌子下移 
		{
			eye[1] += fDistance; 
			center[1] += fDistance; 
			break; 
		}
		case 'z': // 视点靠近桌子 
		{
			eye[2] *= 0.95; 
			break; 
		}
		case 'c': // 视点远离桌子 
		{
			eye[2] *= 1.05; 
			break; 
		}
		case 'l': // 是否使用显示列表
		{
			bDrawList = !bDrawList; 
			break; 
		}
		case ' ': // 是否旋转 
		{
			bAnim = !bAnim; 
			break; 
		}
		case 'i': // 增加兔子数量 
		{
			// if(rabbitNum < 16) rabbitNum++; 
			// 当兔子数量超过16个并要换行时，桌子宽度增加 
			if(rabbitNum >= 16 && rabbitNum % 4 == 0) tableWidth += 1.5f; 
			rabbitNum++; 
			break; 
		}
		case 'k': // 减少兔子数量 
		{
			if(rabbitNum > 1) rabbitNum--; 
			// 当兔子数量超过16个并要换行时，桌子宽度减少 
			if(rabbitNum >= 16 && rabbitNum % 4 == 0) tableWidth -= 1.5f; 
			break; 
		}
		default: break; 
	}
}

// 鼠标按键处理函数
void mouse(int button, int state, int x, int y)
{
	switch(button)
	{
		case GLUT_LEFT_BUTTON: {   // 左键
			if(state == GLUT_DOWN) // 按下
				bRabbitAnim = true; 
			break; 
		}
		case GLUT_MIDDLE_BUTTON: {
			break; 
		}
		case GLUT_RIGHT_BUTTON: {  // 右键
			if(state == GLUT_DOWN) // 按下
				bRabbitAnim = false; 
			break; 
		}
		default: break; 
	}
}

// 主要的显示函数 
void redraw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	// 清除颜色是绿色 
	glClearColor(0.0f, 0.5f, 0.0f, 1.0f); 
	glLoadIdentity(); 

	// 视点、观察坐标和观察的上方向 
	gluLookAt(eye[0], eye[1], eye[2], 
		center[0], center[1], center[2], 
		0, 1, 0); 

	glEnable(GL_DEPTH_TEST); 
	glEnable(GL_LIGHTING); 
	// 定义光源 
	GLfloat gray[] = {0.4f, 0.4f, 0.4f, 1.0f}; 
	GLfloat light_pos[] = {10.0f, 10.0f, 10.0f, 1.0f}; 
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, gray); 
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos); 
	glLightfv(GL_LIGHT0, GL_AMBIENT, gray); 
	glEnable(GL_LIGHT0); 

	// 如果旋转，则增加相应的角度 
	if(bAnim) fRotate += 0.5f; 
	glRotatef(fRotate, 0.0f, 1.0f, 0.0f); 
	if(bRabbitAnim) fRabbitRotate += 0.5f; 

	glScalef(0.4f, 0.4f, 0.4f); 
	// 选择是否用显示列表 
	if(!bDrawList) DrawScene(); 
	else Draw_Scene_List(); 

	// 得到帧数 
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
