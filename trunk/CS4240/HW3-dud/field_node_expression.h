#ifndef NODE_TYPE
#define NODE_TYPE "field"
#endif

#ifndef FIELD_NODE_EXPRESSION_H
#define FIELD_NODE_EXPRESSION_H


#include "base_node.h"
#include "field_node.h"
#include "expression_node.h"
#include <list>
#include <iostream>
#include <fstream>
#include "symbol_table.h"

extern CSymbolTableNode globalSymbolTable;

using namespace std;

class CFieldNodeExpression : public CFieldNode
{
    public:

        CFieldNodeExpression(ExpressionNode expression);
        virtual ~CFieldNodeExpression();

		ExpressionNode GetExpression();
		void PrintNode(ostream& file, int tabCount);
        virtual void GenerateSymbolTables(SymbolTableNode parent);
        virtual string GetNodeType() { return NODE_TYPE; }

    protected:

    private:
		ExpressionNode m_expression;
		

};


typedef CFieldNodeExpression* FieldNodeExpression;
typedef list<FieldNodeExpression> CFieldNodeExpressionList;
typedef CFieldNodeExpressionList* FieldNodeExpressionList;
typedef CFieldNodeExpressionList::iterator FieldNodeExpressionIter;



#endif // FIELD_NODE_EXPRESSION_H

