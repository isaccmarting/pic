#include <windows.h>
#include <GL/glut.h>

// ASCII�ַ��ܹ�ֻ��0��127��һ��128���ַ�
#define MAX_CHAR       128


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

void display(void) {
    selectFont(48, ANSI_CHARSET, "Comic Sans MS");

    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0f, 0.0f, 0.0f);
    glRasterPos2f(0.0f, 0.0f);
    drawString("Hello, World!");

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
