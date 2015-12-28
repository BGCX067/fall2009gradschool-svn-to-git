#include "statement_node_while.h"

CStatementNodeWhile::CStatementNodeWhile(ExpressionNode expressionNode, ChunkNode chunkNode)
{
	m_expressionNode = expressionNode;
	m_chunkNode = chunkNode;
}

CStatementNodeWhile::~CStatementNodeWhile()
{
}

ExpressionNode CStatementNodeWhile::GetExpressionNode()
{
	return m_expressionNode;
}

ChunkNode CStatementNodeWhile::GetChunkNode()
{
	return m_chunkNode;
}

void CStatementNodeWhile::PrintNode(ostream& file, int tabCount)
{
	PrintTabs(file, tabCount);
	file << "( While " << endl;

	m_expressionNode->PrintNode(file, tabCount+1);
	m_chunkNode->PrintNode(file, tabCount+1);

	PrintTabs(file, tabCount);
	file << ")" << endl;
}

void CStatementNodeWhile::GenerateSymbolTables(SymbolTableNode parent)
{
    if (NULL == parent)
    {
        m_expressionNode->GenerateSymbolTables(NULL);
        m_chunkNode->GenerateSymbolTables(NULL);
        return; // TODO: Throw an exception
    }

    m_localSymbolTable = parent;

    m_expressionNode->GenerateSymbolTables(m_localSymbolTable);
    m_chunkNode->GenerateSymbolTables(m_localSymbolTable);
}


BasicBlock* CStatementNodeWhile::Codegen(BasicBlock* block, Function* function, BasicBlock* breakBlock)
{
	//block for while
	BasicBlock* whileBlock = BasicBlock::Create("WhileBlock", function);

	//block to break to inside the while block
	BasicBlock* afterWhile = BasicBlock::Create("WhileBreakBlock", function);



	//test in block passed
	BasicBlock* testBlock = block;

	//builder for the test block
	IRBuilder<> builder(testBlock);

	//get value of evaluation
	Value* val = m_expressionNode->Codegen(&builder);

	//the value returned is not a bool or nil. so its true
	/* Both false and nil are considered false. All values different from
	   nil and false are considered true (in particular, the number 0 and
	   the empty string are also true). */
	if (val->getType() != Type::Int1Ty)
	{
		val = ConstantInt::get(Type::Int1Ty, 1);
	}

	//if val is true branch to while block otherwise branch to afterward
	builder.CreateCondBr(val, whileBlock, afterWhile);




	//create the do chunk returns the last block of the while
	BasicBlock* lastWhileBlock = m_chunkNode->Codegen(whileBlock, function, afterWhile);

	//last block for while chunk needs to Branch back to the test block
	IRBuilder<> builder2(lastWhileBlock);
	builder2.CreateBr(testBlock);



	//move the afterWhile block to after the lastWhileBlock
	afterWhile->moveAfter(lastWhileBlock);

	//this is the last block of this statement so return it
	return afterWhile;
}


