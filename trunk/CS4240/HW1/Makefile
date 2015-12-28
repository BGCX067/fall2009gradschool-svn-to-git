DEBUG= -g



luatfi: main.o ParseTreeNode.o luatfi.tab.o lex.yy.o
	g++ -O $(DEBUG) -o luac main.o ParseTreeNode.o luatfi.tab.o lex.yy.o -lfl -ly

ParseTreeNode.o: ParseTreeNode.cpp
	g++ -O -c $(DEBUG) ParseTreeNode.cpp

main.o: main.cpp
	g++ -O -c $(DEBUG) main.cpp

luatfi.tab.o: luatfi.y
	bison -dv luatfi.y
	g++ -O -c $(DEBUG) luatfi.tab.c -w

lex.yy.o: luatfi.tab.o luatfi.l
	flex luatfi.l
	g++ -O -c $(DEBUG) lex.yy.c

run: luac
	./luac .lua test0.lua test1.lua test2.lua test3.lua test4.lua test5.lua test6.lua test7.lua test8.lua test9.lua test11.lua test10.lua

clean:
	rm -rf *.o lex.yy.c luac.tab.* luac.output luatfi.output luac *~ *.out *.ast
