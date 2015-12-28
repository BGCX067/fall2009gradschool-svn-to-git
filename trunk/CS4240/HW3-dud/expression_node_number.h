#ifndef NODE_TYPE
#define NODE_TYPE "exp"
#endif

#ifndef EXPRESSION_NODE_NUMBER_H
#define EXPRESSION_NODE_NUMBER_H


#include "base_node.h"
#include "expression_node.h"
#include "number_node.h"
#include <list>
#include <iostream>
#include <fstream>

extern CSymbolTableNode globalSymbolTable;

using namespace std;


class CExpressionNodeNumber : public CExpressionNode
{
    public:

        CExpressionNodeNumber(NumberNode value);
        virtual ~CExpressionNodeNumber();

		NumberNode GetValue();

		void PrintNode(ostream& file, int tabCount);
        virtual void GenerateSymbolTables(SymbolTableNode parent);
        virtual string GetNodeType() { return NODE_TYPE; }
        virtual string GetExpressionType();

		Value* Codegen(IRBuilder<>* builder);

    protected:

    private:

		NumberNode m_value;

};

typedef CExpressionNodeNumber* ExpressionNodeNumber;
typedef list<ExpressionNodeNumber> CExpressionNodeNumberList;
typedef CExpressionNodeNumberList* ExpressionNodeNumberList;
typedef CExpressionNodeNumberList::iterator ExpressionNodeNumberIter;



#endif // EXPRESSION_NODE_NUMBER_H

