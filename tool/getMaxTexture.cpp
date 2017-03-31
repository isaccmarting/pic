#include <stdio.h>
#include <gl/glut.h>

int main()
{
	GLint max;
    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max);
	printf("GL_MAX_TEXTURE_SIZE is %d\n", max); 
	return 0; 
}
