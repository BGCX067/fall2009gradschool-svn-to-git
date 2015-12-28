#ifndef NODE_TYPE
#define NODE_TYPE "string"
#endif

#ifndef LEXSTRINGVAL_H
#define LEXSTRINGVAL_H

#include "base_node.h"
#include "yyvaltype.h"
#include <string>
#include <list>
#include <iostream>
#include <fstream>
#include "symbol_table.h"

#include "llvm_generator.h"

extern CSymbolTableNode globalSymbolTable;



using namespace std;

class CStringNode : public CBaseNode
{
    public:
        CStringNode(string value, int linenum);
        CStringNode(yyvalType* yyvaltype);
        virtual ~CStringNode();

		string GetValue();
		void PrintNode(ostream& file, int tabCount);
        virtual void GenerateSymbolTables(SymbolTableNode parent);
        virtual string GetNodeType() { return NODE_TYPE; }
		Value* Codegen(IRBuilder<>* builder);

    protected:
    private:
        string m_value;
};

typedef CStringNode* StringNode;
typedef list<StringNode> CStringNodeList;
typedef CStringNodeList* StringNodeList;
typedef CStringNodeList::iterator StringNodeIter;

#endif // LEXSTRINGVAL_H
