run:
	gcc -c -o main.o main.cpp 
	gcc -o main.exe main.o -lfreeglut -lopengl32 -lglu32 -Wl,--subsystem,windows

lighting:
	gcc -c -o lighting.o lighting.cpp 
	gcc -o lighting.exe lighting.o -lfreeglut -lopengl32 -lglu32 -Wl,--subsystem,windows

clean:
	rm *.o
	rm *.exe

