run: main.o stanford_bunny.o
	gcc -o main.exe stanford_bunny.o main.o -lglu32 -lfreeglut -lopengl32 -Wl,--subsystem,windows

main.o: main.cpp stanford_bunny.h
	gcc -c -o main.o main.cpp 

stanford_bunny.o: stanford_bunny.cpp stanford_bunny.h
	gcc -c -o stanford_bunny.o stanford_bunny.cpp

clean:
	rm *.o
	rm *.exe
