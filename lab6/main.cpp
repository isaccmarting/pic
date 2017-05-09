#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "GLee.h"
#include <GL/glut.h>

#define BITMAP_ID 0x4D42
#define CUSTOM_TEX_WIDTH 64
#define CUSTOM_TEX_HEIGHT 64

GLfloat fRotate; 
GLfloat eye[] = {0.0f, 0.0f, 8.0f}; 
GLfloat center[] = {0.0f, 0.0f, 0.0f}; 

GLuint texture[4]; 
bool bTeapotCustomTex = false; 
bool bTablePlusTex = false; 

bool bPersp = false; 
bool bAnim = false; 
bool bWire = false; 

GLint wWidth = 0, wHeight = 0; 

unsigned char *LoadBitmapFile(char *filename, BITMAPINFOHEADER *bitmapInfoHeader)
{
	FILE *filePtr; 
	BITMAPFILEHEADER bitmapFileHeader; 
	unsigned char *bitmapImage; 
	int imageIdx = 0; 
	unsigned char tempRGB; 

	filePtr = fopen(filename, "rb"); 
	if(filePtr == NULL) {printf("No %s file!\n"); exit(1); } 
	fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, filePtr); 
	if(bitmapFileHeader.bfType != BITMAP_ID) {
		fprintf(stderr, "Error in LoadBitmapFile: the file is not a bitmap file\n"); 
		exit(1); 
	}
	fread(bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, filePtr); 
	fseek(filePtr, bitmapFileHeader.bfOffBits, SEEK_SET); 
	bitmapImage = (unsigned char*) malloc(sizeof(char) * bitmapInfoHeader -> biSizeImage); // new unsigned char[bitmapInfoHeader -> biSizeImage]; 
	if(!bitmapImage) {
		fprintf(stderr, "Error in LoadBitmapFile: memory error\n"); 
		exit(1); 
	}
	fread(bitmapImage, 1, bitmapInfoHeader -> biSizeImage, filePtr); 
	if(bitmapImage == NULL) {
		fprintf(stderr, "Error in LoadBitmapFile: memory error\n"); 
		exit(1); 
	}

	for(imageIdx = 0; imageIdx < bitmapInfoHeader -> biSizeImage; imageIdx += 3) {
		tempRGB = bitmapImage[imageIdx]; 
		bitmapImage[imageIdx] = bitmapImage[imageIdx + 2]; 
		bitmapImage[imageIdx + 2] = tempRGB; 
	}
	fclose(filePtr); 
	return bitmapImage; 
}

void TexLoad(int i, char *filename)
{
	BITMAPINFOHEADER bitmapInfoHeader; 
	unsigned char *bitmapData; 

	bitmapData = LoadBitmapFile(filename, &bitmapInfoHeader); 
	glBindTexture(GL_TEXTURE_2D, texture[i]); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); 
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 
		bitmapInfoHeader.biWidth, bitmapInfoHeader.biHeight, 0, 
		GL_RGB, GL_UNSIGNED_BYTE, bitmapData); 
}

void InitTex()
{
	unsigned char customImage[CUSTOM_TEX_HEIGHT][CUSTOM_TEX_WIDTH][3]; 
	int i, j; 
	char *teapotPic, *tablePic, *tablePic_Plus; 
	teapotPic = (char*) "Monet.bmp"; 
	tablePic = (char*) "Crack.bmp"; 
	tablePic_Plus = (char*) "Spot.bmp"; 
	glGenTextures(4, texture); 
	TexLoad(0, teapotPic); 
	TexLoad(1, tablePic); 
	TexLoad(3, tablePic_Plus); 

	// 
	for(i = 0; i < CUSTOM_TEX_HEIGHT; i++)
		for(j = 0; j < CUSTOM_TEX_WIDTH; j++)
		{
			customImage[i][j][0] = (!((i & 4) ^ (j & 4))) * 255; 
			customImage[i][j][1] = 0; 
			customImage[i][j][2] = 0; 
		}
	glBindTexture(GL_TEXTURE_2D, texture[2]); 
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); 
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 
		CUSTOM_TEX_WIDTH, CUSTOM_TEX_HEIGHT, 0, 
		GL_RGB, GL_UNSIGNED_BYTE, customImage); 
}

void Draw_Tex_Cube(GLfloat ratio)
{
	GLfloat x, y, z; 
	x=y=z = ratio/2; 
	// up, dn; fw, bk; lf, rt; 
	GLfloat A[] = {+x, -y, -z}, // DnFwRt 
			B[] = {-x, -y, -z}, // DnFwLf 
			C[] = {-x, +y, -z}, // DnBkLf 
			D[] = {+x, +y, -z}, // DnBkRt 
			E[] = {+x, -y, +z}, // UpFwRt 
			F[] = {-x, -y, +z}, // UpFwLf 
			G[] = {-x, +y, +z}, // UpBkLf 
			H[] = {+x, +y, +z}; // UpBkRt 
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

	glBegin(GL_QUADS); 
	for(i = 0; i < 6; i++) 
		for(j = 0; j < 4; j++)
		{
			if(!bTablePlusTex) {
				glTexCoord2fv(texCoord[j]); 
			}
			else {
				glMultiTexCoord2fvARB(GL_TEXTURE0_ARB, texCoord[j]); 
				glMultiTexCoord2fvARB(GL_TEXTURE1_ARB, texCoord[j]); 
			}
			glVertex3fv(vertices[i][j]); 
		}
	glEnd(); 
}

void Draw_Tex_Leg()
{
	glScalef(1.0f, 1.0f, 3.0f); 
	// glutSolidCube(1.0f); 
	Draw_Tex_Cube(1.0f); 
}

void Draw_Triangle()
{
	// 茶壶的材质信息
	GLfloat teapot_amb[] = {0.3f, 0.3f, 0.0f, 1.0f}; 
	GLfloat teapot_dif[] = {0.5f, 0.5f, 0.5f, 1.0f}; 
	GLfloat teapot_spe[] = {1.0f, 1.0f, 1.0f, 1.0f}; 
	
	glMaterialfv(GL_FRONT, GL_AMBIENT, teapot_amb); 
	glMaterialfv(GL_FRONT, GL_DIFFUSE, teapot_dif); 
	glMaterialfv(GL_FRONT, GL_SPECULAR, teapot_spe); 
	glMaterialf(GL_FRONT, GL_SHININESS, 60.0f); 
	glPushMatrix(); 
	glTranslatef(0.0f, 0.0f, 4.0f+1.0f); 
	glRotatef(90, 1, 0, 0); 
	glActiveTextureARB(GL_TEXTURE0_ARB); 
	glEnable(GL_TEXTURE_2D); 
	if(!bTeapotCustomTex)
		glBindTexture(GL_TEXTURE_2D, texture[0]); 
	else
		glBindTexture(GL_TEXTURE_2D, texture[2]); 
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); 
	GLfloat white[] = {1.0f, 1.0f, 1.0f, 1.0f}; 
	glTexEnvfv(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, white); 
	glutSolidTeapot(1.0f); 
	glDisable(GL_TEXTURE_2D); 
	glPopMatrix(); 

	glEnable(GL_TEXTURE_2D); 
	glBindTexture(GL_TEXTURE_2D, texture[1]); 
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL); 
	if(bTablePlusTex) {
		glActiveTextureARB(GL_TEXTURE1_ARB); 
		glEnable(GL_TEXTURE_2D); 
		glBindTexture(GL_TEXTURE_2D, texture[3]); 
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); 
	}
	
	glPushMatrix(); 
	glTranslatef(0.0f, 0.0f, 3.5f); 
	glScalef(5.0f, 4.0f, 1.0f); 
	// glutSolidCube(1.0f); 
	Draw_Tex_Cube(1.0f); 
	glPopMatrix(); 

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

	glActiveTextureARB(GL_TEXTURE0_ARB); 
	glDisable(GL_TEXTURE_2D); 
	glActiveTextureARB(GL_TEXTURE1_ARB); 
	glDisable(GL_TEXTURE_2D); 
}

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

void reshape(int width, int height)
{
	if(height == 0)
		height = 1; 

	wWidth = width; 
	wHeight = height; 

	updateView(width, height); 
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
		case ' ': {bAnim = !bAnim; break; }
		case 'o': {bWire = !bWire; break; }
		case 'p': {bPersp = !bPersp; break; }

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

		case 'i': {
			bTeapotCustomTex = !bTeapotCustomTex; 
			break; 
		}
		case 'k': {
			bTablePlusTex = !bTablePlusTex; 
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

	glDepthFunc(GL_LESS); 
	glEnable(GL_DEPTH_TEST); 
	glEnable(GL_LIGHTING); 
	GLfloat white[] = {1.0f, 1.0f, 1.0f, 1.0f}; 
	GLfloat black[] = {0.0f, 0.0f, 0.0f, 1.0f}; 
	GLfloat light_pos[] = {5.0f, 5.0f, 5.0f, 1.0f}; 

	glLightfv(GL_LIGHT0, GL_POSITION, light_pos); 
	glLightfv(GL_LIGHT0, GL_AMBIENT, black); 
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white); 
	glLightfv(GL_LIGHT0, GL_SPECULAR, white); 
	glEnable(GL_LIGHT0); 

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
	int windowHandler = glutCreateWindow("Simple GLUT App"); 

	glutDisplayFunc(redraw); 
	glutIdleFunc(idle); 
	glutReshapeFunc(reshape); 
	glutKeyboardFunc(key); 

	InitTex(); 
	glutMainLoop(); 
	return 0; 
}
