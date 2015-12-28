#include "statement_node_repeate.h"

CStatementNodeRepeate::CStatementNodeRepeate(ChunkNode chunkNode, ExpressionNode expressionNode)
{
	m_chunkNode = chunkNode;
	m_expressionNode = expressionNode;
}

CStatementNodeRepeate::~CStatementNodeRepeate()
{
}


ChunkNode CStatementNodeRepeate::GetChunkNode()
{
	return m_chunkNode;
}

ExpressionNode CStatementNodeRepeate::GetExpressionNode()
{
	return m_expressionNode;
}


void CStatementNodeRepeate::PrintNode(ostream& file, int tabCount)
{
	PrintTabs(file, tabCount);
	file << "( Repeate " << endl;

	m_chunkNode->PrintNode(file, tabCount+1);
	m_expressionNode->PrintNode(file, tabCount+1);

	PrintTabs(file, tabCount);
	file << ")" << endl;
}

void CStatementNodeRepeate::GenerateSymbolTables(SymbolTableNode parent)
{
    if (NULL == parent)
    {
        m_chunkNode->GenerateSymbolTables(NULL);
        m_expressionNode->GenerateSymbolTables(NULL);
        return; // TODO: Throw an exception
    }

    m_localSymbolTable = parent;

    m_chunkNode->GenerateSymbolTables(m_localSymbolTable);
    m_expressionNode->GenerateSymbolTables(m_localSymbolTable);
}



BasicBlock* CStatementNodeRepeate::Codegen(BasicBlock* block, Function* function, BasicBlock* breakBlock)
{


	//block to break to inside the repeate block (will need to move to after testBlock)
	BasicBlock* afterRepeate = BasicBlock::Create("RepeateBreakBlock", function);


	//block for repeate
	BasicBlock* repeateBlock = block;
	//create the repreate chunk    returns the last block of the repeate
	BasicBlock* lastRepeateBlock = m_chunkNode->Codegen(repeateBlock, function, afterRepeate);

	//create block to do test in
	BasicBlock* testBlock  = BasicBlock::Create("RepeateTestBlock", function);;

	//last block for repeate chunk needs to Branch to the test block
	IRBuilder<> builder2(lastRepeateBlock);
	builder2.CreateBr(testBlock);

	//move break block after test block
	afterRepeate->moveAfter(testBlock);



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

	//if val is true branch to repeate block otherwise branch to afterward
	builder.CreateCondBr(val, afterRepeate, repeateBlock);



	//this is the last block of this statement so return it
	return afterRepeate;
}


