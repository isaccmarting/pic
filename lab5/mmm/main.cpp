#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

// 整体已旋转的角度
GLfloat fRotate; 

// 视点坐标
GLfloat eye[] = {0.0f, 0.0f, 8.0f}; 
// 观察坐标
GLfloat center[] = {0.0f, 0.0f, 0.0f}; 

// light0的坐标
GLfloat light_pos[] = {5.0f, 5.0f, 5.0f, 1.0f}; 
// light0的颜色信息
GLfloat *light_color; 

// 聚光灯light1的坐标
GLfloat light1_pos[] = {0.0f, 18.0f, 0.0f, 1.0f}; 
// 聚光灯light1的朝向
GLfloat light1_dir[] = {0.0f, -100.0f, 0.0f}; 
// 聚光灯light1张开的角度
GLfloat light1_angle = 1.125f; 

bool bPersp = false;		// 是否透视投影
bool bAnim = false;			// 是否旋转
bool bWire = false;			// 是否画线
bool bLightColor = false;	// 选择灯光的颜色

GLfloat PI = 3.1415926; 
GLfloat xViewAngle = PI/2;  // 视角与x轴的夹角 
GLfloat yViewAngle = PI/2;  // 视角与y轴的夹角 
GLint old_x=240, old_y=240; // 保存原先x、y的屏幕坐标 
GLfloat r = 7.0f;			// 视野的半径 
bool bMouseDown = false;	// 鼠标是否按下 

GLint wWidth = 0, wHeight = 0; 

// 画桌角
void Draw_Leg()
{
	glScalef(1.0f, 1.0f, 3.0f); 
	glutSolidCube(1.0f); 
}

// 画整个场景，茶壶和桌子
void Draw_Triangle()
{
	// 茶壶的材质信息
	GLfloat teapot_amb[] = {0.92f, 0.89f, 0.41f, 1.0f}; // 0.92f, 0.89f, 0.41f, 1.0f
	GLfloat teapot_dif[] = {0.6f, 0.6f, 0.0f, 1.0f}; 
	GLfloat teapot_spe[] = {0.006f, 0.006f, 0.006f, 1.0f}; 
	// 桌面的材质信息
	GLfloat table_face_amb[] = {1.0f, 0.0f, 0.0f, 1.0f}; 
	GLfloat table_face_dif[] = {1.0f, 0.0f, 0.0f, 1.0f}; 
	// 四个桌角的材质信息
	GLfloat table_leg_amb1[] = {0.0f, 1.0f, 0.0f, 1.0f}; 
	GLfloat table_leg_dif1[] = {0.0f, 1.0f, 0.0f, 1.0f}; 
	GLfloat table_leg_amb2[] = {1.0f, 1.0f, 0.0f, 1.0f}; 
	GLfloat table_leg_dif2[] = {1.0f, 1.0f, 0.0f, 1.0f}; 
	GLfloat table_leg_amb3[] = {0.0f, 1.0f, 1.0f, 1.0f}; 
	GLfloat table_leg_dif3[] = {0.0f, 1.0f, 1.0f, 1.0f}; 
	GLfloat table_leg_amb4[] = {0.0f, 0.0f, 1.0f, 1.0f}; 
	GLfloat table_leg_dif4[] = {0.0f, 0.0f, 1.0f, 1.0f}; 
	
	// 画茶壶
	glFrontFace(GL_CW); 
	// 设置材质，包括高光
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

	// 取消高光
	glMaterialf(GL_FRONT, GL_SHININESS, 0.0f); 

	// 画桌面
	glMaterialfv(GL_FRONT, GL_AMBIENT, table_face_amb); 
	glMaterialfv(GL_FRONT, GL_DIFFUSE, table_face_dif); 
	glMaterialfv(GL_FRONT, GL_SPECULAR, table_face_dif); 
	glPushMatrix(); 
	glTranslatef(0.0f, 0.0f, 3.5f); 
	glScalef(5.0f, 4.0f, 1.0f); 
	glutSolidCube(1.0f); 
	glPopMatrix(); 

	// 画四个桌角
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

// 更新投影方式等
void updateView(int width, int height)
{
	glViewport(0, 0, width, height); 

	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity(); 
	GLfloat whRatio = (GLfloat) width/height; 
	// 透视投影还是正投影
	if(bPersp) 
		gluPerspective(45.0f, whRatio, 0.1f, 100.0f); 
	else
		glOrtho(-3, 3, -3, 3, -100, 100); 

	glMatrixMode(GL_MODELVIEW); 
}

// 窗口大小改变回调函数
void reshape(int width, int height)
{
	if(height == 0)
		height = 1; 
	wWidth = width; 
	wHeight = height; 

	updateView(wWidth, wHeight); 
}

// CPU闲置回调函数
void idle()
{
	glutPostRedisplay(); 
}

// 按键回调函数
void key(unsigned char k, int x, int y)
{
	switch(k)
	{
		case 27: // 退出
		case 'q': {exit(0); break; }
		// 透视投影和正投影的切换
		case 'p': {bPersp = !bPersp; break; }
		// 是否画线
		case 'o': {bWire = !bWire; break; }
		// 是否旋转
		case ' ': {bAnim = !bAnim; break; }

		case 'a': { // 相当于目标左移
			eye[0] += 0.2f; 
			center[0] += 0.2f; 
			break; 
		}
		case 'd': { // 相当于目标右移
			eye[0] -= 0.2f; 
			center[0] -= 0.2f; 
			break; 
		}
		case 'w': { // 相当于目标上移
			eye[1] -= 0.2f; 
			center[1] -= 0.2f; 
			break; 
		}
		case 's': { // 相当于目标下移
			eye[1] += 0.2f; 
			center[1] += 0.2f; 
			break; 
		}
		case 'z': { // 接近目标
			eye[2] -= 0.2f; 
			center[2] -= 0.2f; 
			break; 
		}
		case 'c': { // 远离目标
			eye[2] += 0.2f; 
			center[2] += 0.2f; 
			break; 
		}

		case 'j': { // 光源左移
			light_pos[0] -= 0.2f; 
			break; 
		}
		case 'l': { // 光源右移
			light_pos[0] += 0.2f; 
			break; 
		}
		case 'i': { // 光源上移
			light_pos[1] += 0.2f; 
			break; 
		}
		case 'k': { // 光源下移
			light_pos[1] -= 0.2f; 
			break; 
		}
		case 'n': { // 光源远离屏幕
			light_pos[2] -= 0.2f; 
			break; 
		}
		case 'm': { // 光源接近屏幕
			light_pos[2] += 0.2f; 
			break; 
		}
		case 'u': { // 切换光源颜色
			bLightColor = !bLightColor; 
			break; 
		}

		case 'f': { // 聚光灯朝向左移
			light1_dir[0] -= 1.0f; 
			break; 
		}
		case 'h': { // 聚光灯朝向右移
			light1_dir[0] += 1.0f; 
			break; 
		}
		case 't': { // 聚光灯朝向上移
			light1_dir[1] += 1.0f; 
			break; 
		}
		case 'g': { // 聚光灯朝向下移
			light1_dir[1] -= 1.0f; 
			break; 
		}
		case 'v': { // 聚光灯朝向远离屏幕
			light1_dir[2] -= 1.0f; 
			break; 
		}
		case 'b': { // 聚光灯朝向接近屏幕
			light1_dir[2] += 1.0f; 
			break; 
		}
		case 'r': { // 聚光灯的角度变大
			if(light1_angle < 3.14f) light1_angle += 3.14f / 16; 
			break; 
		}
		case 'y': { // 聚光灯的角度变小
			if(light1_angle > 3.14f / 16) light1_angle -= 3.14f / 16; 
			break; 
		}
	}
	updateView(wWidth, wHeight); 
}

// 鼠标按键处理函数 
void mouse(int button, int state, int x, int y)
{
	switch(button)
	{
		case GLUT_LEFT_BUTTON: {
			// 鼠标释放 
			if(state == GLUT_UP) {
				bMouseDown = false; 
			}
			break; 
		}
		default: break; 
	}
}

// 鼠标移动处理函数 
void onMouseMove(int x, int y)
{
	GLfloat xRange = PI / 180 * 46; 
	GLfloat yRange = PI / 180 * 46; 
	GLfloat cos_xViewAngle, cos_yViewAngle;
	GLfloat sin_xViewAngle, sin_yViewAngle; 
	
	// 第一次调用时，只记录x、y的坐标
	if(bMouseDown == false) {
		old_x = x; 
		old_y = y; 
		// 鼠标按下 
		bMouseDown = true; 
		return ; 
	}
	
	// 更新视角与坐标轴的夹角 
	xViewAngle = (GLfloat) (x - old_x) / wWidth * xRange + xViewAngle; 
	yViewAngle = (GLfloat) (y - old_y) / wHeight * yRange + yViewAngle; 
//	if(xViewAngle < 0) xViewAngle += 2*PI; 
//	else if(xViewAngle > 2*PI) xViewAngle -= 2*PI; 
	if(yViewAngle < 0) yViewAngle = 0; 
	else if(yViewAngle > PI) yViewAngle = PI; 
	// 限制场景在屏幕范围内 
//	if(xViewAngle < 3*PI/8) xViewAngle = 3*PI/8; 
//	else if(xViewAngle > 5*PI/8) xViewAngle = 5*PI/8; 
//	if(yViewAngle < 3*PI/8) yViewAngle = 3*PI/8; 
//	else if(yViewAngle > 5*PI/8) yViewAngle = 5*PI/8; 
	cos_xViewAngle = cos(xViewAngle); 
	cos_yViewAngle = cos(yViewAngle); 
	sin_xViewAngle = sin(xViewAngle); 
	sin_yViewAngle = abs(sin(yViewAngle)); 
	// 更新观察点坐标
	// center[0] = eye[0] - r * cos_xViewAngle; 
	center[0] = eye[0] - r * cos_xViewAngle * sin_yViewAngle; 
	center[1] = eye[1] + r * cos_yViewAngle; 
	// center[2] = eye[2] - r * sqrt(1 - cos_xViewAngle * cos_xViewAngle - cos_yViewAngle * cos_yViewAngle); 
	center[2] = eye[2] - r * sin_xViewAngle * sin_yViewAngle; 

	// fprintf(stderr, "%lf %lf\n", xViewAngle, yViewAngle); 
	// fprintf(stderr, "%d %d %d %d\n", old_x, x, old_y, y); 
	old_x = x; 
	old_y = y; 
	// fprintf(stderr, "%lf %lf %lf\n", center[0], center[1], center[2]); 
}

// 画图回调函数
void redraw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	glLoadIdentity(); 
	// 设定视点、观察坐标和观察正方向
	gluLookAt(eye[0], eye[1], eye[2], 
		center[0], center[1], center[2], 
		0, 1, 0); 

	if(bWire) // 是否画线
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); 
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); 

	// 消去背面
	glFrontFace(GL_CCW); 
	glEnable(GL_CULL_FACE); 
	glCullFace(GL_BACK); 
	// 开启消影
	glDepthFunc(GL_LESS); 
	glEnable(GL_DEPTH_TEST); 
	// 开启光照
	glEnable(GL_LIGHTING); 
	GLfloat white[] = {1.0f, 1.0f, 1.0f, 1.0f}; 
	GLfloat blue[] = {0.0f, 0.0f, 1.0f, 1.0f}; 
	GLfloat red[] = {1.0f, 0.0f, 0.0f, 1.0f}; 
	GLfloat black[] = {0.0f, 0.0f, 0.0f, 1.0f}; 
	if(bLightColor) // 切换光源颜色
		light_color = red; 
	else
		light_color = white; 
	// 设置光源light0
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos); 
	glLightfv(GL_LIGHT0, GL_AMBIENT, black); 
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_color); 
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_color); 
	glEnable(GL_LIGHT0); 

	// 设置光源light1成聚光灯
	glLightfv(GL_LIGHT1, GL_POSITION, light1_pos); 
	glLightfv(GL_LIGHT1, GL_AMBIENT, black); 
	glLightfv(GL_LIGHT1, GL_DIFFUSE, blue); 
	glLightfv(GL_LIGHT1, GL_SPECULAR, blue); 
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, light1_angle); 
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, light1_dir); 
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 6.0f); 
	glEnable(GL_LIGHT1); 

	// 旋转已旋转的角度，并画图
	glRotatef(fRotate, 0, 1, 0); 
	glRotatef(-90, 1, 0, 0); 
	glScalef(0.2f, 0.2f, 0.2f); 
	Draw_Triangle(); 

	// 如果旋转，则已旋转的角度增加
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
	glutMouseFunc(mouse); 
	glutMotionFunc(onMouseMove); 
	glutIdleFunc(idle); 

	glutMainLoop(); 
	return 0; 
}
