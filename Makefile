OBJECTS=main.o graphics.o transformation.o
CFLAGS= -std=c++11 -O2
CC=g++

build: $(OBJECTS)
	$(CC) -o draw_shell $(OBJECTS)

main.o: main.cpp graphics.h
	$(CC) $(CFLAGS) -c main.cpp

graphics.o: graphics.cpp graphics.h
	$(CC) $(CFLAGS) -c graphics.cpp

transformation.o: transformation.cpp graphics.h
	$(CC) $(CFLAGS) -c transformation.cpp

run: build
	./draw_shell

clean:
	rm *.out
	rm *.o
	rm draw_shell
