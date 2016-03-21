OBJECTS=canvas.o transformation.o curves.o parser.o
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

transformation.o: transformation.cpp graphics.h
	$(CC) $(CFLAGS) -c transformation.cpp

run: build
	./shell.out

clean:
	rm *.out
	rm *.o
