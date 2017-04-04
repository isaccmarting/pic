#include <windows.h>
#include "Glee.h"
#include <GL/glut.h>

// ASCII字符总共只有0到127，一共128种字符
#define MAX_CHAR       128
#define FONT_SIZE       64
#define TEXTURE_SIZE    FONT_SIZE

void drawString(const char* str) {
    static int isFirstCall = 1;
    static GLuint lists;

    if( isFirstCall ) { // 如果是第一次调用，执行初始化
                        // 为每一个ASCII字符产生一个显示列表
        isFirstCall = 0;

        // 申请MAX_CHAR个连续的显示列表编号
        lists = glGenLists(MAX_CHAR);

        // 把每个字符的绘制命令都装到对应的显示列表中
        wglUseFontBitmaps(wglGetCurrentDC(), 0, MAX_CHAR, lists);
    }
    // 调用每个字符对应的显示列表，绘制每个字符
    for(; *str!='\0'; ++str)
        glCallList(lists + *str);
}

void selectFont(int size, int charset, const char* face) {
    HFONT hFont = CreateFontA(size, 0, 0, 0, FW_MEDIUM, 0, 0, 0,
        charset, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, face);
    HFONT hOldFont = (HFONT)SelectObject(wglGetCurrentDC(), hFont);
    DeleteObject(hOldFont);
}

void drawCNString(const char* str) {
    int len, i;
    wchar_t* wstring;
    HDC hDC = wglGetCurrentDC();
    GLuint list = glGenLists(1);

    // 计算字符的个数
    // 如果是双字节字符的（比如中文字符），两个字节才算一个字符
    // 否则一个字节算一个字符
    len = 0;
    for(i=0; str[i]!='\0'; ++i)
    {
        if( IsDBCSLeadByte(str[i]) )
            ++i;
        ++len;
    }

    // 将混合字符转化为宽字符
    wstring = (wchar_t*)malloc((len+1) * sizeof(wchar_t));
    MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, str, -1, wstring, len);
    wstring[len] = L'\0';

    // 逐个输出字符
    for(i=0; i<len; ++i)
    {
        wglUseFontBitmapsW(hDC, wstring[i], 1, list);
        glCallList(list);
    }

    // 回收所有临时资源
    free(wstring);
    glDeleteLists(list, 1);
}

GLuint drawChar_To_Texture(const char* s) {
    wchar_t w;
    HDC hDC = wglGetCurrentDC();

    // 选择字体字号、颜色
    // 不指定字体名字，操作系统提供默认字体
    // 设置颜色为白色
    selectFont(FONT_SIZE, DEFAULT_CHARSET, "");
    glColor3f(1.0f, 1.0f, 1.0f);

    // 转化为宽字符
    MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, s, 2, &w, 1);

    // 计算绘制的位置
    {
        int width, x, y;
        GetCharWidth32W(hDC, w, w, &width);    // 取得字符的宽度
        x = (TEXTURE_SIZE - width) / 2;
        y = FONT_SIZE / 8;
        glWindowPos2iARB(x, y); // 一个扩展函数
    }

    // 绘制字符
    // 绘制前应该将各种可能影响字符颜色的效果关闭
    // 以保证能够绘制出白色的字符
    {
        GLuint list = glGenLists(1);

        glDisable(GL_DEPTH_TEST);
        glDisable(GL_LIGHTING);
        glDisable(GL_FOG);
        glDisable(GL_TEXTURE_2D);

        wglUseFontBitmaps(hDC, w, 1, list);
        glCallList(list);
        glDeleteLists(list, 1);
    }

    // 复制字符像素到纹理
    // 注意纹理的格式
    // 不使用通常的GL_RGBA，而使用GL_LUMINANCE4
    // 因为字符本来只有一种颜色，使用GL_RGBA浪费了存储空间
    // GL_RGBA可能占16位或者32位，而GL_LUMINANCE4只占4位
    {
        GLuint texID;
        glGenTextures(1, &texID);
        glBindTexture(GL_TEXTURE_2D, texID);
        glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE4,
            0, 0, TEXTURE_SIZE, TEXTURE_SIZE, 0);
        glTexParameteri(GL_TEXTURE_2D,
            GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,
            GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        return texID;
    }
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    drawChar_To_Texture("我"); 

    glutSwapBuffers();
}

int main(int argc, char *argv[])

{

     glutInit(&argc, argv);

     glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

     glutInitWindowPosition(100, 100);

     glutInitWindowSize(400, 400);

     glutCreateWindow("OpenGL程序");

     glutDisplayFunc(&display);

     glutMainLoop();

     return 0;

}
