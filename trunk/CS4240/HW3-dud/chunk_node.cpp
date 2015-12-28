#include "chunk_node.h"


CChunkNode::CChunkNode(StatementNodeList statements)
{
	m_statements = statements;
}

CChunkNode::~CChunkNode()
{
}


StatementNodeList CChunkNode::GetStatements()
{
	return m_statements;
}

void CChunkNode::PrintNode(ostream& file, int tabCount)
{
	PrintTabs(file, tabCount);
	file << "( Chunk " << endl;

	StatementNodeIter it;
	for (it=m_statements->begin(); it!=m_statements->end(); it++)
	{
		StatementNode statement = *it;
		statement->PrintNode(file, tabCount+1);
	}

	PrintTabs(file, tabCount);
	file << ")" << endl;
}

BasicBlock* CChunkNode::Codegen(BasicBlock* block, Function* function, BasicBlock* breakBlock)
{

	string blockBaseName = block->getName();

	BasicBlock* blockOn = block; //block for the satement being written this iteration
	int blockCount = 1;

	BasicBlock* lastBlock = NULL; //last block of the last written statement

	//generate code for each statement in the block
	StatementNodeIter it;
	for (it=m_statements->begin(); it!=m_statements->end(); it++)
	{
		StatementNode statement = *it;


		if (blockOn == NULL) //true every time but the first (we are provided a block for the first)
		{
			blockCount++; //increment count & make name for block
			stringstream blockName;
  			string blockNameStr;
			blockName << blockBaseName << " " << blockCount;
			blockNameStr=blockName.str();

			//create the block for the this statement
			blockOn = BasicBlock::Create(blockNameStr, function);

			//last block for last statement need to point to this one
			IRBuilder<> builder(lastBlock);
			builder.CreateBr(blockOn);

		}

// 		statement->PrintNode(std::cout,0);
// 		std::cout << endl;

		//write the code for this statement
		lastBlock = statement->Codegen(blockOn, function, breakBlock);

		//std::cout << "fuck" << endl;
	

		//set to NULL so a new block will be created next iteration
		blockOn = NULL;
	}


	return lastBlock;
}

void CChunkNode::GenerateSymbolTables(SymbolTableNode parent)
{
//     if (NULL == parent) return; // TODO: Throw an exception

    if (NULL == parent)
    {
        for (CStatementNodeList::iterator iter = m_statements->begin(); iter != m_statements->end(); iter++)
        {
            (*iter)->GenerateSymbolTables(NULL);
        }
        return;
    }

    m_localSymbolTable = new CSymbolTableNode(parent->functionIn , parent);
    parent->insertChildTable(m_localSymbolTable);

    for (CStatementNodeList::iterator iter = m_statements->begin(); iter != m_statements->end(); iter++)
    {
        (*iter)->GenerateSymbolTables(m_localSymbolTable);
    }
}


