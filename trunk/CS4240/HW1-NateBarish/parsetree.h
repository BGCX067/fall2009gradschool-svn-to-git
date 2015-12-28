#ifndef PARSETREENODE
# define PARSETREENODE

#include "yyvaltype.h"


typedef struct treenode
{
	int linenum;
	char* text;	
   	char* value;

	int numOfChildren;
   	struct treenode** children;
} treenode;


treenode* makeTreeNodeNonTerm(char* text);
treenode* makeTreeNodeTerm(yyvalType* val);

void addChild(treenode* parent, treenode* child);

void addChildren(treenode* parent, treenode* childrensParent);

void printTreeNode(treenode* node, FILE* file);

void deleteTreeNode(treenode* node);

#endif

