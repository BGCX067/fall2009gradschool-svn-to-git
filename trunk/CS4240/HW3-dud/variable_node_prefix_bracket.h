#ifndef NODE_TYPE
#define NODE_TYPE "var"
#endif

#ifndef VARIABLE_NODE_PREFIX_BRACKET_H
#define VARIABLE_NODE_PREFIX_BRACKET_H


#include "base_node.h"
#include "variable_node.h"
#include "prefix_node.h"
#include "expression_node.h"
#include <list>
#include <iostream>
#include <fstream>
#include "symbol_table.h"

extern CSymbolTableNode globalSymbolTable;



using namespace std;


class CVariableNodePrefixBracket : public CVariableNode //abstract
{
    public:

        CVariableNodePrefixBracket(PrefixNode prefix, ExpressionNode expression);
        virtual ~CVariableNodePrefixBracket();

		PrefixNode GetPrefix();
		ExpressionNode GetExpression();
		void PrintNode(ostream& file, int tabCount);
        virtual void GenerateSymbolTables(SymbolTableNode parent);
        virtual string GetNodeType() { return NODE_TYPE; }
        virtual list<BaseNode> GetChildren();
		Value* Codegen(IRBuilder<>* builder, bool locationOnly);

    protected:

    private:
		PrefixNode m_prefix;
		ExpressionNode m_expression;

};

typedef CVariableNodePrefixBracket* VariableNodePrefixBracket;
typedef list<VariableNodePrefixBracket> CVariableNodePrefixBracketList;
typedef CVariableNodePrefixBracketList* VariableNodePrefixBracketList;
typedef CVariableNodePrefixBracketList::iterator VariableNodePrefixBracketIter;



#endif // VARIABLE_NODE_PREFIX_BRACKET_H

