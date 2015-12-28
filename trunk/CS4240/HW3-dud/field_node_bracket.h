#ifndef NODE_TYPE
#define NODE_TYPE "field"
#endif

#ifndef FIELD_NODE_BRACKET_H
#define FIELD_NODE_BRACKET_H


#include "base_node.h"
#include "field_node.h"
#include "expression_node.h"
#include <list>
#include <iostream>
#include <fstream>
#include "symbol_table.h"

extern CSymbolTableNode globalSymbolTable;

using namespace std;

class CFieldNodeBracket : public CFieldNode
{
    public:

        CFieldNodeBracket(ExpressionNode bracketExpression, ExpressionNode equalsExpression);
        virtual ~CFieldNodeBracket();

		ExpressionNode GetBracketExpression();
		ExpressionNode GetEqualsExpression();
		void PrintNode(ostream& file, int tabCount);
        virtual void GenerateSymbolTables(SymbolTableNode parent);
        virtual string GetNodeType() { return NODE_TYPE; }

    protected:

    private:
		ExpressionNode m_bracketExpression;
		ExpressionNode m_equalsExpression;
		
		

};

typedef CFieldNodeBracket* FieldNodeBracket;
typedef list<FieldNodeBracket> CFieldNodeBracketList;
typedef CFieldNodeBracketList* FieldNodeBracketList;
typedef CFieldNodeBracketList::iterator FieldNodeBracketIter;



#endif // FIELD_NODE_BRACKET_H

