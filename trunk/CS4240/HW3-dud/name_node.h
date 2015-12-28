#ifndef NODE_TYPE
#define NODE_TYPE "name"
#endif

#define NAME_NODE_TYPE  "name"

#ifndef LEXNAMEVAL_H
#define LEXNAMEVAL_H


#include "base_node.h"
#include "yyvaltype.h"
#include <math.h>
#include <string>
#include <list>
#include <iostream>
#include <fstream>
#include "symbol_table.h"

#include "llvm_generator.h"

extern CSymbolTableNode globalSymbolTable;

using namespace std;

class CNameNode : public CBaseNode
{
    public:
        CNameNode(string value, int linenum);
        CNameNode(yyvalType* yyvaltype);
        virtual ~CNameNode();

		string GetValue();
		void PrintNode(ostream& file, int tabCount);
        virtual void GenerateSymbolTables(SymbolTableNode parent);
        virtual string GetNodeType() { return NODE_TYPE; }
		Value* Codegen(IRBuilder<>* builder, bool locationOnly);

    protected:
    private:
        string m_value;
};

typedef CNameNode* NameNode;
typedef list<NameNode> CNameNodeList;
typedef CNameNodeList* NameNodeList;
typedef CNameNodeList::iterator NameNodeIter;

#endif // LEXNAMEVAL_H
