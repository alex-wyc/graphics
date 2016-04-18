OBJECTS=bin/canvas.o bin/transformation.o bin/curves.o bin/parser.o bin/util.o bin/3d.o bin/coor_system.o
CFLAGS= -std=c++11 -O2
CC=g++

script: $(OBJECTS)
	$(CC) $(CFLAGS) -o run_script.out main.cpp $(OBJECTS)

bin/coor_system.o: lib/coor_system.cpp lib/graphics.h
	$(CC) $(CFLAGS) -c lib/coor_system.cpp -o bin/coor_system.o

bin/canvas.o: lib/canvas.cpp lib/graphics.h
	$(CC) $(CFLAGS) -c lib/canvas.cpp -o bin/canvas.o

bin/curves.o: lib/curves.cpp lib/graphics.h
	$(CC) $(CFLAGS) -c lib/curves.cpp -o bin/curves.o

bin/parser.o: lib/parser.cpp lib/graphics.h
	$(CC) $(CFLAGS) -c lib/parser.cpp -o bin/parser.o

bin/util.o: lib/util.cpp lib/graphics.h
	$(CC) $(CFLAGS) -c lib/util.cpp -o bin/util.o

bin/3d.o: lib/3d.cpp lib/graphics.h
	$(CC) $(CFLAGS) -c lib/3d.cpp -o bin/3d.o

bin/transformation.o: lib/transformation.cpp lib/graphics.h
	$(CC) $(CFLAGS) -c lib/transformation.cpp -o bin/transformation.o

run_script: script
	./run_script.out script

clean:
	rm bin/*
	rm *.out
	rm *.png
	rm *.ppm
