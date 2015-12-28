all :			lua

lua :			y.tab.c lex.yy.c main.c parsetree.c parsetree.h yyvaltype.c yyvaltype.h
				cc lex.yy.c y.tab.c main.c parsetree.c yyvaltype.c -oluac

y.tab.c :		lua.y
				yacc -d --debug --verbose lua.y


lex.yy.c :		lua.l
				lex -s lua.l



