//modified from flag.c, there is normal for every point: normal[i][j][k],2001/8/28.
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glaux.h>
#include <math.h>
#include <stdio.h>
#include <malloc.h>
 
#define XN 25  //旗帜在X方向的节点数
#define YN 19  //旗帜在Y方向的节点数
#define XL 80.0/(XN-1) //X方向节点间距
#define YL 60.0/(YN-1) //Y方向节点间距
#define mg (XL+YL)*0.0004  //重力
 
void myinit(void);
void CALLBACK display(void);
void CALLBACK myReshape(GLsizei w,GLsizei h);
 
float cloth[XN][YN][3],normal[XN][YN][3],d[XN][YN][3],dd[XN][YN][3],w[3],t;
float lightamb[]={
0.2,0.2,0.2,1.0
};  //此四句定义灯光的属性
float lightdif[]={
0.9,0.9,0.90,1.0
}; 
float lightspe[]={
1.0,1.0,1.0,1.0
};
float lightpos[]={
0.3,0.5,1.2,0.0
};
float mat_amb[]={
0.4,0.2,0.2,1.0
};   //此四句定义旗帜的材质 
float mat_dif[]={
0.9,0.1,0.0,1.0
};
float mat_spe[]={
0.0,0.0,0.0,1.0
};
float mat_shininess[]={
50.0
};
 
float nnorm(float *a);
float norm(float *a);
float dot(float *a,float *b);
void cross(float *a,float *b,float *c);
void add(float *a,float *b,float *c);
void numult(float *a,float b,float*c);
void fixlen(float *a,float *b,float L,float *d);
void straighten(float *a,float *b,float *c,float *d1,float *d2,float *d3);
void strtangl(float *a,float *b,float *c,float *d1,float *d2,float *d3);
void wind(float *w,float *n,float *dd);
 
float nnorm(float *a)
{
 
int i;
float val=0.0;
for(i=0;i<3;i++) val+=a[i]*a[i];
return val;
 
}
float norm(float *a)
{
 
return sqrt(nnorm(a));
 
}
float dot(float *a,float *b)
{
 
int i;
float val=0.0;
for(i=0;i<3;i++) val+=a[i]*b[i];
return val;
 
}
void cross(float *a,float *b,float *c)
{
 
c[0]=a[1]*b[2]-a[2]*b[1];
c[1]=a[2]*b[0]-a[0]*b[2];
c[2]=a[0]*b[1]-a[1]*b[0];
 
}
void add(float *a,float *b,float *c)  //向量加法
{
 
int i;
for(i=0;i<3;i++) c[i]=a[i]+b[i];
 
}
void numult(float *a,float b,float*c)  //向量数乘
{
 
int i;
for(i=0;i<3;i++) c[i]=a[i]*b;
 
}
void fixlen(float *a,float *b,float L,float *d)  //使节点间距恢复到定长
{
 
int i;
float tmp,delta[3],lamda=0.98;
for(i=0;i<3;i++)
delta[i]=b[i]-a[i];
tmp=norm(delta);
if(tmp>0.0)
{
 
tmp=0.5*(1-L/tmp);
if(tmp<0.0) tmp*=0.1;
for(i=0;i<3;i++)
d[i]=tmp*delta[i]*lamda;
 
}
 
}
void straighten(float *a,float *b,float *c,float *d1,float *d2,float *d3)
//直线方向的弹性
{
 
int i;
float u[3],v[3],delta[3],delta1[3],tmp,tmp1,tmp2,lamda=0.005*(XL+YL);
for(i=0;i<3;i++)
{
 
u[i]=b[i]-a[i];
v[i]=c[i]-b[i];
 
}
tmp=norm(u)*norm(v);
if(tmp>0.0)
{
 
tmp=(tmp-dot(u,v))/tmp;
cross(u,v,&delta1);
tmp1=norm(delta1);
if(tmp1>0.0)
{
 
tmp2=tmp/tmp1;
cross(u,delta1,&delta);
for(i=0;i<3;i++)
{
 
tmp=lamda*tmp2*delta[i]/norm(u);
d1[i]+=tmp;
d2[i]-=tmp;
 
}
cross(v,delta1,&delta);
for(i=0;i<3;i++)
{
 
tmp=lamda*tmp2*delta[i]/norm(v);
d3[i]+=tmp;
d2[i]-=tmp;
 
}
 
}
 
}
 
}
 
void strtangl(float *a,float *b,float *c,float *d1,float *d2,float *d3)
//直角方向的弹性
{
 
int i;
float u[3],v[3],delta[3],delta1[3],tmp,tmp1,tmp2,lamda=0.006*(XL+YL);
for(i=0;i<3;i++)
{
 
u[i]=b[i]-a[i];
v[i]=c[i]-b[i];
 
}
tmp=dot(u,v);
if(tmp!=0.0)
{
 
tmp/=norm(u);
tmp/=norm(v);
cross(u,v,&delta1);
cross(delta1,u,&delta);
tmp1=norm(delta);
if(tmp1>0.0)
{
 
tmp1=tmp/tmp1;
for(i=0;i<3;i++)
{
 
tmp2=lamda*tmp1*delta[i];
d1[i]+=tmp2;
d2[i]-=tmp2;
 
}
 
}
cross(delta1,v,&delta);
tmp1=norm(delta);
if(tmp1>0.0)
{
 
tmp1=tmp/tmp1;
for(i=0;i<3;i++)
{
 
tmp2=lamda*tmp1*delta[i];
d3[i]+=tmp2;
d2[i]-=tmp2;
 
}
 
}
 
}
 
}
 
void wind(float *w,float *n,float *dd)//风力的作用
{
 
float tmp,lamda=(XL+YL)*0.008;
int i;
tmp=dot(w,n)*lamda;
for(i=0;i<3;i++)
{
 
dd[i]+=n[i]*tmp;
 
}
 
}
 
void myinit(void)
{
 
int i,j,k;
glShadeModel(GL_SMOOTH);
glEnable(GL_DEPTH_TEST);
auxInitDisplayMode(AUX_RGB|AUX_DEPTH|AUX_DOUBLE);
auxIdleFunc(display);
auxReshapeFunc(myReshape);
glClearColor(1.0,1.0,1.0,1.0);
for(i=0;i<XN;i++)
for(j=0;j<YN;j++)
{
 
cloth[i][j][0]=-40.0+i*XL;
cloth[i][j][1]=-20.0+j*YL;
cloth[i][j][2]=0.0;
 
}
w[0]=1.0;w[1]=0.0;w[2]=0.001;
 
glLightfv(GL_LIGHT0,GL_AMBIENT,lightamb);
glLightfv(GL_LIGHT0,GL_DIFFUSE,lightdif);
glLightfv(GL_LIGHT0,GL_SPECULAR,lightspe);
glLightfv(GL_LIGHT0,GL_POSITION,lightpos);
glEnable(GL_LIGHTING);
glEnable(GL_LIGHT0);
glEnable(GL_NORMALIZE);
glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,mat_amb);
glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,mat_dif);
glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,mat_spe);
glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,mat_shininess);
 
}
 
void CALLBACK display(void)
{
 
int i,j,k;
float tmpd[3],tmpu[3],tmpv[3],tmplen,lamda=0.95;
glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
for(i=0;i<XN;i++)
for(j=0;j<YN;j++)
for(k=0;k<3;k++)
{
 
d[i][j][k]=d[i][j][k]*lamda;
dd[i][j][k]=0.0;
 
}
for(i=0;i<XN;i++)
for(j=0;j<YN;j++)
d[i][j][1]-=mg;
 
for(i=0;i<XN;i++)
{
 
for(j=0;j<YN-1;j++)
{
 
fixlen(cloth[i][j],cloth[i][j+1],YL,tmpd);
for(k=0;k<3;k++)
{
 
d[i][j][k]+=tmpd[k];
d[i][j+1][k]-=tmpd[k];
 
}
 
}
 
}
for(j=0;j<YN;j++)
{
 
for(i=0;i<XN-1;i++)
{
 
fixlen(cloth[i][j],cloth[i+1][j],XL,tmpd);
for(k=0;k<3;k++)
{
 
d[i][j][k]+=tmpd[k];
d[i+1][j][k]-=tmpd[k];
 
}
 
}
 
}
for(i=0;i<XN;i++)
for(j=0;j<YN-2;j++)
{
 
straighten(cloth[i][j],cloth[i][j+1],cloth[i][j+2],d[i][j],d[i][j+1],d[i][j+2]);
 
}
for(j=0;j<YN;j++)
for(i=0;i<XN-2;i++)
{
 
straighten(cloth[i+2][j],cloth[i+1][j],cloth[i][j],d[i][j],d[i+1][j],d[i+2][j]);
 
}
for(i=0;i<XN-1;i++)
for(j=0;j<YN-1;j++)
{
 
strtangl(cloth[i][j],cloth[i+1][j],cloth[i+1][j+1],d[i][j],d[i+1][j],d[i+1][j+1]);
strtangl(cloth[i][j],cloth[i][j+1],cloth[i+1][j+1],d[i][j],d[i][j+1],d[i+1][j+1]);
 
}
for(i=1;i<XN-1;i++)
for(j=1;j<YN-1;j++)
{
 
for(k=0;k<3;k++)
{
 
tmpu[k]=cloth[i+1][j][k]-cloth[i-1][j][k];
tmpv[k]=cloth[i][j+1][k]-cloth[i][j-1][k];
 
}
cross(tmpu,tmpv,normal[i][j]);
tmplen=norm(normal[i][j]);
if(tmplen>0.0)
{
 
for(k=0;k<3;k++) normal[i][j][k]/=tmplen;
 
}
 
}
 
for(i=1;i<XN-1;i++)
{
 
for(k=0;k<3;k++)
{
 
tmpu[k]=cloth[i+1][0][k]-cloth[i-1][0][k];
tmpv[k]=cloth[i][1][k]-cloth[i][0][k];
 
}
cross(tmpu,tmpv,normal[i][0]);
tmplen=norm(normal[i][0]);
if(tmplen>0.0)
{
 
for(k=0;k<3;k++) normal[i][0][k]/=tmplen;
 
}
for(k=0;k<3;k++)
{
 
tmpu[k]=cloth[i+1][YN-1][k]-cloth[i-1][YN-1][k];
tmpv[k]=cloth[i][YN-1][k]-cloth[i][YN-2][k];
 
}
cross(tmpu,tmpv,normal[i][YN-1]);
tmplen=norm(normal[i][YN-1]);
if(tmplen>0.0)
{
 
for(k=0;k<3;k++) normal[i][YN-1][k]/=tmplen;
 
}
 
}
 
for(j=1;j<YN-1;j++)
{
 
for(k=0;k<3;k++)
{
 
tmpu[k]=cloth[1][j][k]-cloth[0][j][k];
tmpv[k]=cloth[0][j+1][k]-cloth[0][j-1][k];
 
}
cross(tmpu,tmpv,normal[0][j]);
tmplen=norm(normal[0][j]);
if(tmplen>0.0)
{
 
for(k=0;k<3;k++) normal[0][j][k]/=tmplen;
 
}
for(k=0;k<3;k++)
{
 
tmpu[k]=cloth[XN-1][j][k]-cloth[XN-2][j][k];
tmpv[k]=cloth[XN-1][j+1][k]-cloth[XN-1][j-1][k];
 
}
cross(tmpu,tmpv,normal[XN-1][j]);
tmplen=norm(normal[XN-1][j]);
if(tmplen>0.0)
{
 
for(k=0;k<3;k++) normal[XN-1][j][k]/=tmplen;
 
}
 
}
for(k=0;k<3;k++)
{
 
tmpu[k]=cloth[1][0][k]-cloth[0][0][k];
tmpv[k]=cloth[0][1][k]-cloth[0][0][k];
 
}
cross(tmpu,tmpv,normal[0][0]);
tmplen=norm(normal[0][0]);
if(tmplen>0.0) 
{
 
for(k=0;k<3;k++) normal[0][0][k]/=tmplen;
 
}
for(k=0;k<3;k++)
{
 
tmpu[k]=cloth[XN-1][0][k]-cloth[XN-2][0][k];
tmpv[k]=cloth[XN-1][1][k]-cloth[XN-1][0][k];
 
}
cross(tmpu,tmpv,normal[XN-1][0]);
tmplen=norm(normal[XN-1][0]);
if(tmplen>0.0) 
{
 
for(k=0;k<3;k++) normal[XN-1][0][k]/=tmplen;
 
}
for(k=0;k<3;k++)
{
 
tmpu[k]=cloth[1][YN-1][k]-cloth[0][YN-1][k];
tmpv[k]=cloth[0][YN-1][k]-cloth[0][YN-2][k];
 
}
cross(tmpu,tmpv,normal[0][YN-1]);
tmplen=norm(normal[0][YN-1]);
if(tmplen>0.0) 
{
 
for(k=0;k<3;k++) normal[0][YN-1][k]/=tmplen;
 
}
 
for(k=0;k<3;k++)
{
 
tmpu[k]=cloth[XN-1][YN-1][k]-cloth[XN-2][YN-1][k];
tmpv[k]=cloth[XN-1][YN-1][k]-cloth[XN-1][YN-2][k];
 
}
cross(tmpu,tmpv,normal[XN-1][YN-1]);
tmplen=norm(normal[XN-1][YN-1]);
if(tmplen>0.0) 
{
 
for(k=0;k<3;k++) normal[XN-1][YN-1][k]/=tmplen;
 
}
for(i=0;i<XN;i++)
for(j=0;j<YN;j++)
{
 
wind(w,normal[i][j],dd[i][j]);
for(k=0;k<3;k++)
d[i][j][k]+=dd[i][j][k];
 
}
for(j=0;j<YN;j++)
for(k=0;k<3;k++)
d[0][j][k]=0.0;
for(i=0;i<XN;i++)
for(j=0;j<YN;j++)
for(k=0;k<3;k++)
{
 
cloth[i][j][k]+=d[i][j][k];
 
}
glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
for(i=0;i<XN-1;i++)
{
 
glBegin(GL_QUAD_STRIP);
for(j=0;j<YN;j++)
{
 
glNormal3fv(normal[i][j]);
glVertex3fv(cloth[i][j]);
glNormal3fv(normal[i+1][j]);
glVertex3fv(cloth[i+1][j]);
 
}
glEnd();
 
}
auxSwapBuffers();  //启动双缓存机制，后台视频缓存向前台传递
 
}
 
void CALLBACK myReshape(GLsizei w,GLsizei h)
{
 
if(!h) return;
glViewport(0,0,w,h);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
if(w<=h)
glFrustum(-20.0,20.0,-20.0*(GLfloat)h/(GLfloat)w,
20.0*(GLfloat)h/(GLfloat)w,25.0,120.0);
else
    glFrustum(-20.0*(GLfloat)w/(GLfloat)h,
20.0*(GLfloat)w/(GLfloat)h,-20.0,20.0,25.0,120.0);
 
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
glTranslatef(0.0,0.0,-60.0);
glRotatef(3.0,0.0,1.0,0.0);
 
}
 
/* Main Loop
 * Open window with initial window size, title bar,
 * RGBA display mode, and handle input events.
 */
int main(int argc,char** argv)
{
 
auxInitDisplayMode(AUX_DOUBLE|AUX_RGB|AUX_DEPTH16);
auxInitPosition(0,0,300,300);  //定义画面大小
auxInitWindow("Flag");
myinit();
auxReshapeFunc(myReshape);
auxMainLoop(display);
return(0);
 
}
