run:
	gcc -c -o Glee.o Glee.c
	gcc -c -o main.o main.cpp 
	gcc -o main.exe Glee.o main.o -lglu32 -lfreeglut -lopengl32 -Wl,--subsystem,windows

clean:
	rm *.o
	rm *.exe

