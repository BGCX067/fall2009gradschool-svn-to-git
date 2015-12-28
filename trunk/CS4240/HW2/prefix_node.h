#ifndef NODE_TYPE
#define NODE_TYPE "prefixexp"
#endif

#ifndef PREFIX_NODE_H
#define PREFIX_NODE_H

#include "name_node.h"
#include "base_node.h"
#include <list>
#include <iostream>
#include <fstream>
#include "symbol_table.h"

extern CSymbolTableNode globalSymbolTable;

using namespace std;

class CPrefixNode : public CBaseNode //abstract
{
    public:

        CPrefixNode();
        virtual ~CPrefixNode();

		virtual void PrintNode(ostream& file, int tabCount)=0;
        virtual void GenerateSymbolTables(SymbolTableNode parent);
        virtual string GetNodeType() { return NODE_TYPE; }
        virtual string GetPrefixType()=0;
		virtual Value* Codegen(IRBuilder<>* builder) = 0;

		virtual NameNode GetNameNode(){ return NULL; }

    protected:

    private:


};

typedef CPrefixNode* PrefixNode;
typedef list<PrefixNode> CPrefixNodeList;
typedef CPrefixNodeList* PrefixNodeList;
typedef CPrefixNodeList::iterator PrefixNodeIter;



#endif // PREFIX_NODE_H

