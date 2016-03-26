OBJECTS=canvas.o transformation.o curves.o parser.o util.o 3d.o
CFLAGS= -std=c++11 -O2
CC=g++

script: $(OBJECTS)
	$(CC) $(CFLAGS) -o run_script.out main.cpp $(OBJECTS)

build: shell.o $(OBJECTS)
	$(CC) -o shell.out $(OBJECTS)

shell.o: shell.cpp graphics.h
	$(CC) $(CFLAGS) -c shell.cpp

canvas.o: canvas.cpp graphics.h
	$(CC) $(CFLAGS) -c canvas.cpp

curves.o: curves.cpp graphics.h
	$(CC) $(CFLAGS) -c curves.cpp

parser.o: parser.cpp graphics.h
	$(CC) $(CFLAGS) -c parser.cpp

util.o: util.cpp graphics.h
	$(CC) $(CFLAGS) -c util.cpp

3d.o: 3d.cpp graphics.h
	$(CC) $(CFLAGS) -c 3d.cpp

transformation.o: transformation.cpp graphics.h
	$(CC) $(CFLAGS) -c transformation.cpp

run_shell: build
	./shell.out

run_script: script
	./run_script.out script

clean:
	rm *.out
	rm *.o
