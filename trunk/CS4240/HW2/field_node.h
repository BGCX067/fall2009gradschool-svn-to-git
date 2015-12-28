#ifndef NODE_TYPE
#define NODE_TYPE "field"
#endif


#ifndef FIELD_NODE_H
#define FIELD_NODE_H


#include "base_node.h"
#include <list>
#include <iostream>
#include <fstream>
#include "symbol_table.h"

extern CSymbolTableNode globalSymbolTable;

using namespace std;

class CFieldNode : public CBaseNode //abstract
{
    public:

        CFieldNode();
        virtual ~CFieldNode();

		virtual void PrintNode(ostream& file, int tabCount)=0;
        virtual void GenerateSymbolTables(SymbolTableNode parent);
        virtual string GetNodeType() { return NODE_TYPE; }


    protected:

    private:
		

};

typedef CFieldNode* FieldNode;
typedef list<FieldNode> CFieldNodeList;
typedef CFieldNodeList* FieldNodeList;
typedef CFieldNodeList::iterator FieldNodeIter;



#endif // FIELD_NODE_H

