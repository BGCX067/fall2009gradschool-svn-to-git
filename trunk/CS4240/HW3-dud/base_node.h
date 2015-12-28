#ifndef BASENODE_H
#define BASENODE_H


#include <list>
#include <iostream>
#include <fstream>
#include <string>

#include "llvm/Module.h"
#include "llvm/Function.h"
#include "llvm/PassManager.h"
#include "llvm/CallingConv.h"
#include "llvm/Analysis/Verifier.h"
#include "llvm/Assembly/PrintModulePass.h"
#include "llvm/Support/IRBuilder.h"
#include "llvm/Support/raw_ostream.h"


#include "error_handling.h"
#include "symbol_table.h"

using namespace llvm;
using namespace std;

class CBaseNode //abstract
{
public:
	CBaseNode();
	virtual ~CBaseNode();


	virtual void PrintNode(ostream& file, int tabCount)=0;
 	virtual void GenerateSymbolTables(SymbolTableNode parent)=0;
    virtual string GetNodeType()=0;

	int GetLineNum();

    SymbolTableNode m_localSymbolTable;
protected:
	void PrintTabs(ostream& file, int tabCount);
	int m_linenum;
   // SymbolTableNode m_localSymbolTable;
private:

};

typedef CBaseNode* BaseNode;
typedef list<BaseNode> CBaseNodeList;
typedef CBaseNodeList* BaseNodeList;
typedef CBaseNodeList::iterator BaseNodeIter;

#endif // BASENODE_H
