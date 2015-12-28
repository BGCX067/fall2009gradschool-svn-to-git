#ifndef NODE_TYPE
#define NODE_TYPE "prefixexp"
#endif

#ifndef PREFIX_NODE_VARIABLE_H
#define PREFIX_NODE_VARIABLE_H


#include "base_node.h"
#include "prefix_node.h"
#include "variable_node.h"
#include "variable_node_name.h"
#include <list>
#include <iostream>
#include <fstream>
#include "symbol_table.h"

extern CSymbolTableNode globalSymbolTable;

using namespace std;

class CPrefixNodeVariable : public CPrefixNode
{
    public:

        CPrefixNodeVariable(VariableNode variableNode);
        virtual ~CPrefixNodeVariable();

		VariableNode GetVariableNode();
		void PrintNode(ostream& file, int tabCount);
        virtual void GenerateSymbolTables(SymbolTableNode parent);
        virtual string GetNodeType() { return NODE_TYPE; }
        virtual string GetPrefixType();
		Value* Codegen(IRBuilder<>* builder);

		NameNode GetNameNode() { return m_variableNode->GetNameNode(); }


    protected:

    private:
		VariableNode m_variableNode;

};

typedef CPrefixNodeVariable* PrefixNodeVariable;
typedef list<PrefixNodeVariable> CPrefixNodeVariableList;
typedef CPrefixNodeVariableList* PrefixNodeVariableList;
typedef CPrefixNodeVariableList::iterator PrefixNodeVariableIter;



#endif // PREFIX_NODE_VARIABLE_H

