#ifndef NODE_TYPE
#define NODE_TYPE "exp"
#endif

#ifndef EXPRESSION_NODE_TABLE_CONSTRUCTOR_H
#define EXPRESSION_NODE_TABLE_CONSTRUCTOR_H


#include "base_node.h"
#include "expression_node.h"
#include "field_node.h"
#include <list>
#include <iostream>
#include <fstream>

extern CSymbolTableNode globalSymbolTable;

using namespace std;

class CExpressionNodeTableConstructor : public CExpressionNode
{
    public:

        CExpressionNodeTableConstructor(FieldNodeList fields);
        virtual ~CExpressionNodeTableConstructor();

		FieldNodeList GetFields();
		void PrintNode(ostream& file, int tabCount);
        virtual void GenerateSymbolTables(SymbolTableNode parent);
        virtual string GetNodeType() { return NODE_TYPE; }
		Value* Codegen(IRBuilder<>* builder);
        virtual string GetExpressionType();


    protected:

    private:
		FieldNodeList m_fields;


};

typedef CExpressionNodeTableConstructor* ExpressionNodeTableConstructor;
typedef list<ExpressionNodeTableConstructor> CExpressionNodeTableConstructorList;
typedef CExpressionNodeTableConstructorList* ExpressionNodeTableConstructorList;
typedef CExpressionNodeTableConstructorList::iterator ExpressionNodeTableConstructorIter;



#endif // EXPRESSION_NODE_TABLE_CONSTRUCTOR_H

