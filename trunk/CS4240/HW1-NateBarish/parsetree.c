#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "parsetree.h"


treenode* makeTreeNodeNonTerm(char* text)
{
	treenode* ret = (treenode*)malloc(sizeof(treenode));

	ret->linenum = -1;
	ret->text = strdup(text);
	ret->value = strdup("");
	ret->numOfChildren = 0;
	ret->children = NULL;

	return ret;
}

treenode* makeTreeNodeTerm(yyvalType* val)
{
	treenode* ret = (treenode*)malloc(sizeof(treenode));

	ret->linenum = val->linenum;
	ret->text = strdup(val->tokText);
	ret->value = strdup(val->value);
	ret->numOfChildren = 0;
	ret->children = NULL;

	return ret;
}


void addChild(treenode* parent, treenode* child)
{
	if (child->linenum < parent->linenum || parent->linenum == -1)
	{
		parent->linenum = child->linenum;
	}

	parent->numOfChildren += 1;
	parent->children = (treenode**)realloc(parent->children, sizeof(treenode*) * parent->numOfChildren);
	parent->children[ parent->numOfChildren - 1 ] = child;

}


void addChildren(treenode* parent, treenode* childrensParent)
{

	int i;
	for(i=0; i < childrensParent->numOfChildren; i++)
	{
		addChild(parent, childrensParent->children[i]);
	}

}

void printTabs(int number, FILE* file)
{
	int i;
	for(i=0;i<number;i++)
	{	
		fprintf(file, "\t");
	}
}


void printTreeNode2(treenode* node, FILE* file, int tabcount)
{
	if (node->numOfChildren == 0)
	{
		printTabs(tabcount, file);
		fprintf(file, "(%s %i %s)\n", node->text, node->linenum, node->value);
	}
	else
	{
	
		printTabs(tabcount, file);
		fprintf(file, "(%s %i %s\n", node->text, node->linenum, node->value);
		
		int i;
		for(i=0; i < node->numOfChildren; i++)
		{
			printTreeNode2(node->children[i], file, tabcount + 1);
		}

		printTabs(tabcount, file);
		fprintf(file, ")\n");
	}
}

void printTreeNode(treenode* node, FILE* file)
{
	printTreeNode2(node, file, 0);
}


void deleteTreeNode(treenode* node)
{	
	free(node->text);
	free(node->value);
	free(node->children);
	free(node);
}




