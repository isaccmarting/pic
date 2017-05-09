#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "GLee.h"
#include <GL/glut.h>

// bmp图片标志
#define BITMAP_ID 0x4D42
// 自定义纹理的宽和高
#define CUSTOM_TEX_WIDTH 64
#define CUSTOM_TEX_HEIGHT 64

// 茶壶和桌子已旋转的角度
GLfloat fRotate; 
// 视点坐标
GLfloat eye[] = {0.0f, 0.0f, 8.0f}; 
// 观察坐标
GLfloat center[] = {0.0f, 0.0f, 0.0f}; 

// 纹理列表
GLuint texture[4]; 
// 是否用茶壶的自定义纹理
bool bTeapotCustomTex = false; 
// 是否用桌子的混合纹理
bool bTablePlusTex = false; 

// 是否透视
bool bPersp = false; 
// 是否旋转
bool bAnim = false; 
// 是否画线
bool bWire = false; 

GLint wWidth = 0, wHeight = 0; 

// 加载一个BMP图片
// 输入文件名和保存图片信息的地址
// 返回图片的bitmap信息
unsigned char *LoadBitmapFile(char *filename, BITMAPINFOHEADER *bitmapInfoHeader)
{
	FILE *filePtr; 
	BITMAPFILEHEADER bitmapFileHeader; 
	unsigned char *bitmapImage; 
	int imageIdx = 0; 
	unsigned char tempRGB; 

	filePtr = fopen(filename, "rb"); 
	if(filePtr == NULL) {printf("No %s file!\n"); exit(1); } 
	// 读取图片文件头
	fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, filePtr); 
	if(bitmapFileHeader.bfType != BITMAP_ID) {
		fprintf(stderr, "Error in LoadBitmapFile: the file is not a bitmap file\n"); 
		exit(1); 
	}
	// 读取图片基本信息
	fread(bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, filePtr); 
	fseek(filePtr, bitmapFileHeader.bfOffBits, SEEK_SET); 
	bitmapImage = (unsigned char*) malloc(sizeof(char) * bitmapInfoHeader -> biSizeImage); // new unsigned char[bitmapInfoHeader -> biSizeImage]; 
	if(!bitmapImage) {
		fprintf(stderr, "Error in LoadBitmapFile: memory error\n"); 
		exit(1); 
	}
	// 读取图片bitmap
	fread(bitmapImage, 1, bitmapInfoHeader -> biSizeImage, filePtr); 
	if(bitmapImage == NULL) {
		fprintf(stderr, "Error in LoadBitmapFile: memory error\n"); 
		exit(1); 
	}

	// 交换红色和蓝色位置，BGR -> RGB
	for(imageIdx = 0; imageIdx < bitmapInfoHeader -> biSizeImage; imageIdx += 3) {
		tempRGB = bitmapImage[imageIdx]; 
		bitmapImage[imageIdx] = bitmapImage[imageIdx + 2]; 
		bitmapImage[imageIdx + 2] = tempRGB; 
	}
	fclose(filePtr); 
	return bitmapImage; 
}

// 加载纹理到指定纹理位置
// 输入纹理列表中的序号和文件名
void TexLoad(int i, char *filename)
{
	BITMAPINFOHEADER bitmapInfoHeader; 
	unsigned char *bitmapData; 

	// 读取图片的bitmap
	bitmapData = LoadBitmapFile(filename, &bitmapInfoHeader); 
	// 载入图片纹理
	glBindTexture(GL_TEXTURE_2D, texture[i]); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); 
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 
		bitmapInfoHeader.biWidth, bitmapInfoHeader.biHeight, 0, 
		GL_RGB, GL_UNSIGNED_BYTE, bitmapData); 
}

// 初始化纹理
void InitTex()
{
	unsigned char customImage[CUSTOM_TEX_HEIGHT][CUSTOM_TEX_WIDTH][3]; 
	int i, j; 
	char *teapotPic, *tablePic, *tablePic_Plus; 
	teapotPic = (char*) "Monet.bmp"; 
	tablePic = (char*) "Crack.bmp"; 
	tablePic_Plus = (char*) "Spot.bmp"; 
	// 生成纹理列表
	glGenTextures(4, texture); 
	// 分别加载这些图片的纹理
	TexLoad(0, teapotPic); 
	TexLoad(1, tablePic); 
	TexLoad(3, tablePic_Plus); 

	// 生成自定义纹理
	for(i = 0; i < CUSTOM_TEX_HEIGHT; i++)
		for(j = 0; j < CUSTOM_TEX_WIDTH; j++)
		{
			// 根据位置计算这个位置是红色还是黑色
			customImage[i][j][0] = (!((i & 4) ^ (j & 4))) * 255; 
			customImage[i][j][1] = 0; 
			customImage[i][j][2] = 0; 
		}
	glBindTexture(GL_TEXTURE_2D, texture[2]); 
	// 定义存储的对齐方式
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); 
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 
		CUSTOM_TEX_WIDTH, CUSTOM_TEX_HEIGHT, 0, 
		GL_RGB, GL_UNSIGNED_BYTE, customImage); 
}

// 画一个有纹理的立方体
void Draw_Tex_Cube(GLfloat ratio)
{
	GLfloat x, y, z; 
	x=y=z = ratio/2; 
	// 定义立方体的每个点坐标
	// up:up, dn:down; fw:forward, bk:back; lf:left, rt:right; 
	GLfloat A[] = {+x, -y, -z}, // DnFwRt 
			B[] = {-x, -y, -z}, // DnFwLf 
			C[] = {-x, +y, -z}, // DnBkLf 
			D[] = {+x, +y, -z}, // DnBkRt 
			E[] = {+x, -y, +z}, // UpFwRt 
			F[] = {-x, -y, +z}, // UpFwLf 
			G[] = {-x, +y, +z}, // UpBkLf 
			H[] = {+x, +y, +z}; // UpBkRt 
	// 定义立方体的每个面
	GLfloat *vertices[][4] = {
		{A, B, C, D}, 
		{C, B, F, G}, 
		{B, A, E, F}, 
		{A, D, H, E}, 
		{D, C, G, H}, 
		{F, E, H, G} 
	}; 
	GLfloat texCoord[][2] = {
		{0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f}
	}; 
	int i, j; 

	// 画出带有纹理的立方体
	glBegin(GL_QUADS); 
	for(i = 0; i < 6; i++) 
		for(j = 0; j < 4; j++)
		{
			if(!bTablePlusTex) { // 只有一层纹理
				glTexCoord2fv(texCoord[j]); 
			}
			else { // 有两层纹理
				glMultiTexCoord2fvARB(GL_TEXTURE0_ARB, texCoord[j]); 
				glMultiTexCoord2fvARB(GL_TEXTURE1_ARB, texCoord[j]); 
			}
			glVertex3fv(vertices[i][j]); 
		}
	glEnd(); 
}

// 画出有纹理的桌腿
void Draw_Tex_Leg()
{
	glScalef(1.0f, 1.0f, 3.0f); 
	// glutSolidCube(1.0f); 
	Draw_Tex_Cube(1.0f); 
}

// 画出整个场景
void Draw_Triangle()
{
	// 茶壶的材质信息
	GLfloat teapot_amb[] = {0.3f, 0.3f, 0.0f, 1.0f}; 
	GLfloat teapot_dif[] = {0.5f, 0.5f, 0.5f, 1.0f}; 
	GLfloat teapot_spe[] = {1.0f, 1.0f, 1.0f, 1.0f}; 
	
	// 画茶壶
	// 设置茶壶的材质
	glMaterialfv(GL_FRONT, GL_AMBIENT, teapot_amb); 
	glMaterialfv(GL_FRONT, GL_DIFFUSE, teapot_dif); 
	glMaterialfv(GL_FRONT, GL_SPECULAR, teapot_spe); 
	glMaterialf(GL_FRONT, GL_SHININESS, 60.0f); 
	glPushMatrix(); 
	glTranslatef(0.0f, 0.0f, 4.0f+1.0f); 
	glRotatef(90, 1, 0, 0); 
	// 激活并开启纹理
	glActiveTextureARB(GL_TEXTURE0_ARB); 
	glEnable(GL_TEXTURE_2D); 
	if(!bTeapotCustomTex) // 用图片纹理
		glBindTexture(GL_TEXTURE_2D, texture[0]); 
	else // 用自定义纹理
		glBindTexture(GL_TEXTURE_2D, texture[2]); 
	// 纹理和光照叠加
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); 
	GLfloat white[] = {1.0f, 1.0f, 1.0f, 1.0f}; 
	glTexEnvfv(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, white); 
	glutSolidTeapot(1.0f); 
	glDisable(GL_TEXTURE_2D); 
	glPopMatrix(); 

	// 画桌子
	// 设置第一层纹理，绑定桌子纹理图片
	glEnable(GL_TEXTURE_2D); 
	glBindTexture(GL_TEXTURE_2D, texture[1]); 
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL); 
	if(bTablePlusTex) { // 设置第二层纹理，绑定另一张图片
		glActiveTextureARB(GL_TEXTURE1_ARB); 
		glEnable(GL_TEXTURE_2D); 
		glBindTexture(GL_TEXTURE_2D, texture[3]); 
		// 使两张纹理可叠加
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); 
	}
	
	// 画桌面
	glPushMatrix(); 
	glTranslatef(0.0f, 0.0f, 3.5f); 
	glScalef(5.0f, 4.0f, 1.0f); 
	// glutSolidCube(1.0f); 
	Draw_Tex_Cube(1.0f); 
	glPopMatrix(); 

	// 画桌角
	glPushMatrix(); 
	glTranslatef(1.5f, 1.0f, 1.5f); 
	Draw_Tex_Leg(); 
	glPopMatrix(); 

	glPushMatrix(); 
	glTranslatef(-1.5f, 1.0f, 1.5f); 
	Draw_Tex_Leg(); 
	glPopMatrix(); 

	glPushMatrix(); 
	glTranslatef(-1.5f, -1.0f, 1.5f); 
	Draw_Tex_Leg(); 
	glPopMatrix(); 

	glPushMatrix(); 
	glTranslatef(1.5f, -1.0f, 1.5f); 
	Draw_Tex_Leg(); 
	glPopMatrix(); 

	// 关闭每层纹理
	glActiveTextureARB(GL_TEXTURE0_ARB); 
	glDisable(GL_TEXTURE_2D); 
	glActiveTextureARB(GL_TEXTURE1_ARB); 
	glDisable(GL_TEXTURE_2D); 
}

// 更新视图和投影
void updateView(int width, int height)
{
	glViewport(0, 0, width, height); 

	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity(); 
	GLfloat whRatio = (GLfloat) width / height; 
	if(bPersp)
		gluPerspective(45.0f, whRatio, 0.1f, 100.0f); 
	else
		glOrtho(-3, 3, -3, 3, -100, 100); 

	glMatrixMode(GL_MODELVIEW); 
}

// 窗口形状改变回调函数
void reshape(int width, int height)
{
	if(height == 0)
		height = 1; 

	wWidth = width; 
	wHeight = height; 

	updateView(width, height); 
}

// CPU闲置回调函数
void idle()
{
	glutPostRedisplay(); 
}

// 键盘回调函数
void key(unsigned char k, int x, int y)
{
	switch(k)
	{
		case 27: // 退出
		case 'q': {exit(0); break; }
		// 是否旋转
		case ' ': {bAnim = !bAnim; break; }
		// 是否画线
		case 'o': {bWire = !bWire; break; }
		// 是否透视投影
		case 'p': {bPersp = !bPersp; break; }

		case 'a': { // 物体左移
			eye[0] += 0.2f; 
			center[0] += 0.2f; 
			break; 
		}
		case 'd': { // 物体右移
			eye[0] -= 0.2f; 
			center[0] -= 0.2f; 
			break; 
		}
		case 'w': { // 物体上移
			eye[1] -= 0.2f; 
			center[1] -= 0.2f; 
			break; 
		}
		case 's': { // 物体下移
			eye[1] += 0.2f; 
			center[1] += 0.2f; 
			break; 
		}
		case 'z': { // 接近物体
			eye[2] -= 0.2f; 
			center[2] -= 0.2f; 
			break; 
		}
		case 'c': { // 远离物体
			eye[2] += 0.2f; 
			center[2] += 0.2f; 
			break; 
		}

		case 'i': { // 切换茶壶的纹理
			bTeapotCustomTex = !bTeapotCustomTex; 
			break; 
		}
		case 'k': { // 切换桌子的纹理
			bTablePlusTex = !bTablePlusTex; 
			break; 
		}
	}
	updateView(wWidth, wHeight); 
}

// 画图回调函数
void redraw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	glLoadIdentity(); 

	// 视点、观察坐标和观察正方向
	gluLookAt(eye[0], eye[1], eye[2], 
		center[0], center[1], center[2], 
		0, 1, 0); 

	if(bWire) // 画线
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); 
	else      // 画面
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); 

	// 开启消影
	glDepthFunc(GL_LESS); 
	glEnable(GL_DEPTH_TEST); 
	// 开启光源
	glEnable(GL_LIGHTING); 
	GLfloat white[] = {1.0f, 1.0f, 1.0f, 1.0f}; 
	GLfloat black[] = {0.0f, 0.0f, 0.0f, 1.0f}; 
	GLfloat light_pos[] = {5.0f, 5.0f, 5.0f, 1.0f}; 

	glLightfv(GL_LIGHT0, GL_POSITION, light_pos); 
	glLightfv(GL_LIGHT0, GL_AMBIENT, black); 
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white); 
	glLightfv(GL_LIGHT0, GL_SPECULAR, white); 
	glEnable(GL_LIGHT0); 

	// 画出场景
	glRotatef(fRotate, 0, 1, 0); 
	glRotatef(-90, 1, 0, 0); 
	glScalef(0.2f, 0.2f, 0.2f); 
	Draw_Triangle(); 

	// 是否旋转，以及改变已旋转角度
	if(bAnim) fRotate += 0.5f; 
	glutSwapBuffers(); 
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv); 
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE); 
	glutInitWindowSize(480, 480); 
	int windowHandler = glutCreateWindow("Simple GLUT App"); 

	glutDisplayFunc(redraw); 
	glutIdleFunc(idle); 
	glutReshapeFunc(reshape); 
	glutKeyboardFunc(key); 

	InitTex(); 
	glutMainLoop(); 
	return 0; 
}
