OBJECTS=main.o graphics.o transformation.o
CFLAGS= -std=c++11 -O2
CC=g++

build: $(OBJECTS)
	$(CC) -o draw_shell.out $(OBJECTS)

flag: draw_flag.o graphics.o transformation.o
	$(CC) -o a.out draw_flag.o graphics.o transformation.o

draw_flag.o: draw_flag.cpp graphics.h
	$(CC) $(CFLAGS) -c draw_flag.cpp

main.o: main.cpp graphics.h
	$(CC) $(CFLAGS) -c main.cpp

graphics.o: graphics.cpp graphics.h
	$(CC) $(CFLAGS) -c graphics.cpp

transformation.o: transformation.cpp graphics.h
	$(CC) $(CFLAGS) -c transformation.cpp

run: build
	./draw_shell.out

clean:
	rm *.out
	rm *.o
