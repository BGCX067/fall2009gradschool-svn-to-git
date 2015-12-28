#ifndef NODE_TYPE
#define NODE_TYPE "dots"
#endif

#ifndef EXPRESSION_NODE_DOTS_H
#define EXPRESSION_NODE_DOTS_H


#include "base_node.h"
#include "expression_node.h"
#include <list>
#include <iostream>
#include <fstream>

extern CSymbolTableNode globalSymbolTable;

using namespace std;


class CExpressionNodeDots : public CExpressionNode
{
    public:

        CExpressionNodeDots();
        virtual ~CExpressionNodeDots();

        void PrintNode(ostream& file, int tabCount);
        virtual void GenerateSymbolTables(SymbolTableNode parent);
        virtual string GetNodeType() { return NODE_TYPE; }
        virtual string GetExpressionType();
		Value* Codegen(IRBuilder<>* builder);

    protected:

    private:

};


typedef CExpressionNodeDots* ExpressionNodeDots;
typedef list<ExpressionNodeDots> CExpressionNodeDotsList;
typedef CExpressionNodeDotsList* ExpressionNodeDotsList;
typedef CExpressionNodeDotsList::iterator ExpressionNodeDotsIter;



#endif // EXPRESSION_NODE_DOTS_H

