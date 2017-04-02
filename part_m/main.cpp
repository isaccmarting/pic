#include <stdio.h>
#include "GLee.h"
#include <GL/glut.h>

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    if( GLEE_ARB_window_pos ) { // 如果支持GL_ARB_window_pos
                                 // 则使用glWindowPos2iARB函数，指定绘制位置
        printf("支持GL_ARB_window_pos\n");
        printf("使用glWindowPos函数\n");
        glWindowPos2iARB(100, 100);
    } else {                     // 如果不支持GL_ARB_window_pos
                                 // 则只能使用glRasterPos*系列函数
                                 // 先计算出一个经过变换后能够得到
                                 //    (100, 100)的坐标(x, y, z)
                                 // 然后调用glRasterPos3d(x, y, z);
        GLint viewport[4];
        GLdouble modelview[16], projection[16];
        GLdouble x, y, z;

        printf("不支持GL_ARB_window_pos\n");
        printf("使用glRasterPos函数\n");

        glGetIntegerv(GL_VIEWPORT, viewport);
        glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
        glGetDoublev(GL_PROJECTION_MATRIX, projection);
        gluUnProject(100, 100, 0.5, modelview, projection, viewport,
            &x, &y, &z);
        glRasterPos3d(x, y, z);
     }

     {  // 绘制一个5*5的像素块
        GLubyte pixels[5][5][4];
        // 把像素中的所有像素都设置为红色
        int i, j;
        for(i=0; i<5; ++i)
            for(j=0; j<5; ++j) {
                 pixels[i][j][0] = 255;  // red
                 pixels[i][j][1] = 0;    // green
                 pixels[i][j][2] = 0;    // blue
                 pixels[i][j][3] = 255;  // alpha
             }
        glDrawPixels(5, 5, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
     }

     glutSwapBuffers();
}

int main(int argc, char* argv[]) {
     glutInit(&argc, argv);
     glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
     glutInitWindowPosition(100, 100);
     glutInitWindowSize(512, 512);
     glutCreateWindow("OpenGL");
     glutDisplayFunc(&display);
     glutMainLoop();
}
