#
# Makefile for LUA
# Gnu C Version
# Haicheng
#

CC = gcc

LEX = flex

YACC = bison

CFLAGS = -g

LDFLAGS = -lfl -ly

OBJS = main.o util.o scan.o parse.o symtab.o analyze.o code.o cgen.o \
       cfg.o dfg.o constprop.o deadcode.o cfgopti.o rmunreachable.o cse.o

luac: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o luac $(LDFLAGS)

main.o: main.c globals.h util.h scan.h parse.o
	$(CC) $(CFLAGS) -c main.c

util.o: util.c util.h globals.h parse.o
	$(CC) $(CFLAGS) -c util.c

scan.o: lua.l scan.h util.h globals.h parse.o
	$(LEX) lua.l
	$(CC) $(CFLAGS) -c lex.yy.c -o scan.o

parse.o: lua.y parse.h scan.h globals.h util.h
	$(YACC) -d lua.y
	$(CC) $(CFLAGS) -c lua.tab.c -o parse.o
	
symtab.o: symtab.c symtab.h
	$(CC) $(CFLAGS) -c symtab.c

analyze.o: analyze.c globals.h symtab.h analyze.h
	$(CC) $(CFLAGS) -c analyze.c
	
code.o: code.c code.h globals.h
	$(CC) $(CFLAGS) -c code.c

cgen.o: cgen.c globals.h symtab.h code.h cgen.h constprop.h rmunreachable.h cfg.h dfg.h cfgopti.h constprop.h deadcode.h cse.h
	$(CC) $(CFLAGS) -c cgen.c
	
cfg.o: cfg.c cfg.h globals.h code.h
	$(CC) $(CFLAGS) -c cfg.c
	
cfgopti.o: cfgopti.c cfgopti.h cfg.c cfg.h
	$(CC) $(CFLAGS) -c cfgopti.c
	
dfg.o: dfg.c dfg.h globals.h code.h
	$(CC) $(CFLAGS) -c dfg.c
	
constprop.o: constprop.c constprop.h code.h globals.h cfg.h dfg.h
	$(CC) $(CFLAGS) -c constprop.c
	
deadcode.o: deadcode.c deadcode.h code.h globals.h cfg.h dfg.h
	$(CC) $(CFLAGS) -c deadcode.c
	
rmunreachable.o: rmunreachable.c rmunreachable.h code.h globals.h
	$(CC) $(CFLAGS) -c rmunreachable.c
	
cse.o: cse.c cse.h code.h globals.h
	$(CC) $(CFLAGS) -c cse.c

clean:
	-rm -rf luac
	-rm -rf *.ll
	-rm -rf *.bc
	-rm -rf lex.yy.c
	-rm -rf lua.tab.*
	-rm -rf $(OBJS)
	-rm -rf *~

all: luac

