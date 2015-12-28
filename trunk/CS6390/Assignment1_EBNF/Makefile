DEBUG= -g

ebnf: main.o ebnf.tab.o lex.yy.o
	g++ -O -o ebnf main.o ebnf.tab.o lex.yy.o -lfl -ly -g

main.o: main.cpp
	g++ -O -c $(DEBUG) main.cpp -g

ebnf.tab.o: ebnf.y
	bison -dv ebnf.y
	g++ -O -c $(DEBUG) ebnf.tab.c -w -g

lex.yy.o: ebnf.tab.o ebnf.l
	flex ebnf.l
	g++ -O -c lex.yy.c -g

clean:
	rm -rf *.o lex.yy.c ebnf.tab.* ebnf.output ebnf *~
