#ifndef NODE_TYPE
#define NODE_TYPE "exp"
#endif

#ifndef EXPRESSION_NODE_PREFIX_H
#define EXPRESSION_NODE_PREFIX_H


#include "base_node.h"
#include "expression_node.h"
#include "prefix_node.h"
#include <list>
#include <iostream>
#include <fstream>

extern CSymbolTableNode globalSymbolTable;

using namespace std;


class CExpressionNodePrefix : public CExpressionNode
{
    public:

        CExpressionNodePrefix(PrefixNode prefixNode);
        virtual ~CExpressionNodePrefix();

		PrefixNode GetPrefixNode();

		void PrintNode(ostream& file, int tabCount);
        virtual void GenerateSymbolTables(SymbolTableNode parent);
        virtual string GetNodeType() { return NODE_TYPE; }
        virtual string GetExpressionType();
		Value* Codegen(IRBuilder<>* builder);

    protected:

    private:

		PrefixNode m_prefixNode;

};

typedef CExpressionNodePrefix* ExpressionNodePrefix;
typedef list<ExpressionNodePrefix> CExpressionNodePrefixList;
typedef CExpressionNodePrefixList* ExpressionNodePrefixList;
typedef CExpressionNodePrefixList::iterator ExpressionNodePrefixIter;



#endif // EXPRESSION_NODE_PREFIX_H

