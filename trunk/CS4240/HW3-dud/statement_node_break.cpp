#include "statement_node_break.h"

CStatementNodeBreak::CStatementNodeBreak()
{
}

CStatementNodeBreak::~CStatementNodeBreak()
{
}


void CStatementNodeBreak::PrintNode(ostream& file, int tabCount)
{
	PrintTabs(file, tabCount);
	file << "( Break ) " << endl;
}

void CStatementNodeBreak::GenerateSymbolTables(SymbolTableNode parent)
{
    if (NULL == parent) return; // TODO: Throw an exception

    m_localSymbolTable = parent;
}


BasicBlock* CStatementNodeBreak::Codegen(BasicBlock* block, Function* function, BasicBlock* breakBlock)
{
	if (breakBlock == NULL)
	{
		std::cout << "Trying to break in a non breakable location" << endl;
	}

	//just add a branch to this block branching to the break block
	IRBuilder<> builder(block);
	builder.CreateBr(breakBlock);

	return block;

}


