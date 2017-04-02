#include <stdio.h>
#include <string.h>
#include <GL/glut.h>

// 判断OpenGL是否支持某个指定的扩展
// 若支持，返回1。否则返回0。
int hasExtension(const char* name) {
    const char* extensions = (const char*)glGetString(GL_EXTENSIONS);
    const char* end = extensions + strlen(extensions);
    size_t name_length = strlen(name);
    while( extensions < end ) {
        size_t position = strchr(extensions, ' ') - extensions;
        if( position == name_length &&
                strncmp(extensions, name, position) == 0 )
            return 1;
         extensions += (position + 1);
     }
    return 0;
}

int main()
{
	int main_version, sub_version, release_version;
	char version[20]; 
	// const char* version = (const char*)glGetString(GL_VERSION);
//	glGetString(GL_VENDOR); 返回OpenGL的提供厂商。
//	glGetString(GL_RENDERER); 返回执行OpenGL渲染的设备，通常就是显卡的名字。
//	glGetString(GL_EXTENSIONS); 返回所支持的所有扩展，每两个扩展之间用空格隔开。
	
//	strcpy(version, (const char*)glGetString(GL_VERSION)); 
	printf("OpenGL 版本：%s\n", (const char*)glGetString(GL_VERSION)); 
	sscanf(version, "%d.%d.%d", &main_version, &sub_version, &release_version);
	printf("OpenGL 版本：%s\n", version);
	printf("主版本号：%d\n", main_version);
	printf("次版本号：%d\n", sub_version);
	printf("发行版本号：%d\n", release_version);

	return 0; 
}
