#ifndef NODE_TYPE
#define NODE_TYPE "exp"
#endif

#ifndef EXPRESSION_NODE_STRING_H
#define EXPRESSION_NODE_STRING_H


#include "base_node.h"
#include "expression_node.h"
#include "string_node.h"
#include <list>
#include <iostream>
#include <fstream>

extern CSymbolTableNode globalSymbolTable;

using namespace std;

class CExpressionNodeString : public CExpressionNode
{
    public:

        CExpressionNodeString(StringNode value);
        virtual ~CExpressionNodeString();

		StringNode GetValue();

		void PrintNode(ostream& file, int tabCount);
        virtual void GenerateSymbolTables(SymbolTableNode parent);
        virtual string GetNodeType() { return NODE_TYPE; }
        virtual string GetExpressionType();
		Value* Codegen(IRBuilder<>* builder);

    protected:

    private:
		StringNode m_value;

};

typedef CExpressionNodeString* ExpressionNodeString;
typedef list<ExpressionNodeString> CExpressionNodeStringList;
typedef CExpressionNodeStringList* ExpressionNodeStringList;
typedef CExpressionNodeStringList::iterator ExpressionNodeStringIter;



#endif // EXPRESSION_NODE_STRING_H

