#ifndef NODE_TYPE
#define NODE_TYPE "bool"
#endif

#ifndef EXPRESSION_NODE_BOOL_H
#define EXPRESSION_NODE_BOOL_H


#include "base_node.h"
#include "expression_node.h"
#include <list>
#include <iostream>
#include <fstream>

extern CSymbolTableNode globalSymbolTable;

using namespace std;


class CExpressionNodeBool : public CExpressionNode
{
    public:

        CExpressionNodeBool(bool value);
        virtual ~CExpressionNodeBool();

		bool GetValue();

		void PrintNode(ostream& file, int tabCount);
        virtual void GenerateSymbolTables(SymbolTableNode parent);
        virtual string GetNodeType() { return NODE_TYPE; }
        virtual string GetExpressionType();
		Value* Codegen(IRBuilder<>* builder);
    protected:

    private:
		bool m_value;

};


typedef CExpressionNodeBool* ExpressionNodeBool;
typedef list<ExpressionNodeBool> CExpressionNodeBoolList;
typedef CExpressionNodeBoolList* ExpressionNodeBoolList;
typedef CExpressionNodeBoolList::iterator ExpressionNodeBoolIter;



#endif // EXPRESSION_NODE_BOOL_H

