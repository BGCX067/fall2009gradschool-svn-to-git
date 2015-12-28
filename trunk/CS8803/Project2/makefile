
aicop: main.o frame.o aicop.tab.o lex.yy.o
	g++ -Wall -O0 -g -o aicop main.o frame.o aicop.tab.o lex.yy.o -lfl -ly

frame.o: frame.cpp
	g++ -Wall -O0 -c -g frame.cpp

main.o: main.cpp
	g++ -Wall -O0 -c -g main.cpp

aicop.tab.o: aicop.y
	bison -dv aicop.y
	g++ -O0 -c -g aicop.tab.c -w

lex.yy.o: aicop.l
	flex aicop.l
	g++ -O0 -c -g lex.yy.c

clean:
	rm -rf aicop *.o *.output *.tab.c *.tab.h lex.yy.c *~
