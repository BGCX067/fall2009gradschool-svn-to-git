#ifndef NODE_TYPE
#define NODE_TYPE "var"
#endif

#ifndef VARIABLE_NODE_NAME_H
#define VARIABLE_NODE_NAME_H


#include "base_node.h"
#include "variable_node.h"
#include "name_node.h"
#include <list>
#include <iostream>
#include <fstream>
#include "symbol_table.h"

extern CSymbolTableNode globalSymbolTable;



using namespace std;


class CVariableNodeName : public CVariableNode //abstract
{
    public:

        CVariableNodeName(NameNode name);
        virtual ~CVariableNodeName();

		NameNode GetName();
		void PrintNode(ostream& file, int tabCount);
        virtual void GenerateSymbolTables(SymbolTableNode parent);
        virtual string GetNodeType() { return NODE_TYPE; }
        virtual list<BaseNode> GetChildren();

		Value* Codegen(IRBuilder<>* builder, bool locationOnly);

		virtual NameNode GetNameNode(){ return m_name; }

    protected:

    private:
		NameNode m_name;


};

typedef CVariableNodeName* VariableNodeName;
typedef list<VariableNodeName> CVariableNodeNameList;
typedef CVariableNodeNameList* VariableNodeNameList;
typedef CVariableNodeNameList::iterator VariableNodeNameIter;



#endif // VARIABLE_NODE_NAME_H

