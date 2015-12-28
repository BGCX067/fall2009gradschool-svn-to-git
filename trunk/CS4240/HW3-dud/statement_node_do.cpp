#include "statement_node_do.h"

CStatementNodeDo::CStatementNodeDo(ChunkNode chunkNode)
{
	m_chunkNode = chunkNode;
}

CStatementNodeDo::~CStatementNodeDo()
{
}


ChunkNode CStatementNodeDo::GetChunkNode()
{
	return m_chunkNode;
}


void CStatementNodeDo::PrintNode(ostream& file, int tabCount)
{
	PrintTabs(file, tabCount);
	file << "( Do " << endl;

	m_chunkNode->PrintNode(file, tabCount+1);

	PrintTabs(file, tabCount);
	file << ")" << endl;
}

void CStatementNodeDo::GenerateSymbolTables(SymbolTableNode parent)
{
    if (NULL == parent)
    {
        m_chunkNode->GenerateSymbolTables(NULL);
        return; // TODO: Throw an exception
    }

    m_localSymbolTable = parent;

    m_chunkNode->GenerateSymbolTables(m_localSymbolTable);
}



BasicBlock* CStatementNodeDo::Codegen(BasicBlock* block, Function* function, BasicBlock* breakBlock)
{

	//block to break to inside the do block
	BasicBlock* afterDo = BasicBlock::Create("DoBreakBlock", function);

	//create do block in block passed
	BasicBlock* doBlock = block;

	//create the do chunk returns the last block of the do
	BasicBlock* lastDoBlock = m_chunkNode->Codegen(doBlock, function, afterDo);

	//move the afterDo block to after the lastDoBlock
	afterDo->moveAfter(lastDoBlock);

	//last block for do chunk needs to Branch to afterDo block
	IRBuilder<> builder(lastDoBlock);
	builder.CreateBr(afterDo);

	//this is the last block of this statement so return it
	return afterDo;
}


