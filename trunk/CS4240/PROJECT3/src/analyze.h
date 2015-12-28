/****************************************************/
/* File: analyze.h                                  */
/* Semantic analyzer interface for LUA compiler     */
/* Haicheng                                         */
/****************************************************/

#ifndef _ANALYZE_H_
#define _ANALYZE_H_

/* Function buildSymtab constructs the symbol 
 * table by preorder traversal of the syntax tree
 */
void buildSymtab(TreeNode *);

/* Procedure typeCheck performs type checking 
 * by a postorder syntax tree traversal
 */
void typeCheck(TreeNode *);

void traversePrintSym (FILE * listing, HashTable * t);

void entBlock();

void entFunBlock();

void lvBlock();

void lvFunBlock();

#endif
