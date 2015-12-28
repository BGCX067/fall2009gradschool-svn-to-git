#ifndef NODE_TYPE
#define NODE_TYPE "var"
#endif

#ifndef VARIABLE_NODE_PREFIX_DOT_H
#define VARIABLE_NODE_PREFIX_DOT_H


#include "base_node.h"
#include "variable_node.h"
#include "prefix_node.h"
#include "name_node.h"
#include <list>
#include <iostream>
#include <fstream>
#include "symbol_table.h"

extern CSymbolTableNode globalSymbolTable;



using namespace std;


class CVariableNodePrefixDot : public CVariableNode //abstract
{
    public:

        CVariableNodePrefixDot(PrefixNode prefix, NameNode name);
        virtual ~CVariableNodePrefixDot();
	
		PrefixNode GetPrefix();
		NameNode GetName();
		void PrintNode(ostream& file, int tabCount);
        virtual void GenerateSymbolTables(SymbolTableNode parent);
        virtual string GetNodeType() { return NODE_TYPE; }
        virtual list<BaseNode> GetChildren();
		Value* Codegen(IRBuilder<>* builder, bool locationOnly);

    protected:

    private:

		PrefixNode m_prefix;
		NameNode m_name;
		

};

typedef CVariableNodePrefixDot* VariableNodePrefixDot;
typedef list<VariableNodePrefixDot> CVariableNodePrefixDotList;
typedef CVariableNodePrefixDotList* VariableNodePrefixDotList;
typedef CVariableNodePrefixDotList::iterator VariableNodePrefixDotIter;



#endif // VariableNodePrefixDot_H

