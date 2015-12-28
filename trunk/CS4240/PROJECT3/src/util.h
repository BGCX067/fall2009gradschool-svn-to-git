/****************************************************/
/* File: util.h                                     */
/* Utility functions for the LUA  compiler          */
/* Haicheng                                         */
/****************************************************/



#ifndef _UTIL_H_
#define _UTIL_H_

#include "cfg.h"
#include "dfg.h"

/* Procedure printToken prints a token 
 * and its lexeme to the listing file
 */
void printToken( TokenType, const char* );

/* Function newTermNode creates a new terminal
 * node for syntax tree construction
 */
TreeNode * newStmtNode(StmtKind);

/* Function newNTermNode creates a new nonterminal 
 * node for syntax tree construction
 */
TreeNode * newExpNode(ExpKind);

/* Function copyString allocates and makes a new
 * copy of an existing string
 */
char * copyString( char * );

/* procedure printTree prints a syntax tree to the 
 * listing file using indentation to indicate subtrees
 */
void printTree( TreeNode * );

void printTypeTree( TreeNode * );
void printCFGNode(CFGNode* node);
void printCFG(CFG* cfg);
void printDFG(BLOCK *blk);

#endif
