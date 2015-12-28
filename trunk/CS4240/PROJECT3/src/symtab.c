/****************************************************/
/* File: symtab.c                                   */
/* Symbol table implementation for the LUA compiler */
/* Symbol table is implemented as a chained         */
/* hash table                                       */
/* Haicheng                                         */
/****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "globals.h"
#include "symtab.h"

HashTable *rootSymTable, *currSymTable, *nextChildSym, *currFunSymTab;
int isRootSymTab;

/* the hash function */
static int hash ( char * key )
{ int temp = 0;
  int i = 0;
  while (key[i] != '\0')
  { temp = ((temp << SHIFT) + key[i]) % SIZE;
    ++i;
  }
  return temp;
}

HashTable * st_create()
{ HashTable *st_table = (HashTable *)malloc(sizeof(HashTable));
  memset(st_table, 0, sizeof(HashTable));
  return st_table;
}

void st_update(int lineno, BucketList l)
{ LineList t = l->lines;
  while (t->next != NULL) t = t->next;
  t->next = (LineList) malloc(sizeof(struct LineListRec));
  t->next->lineno = lineno;
  t->next->next = NULL;
}

/* Procedure st_insert inserts line numbers and
 * memory locations into the symbol table
 * loc = memory location is inserted only the
 * first time, otherwise ignored
 */
void st_insert( char * name, int lineno, int loc )
{ int h = hash(name);
  BucketList l, *tab;
  
  if (isRootSymTab)
    tab =  rootSymTable->table;
  else if(isRootSymTab == FALSE && isFuncName == TRUE)
    tab = currSymTable->parent->table;
  else
    tab = currSymTable->table;
    
  l = tab[h];
  l = (BucketList) malloc(sizeof(struct BucketListRec));
  l->name = name;
  l->lines = (LineList) malloc(sizeof(struct LineListRec));
  l->lines->lineno = lineno;
  l->memloc = loc;
  l->type = NilTy;
  l->tabType = NilTy;
  l->tabEleNum = 0;
  l->ptr = NULL;
  l->loc = NULL;
  l->lines->next = NULL;
  
  if ( isFuncName == TRUE)
    l->ptr = (void *) currSymTable;
  
  if ( isPar == TRUE)
  { ArgTypeList lt = currSymTable->argType;
  
    if (lt != NULL)
    {
      while(lt->next != NULL)
        lt = lt->next;
        
      lt->next = malloc(sizeof(struct ArgTypeRec));
      lt->next->arg = l;
      lt->next->next = NULL;
    }
    else
    { currSymTable->argType = malloc(sizeof(struct ArgTypeRec));
      currSymTable->argType->arg = l;
      currSymTable->argType->next = NULL;
    }
    
    l->isPar = TRUE;
  }
  else
    l->isPar = FALSE;
  
  l->next = tab[h];
  tab[h] = l; 
} /* st_insert */

/* Function st_lookup returns the memory 
 * location of a variable or -1 if not found
 */
BucketList st_lookup ( char * name )
{ int h = hash(name);
  HashTable *table = currSymTable;
  BucketList l;
  while (table != NULL)
  { l = table->table[h];
    while ((l != NULL) && (strcmp(name,l->name) != 0))
      l = l->next;
    if (l == NULL) table = table->parent;
    else return l;    
  }
  return NULL;
}

/* Procedure printSymTab prints a formatted 
 * listing of the symbol table contents 
 * to the listing file
 */
void printSymTab(FILE * listing, HashTable * tab)
{ int i;
  static tabID = 0;
  BucketList *table = tab->table;
  fprintf(listing,"Printing Symbol table %d\n", tabID++);
  fprintf(listing,"Variable Name  Location   Line Numbers\n");
  fprintf(listing,"-------------  --------   ------------\n");
  for (i=0;i<SIZE;++i)
  { if (table[i] != NULL)
    { BucketList l = table[i];
      while (l != NULL)
      { LineList t = l->lines;
        fprintf(listing,"%-14s ",l->name);
        fprintf(listing,"%-8d  ",l->memloc);
        while (t != NULL)
        { fprintf(listing,"%4d ",t->lineno);
          t = t->next;
        }
        fprintf(listing,"\n");
        l = l->next;
      }
    }
  }
} /* printSymTab */
