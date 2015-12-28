
#ifndef NODE_TYPE
#define NODE_TYPE "chunk"
#endif

#ifndef CHUNKNODE_H
#define CHUNKNODE_H

#include "base_node.h"
#include "statement_node.h"
#include <list>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>


#include "llvm/Module.h"
#include "llvm/Function.h"
#include "llvm/PassManager.h"
#include "llvm/CallingConv.h"
#include "llvm/Analysis/Verifier.h"
#include "llvm/Assembly/PrintModulePass.h"
#include "llvm/Support/IRBuilder.h"
#include "llvm/Support/raw_ostream.h"

#include "symbol_table.h"



extern CSymbolTableNode globalSymbolTable;

using namespace llvm;
using namespace std;

class CChunkNode : public CBaseNode
{
    public:
        CChunkNode(StatementNodeList statements);
        virtual ~CChunkNode();
		StatementNodeList GetStatements();
		void PrintNode(ostream& file, int tabCount);

		//each chunk gets: (this is the same as a statement_node)
		//block - functionality of the chunk should start in this block (more block can be made but this must be the first)
		//function - if more block need be made this is the function they should be made with this function
		//breakBlock - if a break happens in this statement or somewhere down the line this is the block that gets breaked to
		//return - the last block of this statement
		BasicBlock* Codegen(BasicBlock* block, Function* function, BasicBlock* breakBlock);

		virtual void GenerateSymbolTables(SymbolTableNode parent);
        virtual string GetNodeType() { return NODE_TYPE; }
        CSymbolTableNode* GetLocalSymbolTable() { return m_localSymbolTable; }

    protected:
    private:
		StatementNodeList m_statements;
};

typedef CChunkNode* ChunkNode;
typedef list<ChunkNode> CChunkNodeList;
typedef CChunkNodeList* ChunkNodeList;
typedef CChunkNodeList::iterator ChunkNodeIter;

#endif // CHUNKNODE_H
