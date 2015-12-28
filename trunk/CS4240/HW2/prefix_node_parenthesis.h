#ifndef NODE_TYPE
#define NODE_TYPE "prefixexp"
#endif

#ifndef PREFIX_NODE_PARENTHESIS_H
#define PREFIX_NODE_PARENTHESIS_H


#include "base_node.h"
#include "prefix_node.h"
#include "expression_node.h"
#include <list>
#include <iostream>
#include <fstream>
#include "symbol_table.h"

extern CSymbolTableNode globalSymbolTable;

using namespace std;

class CPrefixNodeParenthesis : public CPrefixNode
{
    public:

        CPrefixNodeParenthesis(ExpressionNode expressionNode);
        virtual ~CPrefixNodeParenthesis();

		ExpressionNode GetExpressionNode();
		void PrintNode(ostream& file, int tabCount);
        virtual void GenerateSymbolTables(SymbolTableNode parent);
        virtual string GetNodeType() { return NODE_TYPE; }
        virtual string GetPrefixType();
		Value* Codegen(IRBuilder<>* builder);

    protected:

    private:
		ExpressionNode m_expressionNode;
};

typedef CPrefixNodeParenthesis* PrefixNodeParenthesis;
typedef list<PrefixNodeParenthesis> CPrefixNodeParenthesisList;
typedef CPrefixNodeParenthesisList* PrefixNodeParenthesisList;
typedef CPrefixNodeParenthesisList::iterator PrefixNodeParenthesisIter;



#endif // PREFIX_NODE_PARENTHESIS_H

