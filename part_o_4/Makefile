run:
	gcc -c -o Glee.o Glee.c
	gcc -c -o main.o main.cpp 
	gcc -o main.exe main.o Glee.o -lfreeglut -lopengl32 -lgdi32 -Wl,--subsystem,windows

clean:
	rm *.o
	rm *.exe

