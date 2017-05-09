run: glee.o main.o
	gcc -o main.exe glee.o main.o -lglu32 -lfreeglut -lopengl32 -Wl,--subsystem,windows

glee.o: glee.c glee.h
	gcc -c -o glee.o glee.c
main.o: main.cpp glee.h
	gcc -c -o main.o main.cpp 

clean:
	rm *.o
	rm *.exe
