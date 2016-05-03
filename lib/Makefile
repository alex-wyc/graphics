lex.yy.c: mdl.l y.tab.h
	flex -I mdl.l

y.tab.c: mdl.y symtab.h parser.h
	bison -d -y mdl.y

y.tab.h: mdl.y
	bison -d -y mdl.y

symtab.o: symtab.c parser.h 
