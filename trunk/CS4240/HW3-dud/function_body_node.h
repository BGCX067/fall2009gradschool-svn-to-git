#ifndef NODE_TYPE
#define NODE_TYPE "funcbody"
#endif

#ifndef FUNCTION_BODY_NODE_H
#define FUNCTION_BODY_NODE_H


#include "base_node.h"
#include "chunk_node.h"
#include "name_node.h"
#include <list>
#include <iostream>
#include <fstream>
#include "symbol_table.h"

extern CSymbolTableNode globalSymbolTable;

using namespace std;

class CFunctionBodyNode : public CBaseNode //abstract
{
    public:
        CFunctionBodyNode(NameNodeList parameters, bool varparm, ChunkNode block);
        virtual ~CFunctionBodyNode();

		NameNodeList GetParameters();
		bool GetVarparm();
		ChunkNode GetBlock();
		void PrintNode(ostream& file, int tabCount);
        virtual void GenerateSymbolTables(SymbolTableNode parent);
        virtual string GetNodeType() { return NODE_TYPE; }
		Function* Codegen(string functionName);
        CSymbolTableNode* GetLocalSymbolTable() { return m_localSymbolTable; }


    protected:

    private:
		NameNodeList m_parameters;
		bool m_varparm;
		ChunkNode m_block;

};

typedef CFunctionBodyNode* FunctionBodyNode;
typedef list<FunctionBodyNode> CFunctionBodyNodeList;
typedef CFunctionBodyNodeList* FunctionBodyNodeList;
typedef CFunctionBodyNodeList::iterator FunctionBodyNodeIter;



#endif // FUNCTION_BODY_NODE_H

