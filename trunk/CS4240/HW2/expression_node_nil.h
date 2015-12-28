#ifndef NODE_TYPE
#define NODE_TYPE "nil"
#endif

#ifndef EXPRESSION_NODE_NIL_H
#define EXPRESSION_NODE_NIL_H


#include "base_node.h"
#include "expression_node.h"
#include <list>
#include <iostream>
#include <fstream>

extern CSymbolTableNode globalSymbolTable;

using namespace std;


class CExpressionNodeNil : public CExpressionNode
{
    public:
        CExpressionNodeNil();
        virtual ~CExpressionNodeNil();

		void PrintNode(ostream& file, int tabCount);
        virtual void GenerateSymbolTables(SymbolTableNode parent);
        virtual string GetNodeType() { return NODE_TYPE; }
        virtual string GetExpressionType();

		Value* Codegen(IRBuilder<>* builder);

    protected:

    private:


};


typedef CExpressionNodeNil* ExpressionNodeNil;
typedef list<ExpressionNodeNil> CExpressionNodeNilList;
typedef CExpressionNodeNilList* ExpressionNodeNilList;
typedef CExpressionNodeNilList::iterator ExpressionNodeNilIter;



#endif // EXPRESSION_NODE_NIL_H

