OBJECTS=bin/canvas.o bin/transformation.o bin/curves.o bin/util.o bin/3d.o bin/coor_system.o bin/symtab.o bin/print_pcode.o bin/my_main.o
CFLAGS= -std=c++11 -O2
LDFLAGS= -lm
CC=g++

all: parser

parser: lex.yy.c y.tab.c y.tab.h $(OBJECTS)
	$(CC) -o run_script $(CFLAGS) lex.yy.c y.tab.c $(OBJECTS) $(LDFLAGS)

lex.yy.c: lib/mdl.l y.tab.h 
	flex -I lib/mdl.l

y.tab.c: lib/mdl.y lib/symtab.h lib/parser.h
	bison -d -y lib/mdl.y

y.tab.h: lib/mdl.y 
	bison -d -y lib/mdl.y

bin/my_main.o: my_main.cpp
	$(CC) -c $(CFLAGS) my_main.cpp -o bin/my_main.o

bin/symtab.o: lib/symtab.c lib/parser.h
	$(CC) -c $(CFLAGS) lib/symtab.c -o bin/symtab.o

bin/print_pcode.o: lib/print_pcode.c lib/parser.h
	$(CC) -c $(CFLAGS) lib/print_pcode.c -o bin/print_pcode.o

bin/coor_system.o: lib/coor_system.cpp lib/graphics.h
	$(CC) $(CFLAGS) -c lib/coor_system.cpp -o bin/coor_system.o

bin/canvas.o: lib/canvas.cpp lib/graphics.h
	$(CC) $(CFLAGS) -c lib/canvas.cpp -o bin/canvas.o

bin/curves.o: lib/curves.cpp lib/graphics.h
	$(CC) $(CFLAGS) -c lib/curves.cpp -o bin/curves.o

bin/util.o: lib/util.cpp lib/graphics.h
	$(CC) $(CFLAGS) -c lib/util.cpp -o bin/util.o

bin/3d.o: lib/3d.cpp lib/graphics.h
	$(CC) $(CFLAGS) -c lib/3d.cpp -o bin/3d.o

bin/transformation.o: lib/transformation.cpp lib/graphics.h
	$(CC) $(CFLAGS) -c lib/transformation.cpp -o bin/transformation.o

clean:
	rm bin/*
	rm *.out
	rm *.png
	rm *.ppm
