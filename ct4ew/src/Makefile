
all: turtle eins.ps

eins.ps: eins.tlt turtle
	./turtle < eins.tlt > eins.ps

lex.yy.o:  lex.yy.c turtle.tab.h symtab.h
	gcc -c lex.yy.c -o lex.yy.o

lex.yy.c: turtle_ct4ew.l
	flex turtle_ct4ew.l 
	
turtle.tab.h: turtle_ct4ew.y
	bison -d turtle_ct4ew.y -o turtle.tab.h
	
turtle.tab.c: turtle_ct4ew.y
	bison -d turtle_ct4ew.y -o turtle.tab.c
	
turtle.tab.o: turtle.tab.c symtab.h
	gcc -c turtle.tab.c -o turtle.tab.o

turtle: turtle.tab.o lex.yy.o symtab.c
	gcc lex.yy.o turtle.tab.o symtab.c -ll -o turtle

clean:
	rm -f turtle lex.* turtle.tab.* *.o eins.ps

