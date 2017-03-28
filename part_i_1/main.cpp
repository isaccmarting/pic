#include <stdio.h>
#include <stdlib.h>
#include <gl/glut.h>

#define WindowWidth   400
#define WindowHeight 400

/* 函数grab
* 抓取窗口中的像素
* 假设窗口宽度为WindowWidth，高度为WindowHeight
*/
#define BMP_Header_Length 54
void grab(void)
{
     FILE*     pDummyFile;
     FILE*     pWritingFile;
     GLubyte* pPixelData;
     GLubyte   BMP_Header[BMP_Header_Length];
     GLint     i, j;
     GLint     PixelDataLength;

     // 计算像素数据的实际长度
     i = WindowWidth * 3;    // 得到每一行的像素数据长度
     while( i%4 != 0 )       // 补充数据，直到i是的倍数
         ++i;                // 本来还有更快的算法，
                            // 但这里仅追求直观，对速度没有太高要求
     PixelDataLength = i * WindowHeight;

     // 分配内存和打开文件
     pPixelData = (GLubyte*)malloc(PixelDataLength);
     if( pPixelData == 0 )
         exit(0);

     pDummyFile = fopen("dummy.bmp", "rb");
     if( pDummyFile == 0 )
         exit(0);

     pWritingFile = fopen("grab.bmp", "wb");
     if( pWritingFile == 0 )
         exit(0);

     // 读取像素
     glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
     glReadPixels(0, 0, WindowWidth, WindowHeight,
         GL_BGR_EXT, GL_UNSIGNED_BYTE, pPixelData);

     // 把dummy.bmp的文件头复制为新文件的文件头
     fread(BMP_Header, sizeof(BMP_Header), 1, pDummyFile);
     fwrite(BMP_Header, sizeof(BMP_Header), 1, pWritingFile);
     fseek(pWritingFile, 0x0012, SEEK_SET);
     i = WindowWidth;
     j = WindowHeight;
     fwrite(&i, sizeof(i), 1, pWritingFile);
     fwrite(&j, sizeof(j), 1, pWritingFile);

     // 写入像素数据
     fseek(pWritingFile, 0, SEEK_END);
     fwrite(pPixelData, PixelDataLength, 1, pWritingFile);

     // 释放内存和关闭文件
     fclose(pDummyFile);
     fclose(pWritingFile);
     free(pPixelData);
}

void myDisplay(void)
{
     glClear(GL_COLOR_BUFFER_BIT);

     glEnable(GL_BLEND);
     glBlendFunc(GL_ONE, GL_ZERO);
	 // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	 // glBlendFunc(GL_ONE, GL_ONE);

     glColor4f(1, 0, 0, 0.5);
     glRectf(-1, -1, 0.5, 0.5);
     glColor4f(0, 1, 0, 0.5);
     glRectf(-0.5, -0.5, 1, 1);

     grab(); 
	 glutSwapBuffers();
}

int main(int argc, char* argv[])
{
     glutInit(&argc, argv);
     glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
     glutInitWindowPosition(200, 200);
     glutInitWindowSize(WindowWidth, WindowHeight);
     glutCreateWindow("OpenGL 窗口");
     glutDisplayFunc(&myDisplay);
     glutMainLoop();
     return 0;
}

