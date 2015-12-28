/****************************************************/
/* File: symtab.h                                   */
/* Symbol table interface for the LUA compiler      */
/* Haicheng                                         */
/****************************************************/

#ifndef _SYMTAB_H_
#define _SYMTAB_H_

extern HashTable *rootSymTable, *currSymTable, *nextChildSym;
extern HashTable *currFunSymTab;
extern int isRootSymTab;
extern int isFuncName;
extern int isPar;

HashTable * st_create();

void st_update(int lineno, BucketList l);

/* Procedure st_insert inserts line numbers and
 * memory locations into the symbol table
 * loc = memory location is inserted only the
 * first time, otherwise ignored
 */
void st_insert( char * name, int lineno, int loc );

/* Function st_lookup returns the memory 
 * location of a variable or -1 if not found
 */
BucketList st_lookup ( char * name );

/* Procedure printSymTab prints a formatted 
 * listing of the symbol table contents 
 * to the listing file
 */
void printSymTab(FILE * listing, HashTable * tab);

#endif
