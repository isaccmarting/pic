#include <windows.h>
#include "Glee.h"
#include <GL/glut.h>

// ASCII�ַ��ܹ�ֻ��0��127��һ��128���ַ�
#define MAX_CHAR       128
#define FONT_SIZE       64
#define TEXTURE_SIZE    FONT_SIZE

void drawString(const char* str) {
    static int isFirstCall = 1;
    static GLuint lists;

    if( isFirstCall ) { // ����ǵ�һ�ε��ã�ִ�г�ʼ��
                        // Ϊÿһ��ASCII�ַ�����һ����ʾ�б�
        isFirstCall = 0;

        // ����MAX_CHAR����������ʾ�б���
        lists = glGenLists(MAX_CHAR);

        // ��ÿ���ַ��Ļ������װ����Ӧ����ʾ�б���
        wglUseFontBitmaps(wglGetCurrentDC(), 0, MAX_CHAR, lists);
    }
    // ����ÿ���ַ���Ӧ����ʾ�б�����ÿ���ַ�
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

    // �����ַ��ĸ���
    // �����˫�ֽ��ַ��ģ����������ַ����������ֽڲ���һ���ַ�
    // ����һ���ֽ���һ���ַ�
    len = 0;
    for(i=0; str[i]!='\0'; ++i)
    {
        if( IsDBCSLeadByte(str[i]) )
            ++i;
        ++len;
    }

    // ������ַ�ת��Ϊ���ַ�
    wstring = (wchar_t*)malloc((len+1) * sizeof(wchar_t));
    MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, str, -1, wstring, len);
    wstring[len] = L'\0';

    // �������ַ�
    for(i=0; i<len; ++i)
    {
        wglUseFontBitmapsW(hDC, wstring[i], 1, list);
        glCallList(list);
    }

    // ����������ʱ��Դ
    free(wstring);
    glDeleteLists(list, 1);
}

GLuint drawChar_To_Texture(const char* s) {
    wchar_t w;
    HDC hDC = wglGetCurrentDC();

    // ѡ�������ֺš���ɫ
    // ��ָ���������֣�����ϵͳ�ṩĬ������
    // ������ɫΪ��ɫ
    selectFont(FONT_SIZE, DEFAULT_CHARSET, "");
    glColor3f(1.0f, 1.0f, 1.0f);

    // ת��Ϊ���ַ�
    MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, s, 2, &w, 1);

    // ������Ƶ�λ��
    {
        int width, x, y;
        GetCharWidth32W(hDC, w, w, &width);    // ȡ���ַ��Ŀ��
        x = (TEXTURE_SIZE - width) / 2;
        y = FONT_SIZE / 8;
        glWindowPos2iARB(x, y); // һ����չ����
    }

    // �����ַ�
    // ����ǰӦ�ý����ֿ���Ӱ���ַ���ɫ��Ч���ر�
    // �Ա�֤�ܹ����Ƴ���ɫ���ַ�
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

    // �����ַ����ص�����
    // ע������ĸ�ʽ
    // ��ʹ��ͨ����GL_RGBA����ʹ��GL_LUMINANCE4
    // ��Ϊ�ַ�����ֻ��һ����ɫ��ʹ��GL_RGBA�˷��˴洢�ռ�
    // GL_RGBA����ռ16λ����32λ����GL_LUMINANCE4ֻռ4λ
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

    drawChar_To_Texture("��"); 

    glutSwapBuffers();
}

int main(int argc, char *argv[])

{

     glutInit(&argc, argv);

     glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

     glutInitWindowPosition(100, 100);

     glutInitWindowSize(400, 400);

     glutCreateWindow("OpenGL����");

     glutDisplayFunc(&display);

     glutMainLoop();

     return 0;

}
