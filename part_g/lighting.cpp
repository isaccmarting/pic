#include <windows.h>
#include <math.h>
#include <gl/glut.h>

#define WIDTH 400
#define HEIGHT 400

// #define ColoredVertex(c, v) do{ glColor3fv(c); glVertex3fv(v); }while(0)

GLfloat angle = 0.0f;

void setNormal(GLfloat* Point1, GLfloat* Point2, GLfloat* Point3)
{
     GLfloat normal[3];
     int i;
     for(i=0; i<3; ++i)
         normal[i] = (Point1[i]+Point2[i]+Point3[i]) / 3;
     glNormal3fv(normal);
}

void myDisplay(void)
{
     static int list1 = 0, list2;
	 if(list1 == 0)
	 {
		 list1 = glGenLists(1);
         glNewList(list1, GL_COMPILE);
		 // 定义太阳光源，它是一种白色的光源
		 {
			 GLfloat sun_light_position[] = {1.0f, 0.0f, 0.0f, 1.0f};
			 GLfloat sun_light_ambient[]   = {0.0f, 0.0f, 0.0f, 1.0f};
			 GLfloat sun_light_diffuse[]   = {1.0f, 1.0f, 1.0f, 1.0f};
			 GLfloat sun_light_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};

			 glLightfv(GL_LIGHT0, GL_POSITION, sun_light_position);
			 glLightfv(GL_LIGHT0, GL_AMBIENT,   sun_light_ambient);
			 glLightfv(GL_LIGHT0, GL_DIFFUSE,   sun_light_diffuse);
			 glLightfv(GL_LIGHT0, GL_SPECULAR, sun_light_specular);

			 glEnable(GL_LIGHT0);
			 glEnable(GL_LIGHTING);
	     }
		 glEndList();
	 }
     if( list2 == 0 )
     {
         // 如果显示列表不存在，则创建
        /* GLfloat
             PointA[] = {-0.5, -5*sqrt(5)/48,   sqrt(3)/6},
             PointB[] = { 0.5, -5*sqrt(5)/48,   sqrt(3)/6},
             PointC[] = {    0, -5*sqrt(5)/48, -sqrt(3)/3},
             PointD[] = {    0, 11*sqrt(6)/48,           0}; */
        // 2007年4月27日修改
         GLfloat
             PointA[] = { 0.5f, -sqrt(6.0f)/12, -sqrt(3.0f)/6},
             PointB[] = {-0.5f, -sqrt(6.0f)/12, -sqrt(3.0f)/6},
             PointC[] = { 0.0f, -sqrt(6.0f)/12,   sqrt(3.0f)/3},
             PointD[] = { 0.0f,    sqrt(6.0f)/4,              0};
         GLfloat
             ColorR[] = {1, 0, 0},
             ColorG[] = {0, 1, 0},
             ColorB[] = {0, 0, 1},
             ColorY[] = {1, 1, 0};

         list2 = glGenLists(1);
         glNewList(list2, GL_COMPILE);
		 // 定义太阳的材质并绘制太阳
		 {
			 GLfloat tri_mat_ambient[]   = {0.0f, 0.0f, 0.0f, 1.0f};
			 GLfloat tri_mat_diffuse[]   = {0.0f, 0.0f, 0.0f, 1.0f};
			 GLfloat tri_mat_specular[] = {0.0f, 0.0f, 0.0f, 1.0f};
			 GLfloat tri_mat_emission[] = {0.5f, 0.0f, 0.0f, 1.0f};
			 GLfloat tri_mat_shininess   = 0.0f;

			 glMaterialfv(GL_FRONT, GL_AMBIENT,    tri_mat_ambient);
			 glMaterialfv(GL_FRONT, GL_DIFFUSE,    tri_mat_diffuse);
			 glMaterialfv(GL_FRONT, GL_SPECULAR,   tri_mat_specular);
			 glMaterialfv(GL_FRONT, GL_EMISSION,   tri_mat_emission);
			 glMaterialf (GL_FRONT, GL_SHININESS, tri_mat_shininess);
		 }

         glBegin(GL_TRIANGLES);
         // 平面ABC
		 glVertex3fv(PointA);
		 glVertex3fv(PointB);
		 glVertex3fv(PointC);
		 setNormal(PointA, PointB, PointC); 
         // 平面ACD
         glVertex3fv(PointA);
		 glVertex3fv(PointC);
		 glVertex3fv(PointD);
		 setNormal(PointA, PointC, PointD); 
         // 平面CBD
         glVertex3fv(PointC);
		 glVertex3fv(PointB);
		 glVertex3fv(PointD);
		 setNormal(PointC, PointB, PointD); 
         // 平面BAD
         glVertex3fv(PointB);
		 glVertex3fv(PointA);
		 glVertex3fv(PointD);
		 setNormal(PointB, PointA, PointD); 
         glEnd();
         glEndList();

         glEnable(GL_DEPTH_TEST);
     }
     // 已经创建了显示列表，在每次绘制正四面体时将调用它
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
     glPushMatrix();
	 glCallList(list1);
     glRotatef(angle, 1, 0.5, 0);
	 glCallList(list2);
     glPopMatrix();
     glutSwapBuffers();
}

void myIdle(void)
{
     ++angle;
     if( angle >= 360.0f )
         angle = 0.0f;
	 Sleep(100); 
     myDisplay();
}

int main(int argc, char* argv[])
{
     glutInit(&argc, argv);
     glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
     glutInitWindowPosition(200, 200);
     glutInitWindowSize(WIDTH, HEIGHT);
     glutCreateWindow("OpenGL 窗口");
     glutDisplayFunc(&myDisplay);
     glutIdleFunc(&myIdle);
     glutMainLoop();
     return 0;
}

