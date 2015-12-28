#ifndef NODE_TYPE
#define NODE_TYPE "field"
#endif

#ifndef FIELD_NODE_NAME_H
#define FIELD_NODE_NAME_H


#include "base_node.h"
#include "field_node.h"
#include "expression_node.h"
#include "name_node.h"
#include <list>
#include <iostream>
#include <fstream>
#include "symbol_table.h"

extern CSymbolTableNode globalSymbolTable;

using namespace std;

class CFieldNodeName : public CFieldNode
{
    public:

        CFieldNodeName(NameNode name, ExpressionNode expression);
        virtual ~CFieldNodeName();

		ExpressionNode GetExpression();
		NameNode GetName();
		void PrintNode(ostream& file, int tabCount);
        virtual void GenerateSymbolTables(SymbolTableNode parent);
        virtual string GetNodeType() { return NODE_TYPE; }

    protected:

    private:
		ExpressionNode m_expression;
		NameNode m_name;
		

};


typedef CFieldNodeName* FieldNodeName;
typedef list<FieldNodeName> CFieldNodeNameList;
typedef CFieldNodeNameList* FieldNodeNameList;
typedef CFieldNodeNameList::iterator FieldNodeNameIter;



#endif // FIELD_NODE_NAME_H

