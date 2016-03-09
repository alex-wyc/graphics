OBJECTS=main.o canvas.o transformation.o
CFLAGS= -std=c++11 -O2
CC=g++

build: $(OBJECTS)
	$(CC) -o draw_shell.out $(OBJECTS)

main.o: main.cpp graphics.h
	$(CC) $(CFLAGS) -c main.cpp

canvas.o: canvas.cpp graphics.h
	$(CC) $(CFLAGS) -c canvas.cpp

transformation.o: transformation.cpp graphics.h
	$(CC) $(CFLAGS) -c transformation.cpp

run: build
	./draw_shell.out

clean:
	rm *.out
	rm *.o
