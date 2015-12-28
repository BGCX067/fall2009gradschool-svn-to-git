#include "statement_node_numeric_for.h"

CStatementNodeNumericFor::CStatementNodeNumericFor(NameNode name, ExpressionNode exp1, ExpressionNode exp2, ExpressionNode exp3, ChunkNode chunk)
{
	m_name = name;
	m_exp1 = exp1;
	m_exp2 = exp2;
	m_exp3 = exp3;
	m_chunk = chunk;
}

CStatementNodeNumericFor::~CStatementNodeNumericFor()
{
}

NameNode CStatementNodeNumericFor::GetName()
{
	return m_name;
}

ExpressionNode CStatementNodeNumericFor::GetExp1()
{
	return m_exp1;
}

ExpressionNode CStatementNodeNumericFor::GetExp2()
{
	return m_exp2;
}

ExpressionNode CStatementNodeNumericFor::GetExp3()
{
	return m_exp3;
}

ChunkNode CStatementNodeNumericFor::GetChunk()
{
	return m_chunk;
}


void CStatementNodeNumericFor::PrintNode(ostream& file, int tabCount)
{
	PrintTabs(file, tabCount);
	file << "( For " << endl;

	m_name->PrintNode(file, tabCount+1);
	m_exp1->PrintNode(file, tabCount+1);
	m_exp2->PrintNode(file, tabCount+1);
	if (m_exp3 != NULL)
	{
		m_exp3->PrintNode(file, tabCount+1);
	}
	m_chunk->PrintNode(file, tabCount+1);

	PrintTabs(file, tabCount);
	file << ")" << endl;
}

void CStatementNodeNumericFor::GenerateSymbolTables(SymbolTableNode parent)
{
    if (NULL == parent && NULL == m_localSymbolTable) return; // TODO: Throw an exception

    if (NULL == m_localSymbolTable)
    {
        m_localSymbolTable = new CSymbolTableNode(parent->functionIn, parent);
        parent->insertChildTable(m_localSymbolTable);
    }

    if (NULL != parent)
    {
        m_exp1->GenerateSymbolTables(m_localSymbolTable);
        m_localSymbolTable->insertTableEntry("var", m_exp1->GetExpressionType());

        m_exp2->GenerateSymbolTables(m_localSymbolTable);
        m_localSymbolTable->insertTableEntry("limit", m_exp2->GetExpressionType());

        if(m_exp3 != NULL)
        {
            m_exp3->GenerateSymbolTables(m_localSymbolTable);
            m_localSymbolTable->insertTableEntry("step", m_exp3->GetExpressionType());
        }
        m_chunk->GenerateSymbolTables(m_localSymbolTable);

        m_name->GenerateSymbolTables(m_localSymbolTable);
        m_chunk->GetLocalSymbolTable()->insertTableEntry(m_name->GetValue(), m_exp1->GetExpressionType());
    }
    else
    {
        m_name->GenerateSymbolTables(NULL);
        m_exp1->GenerateSymbolTables(NULL);
        m_exp2->GenerateSymbolTables(NULL);
        if(m_exp3 != NULL)
        {
            m_exp3->GenerateSymbolTables(NULL);
        }
        m_chunk->GenerateSymbolTables(NULL);
    }

}


BasicBlock* CStatementNodeNumericFor::Codegen(BasicBlock* block, Function* function, BasicBlock* breakBlock)
{

	//evalue the expressions for the for block
	BasicBlock* forEvalBlock = block;

	//block for testing that for should continue
	BasicBlock* forTestBlock = BasicBlock::Create("ForTestBlock", function);

	//block for For
	BasicBlock* forBlock = BasicBlock::Create("ForBlock", function);

	//block for Increment block
	BasicBlock* forIncBlock = BasicBlock::Create("ForIncrementBlock", function);

	//block to break to inside the for block
	BasicBlock* forBreakBlock = BasicBlock::Create("ForBreakBlock", function);

	//create the for chunk      returns the last block of the for
	BasicBlock* lastForBlock = m_chunk->Codegen(forBlock, function, forBreakBlock);


	//last block should branch to the inc block
	IRBuilder<> builder2(lastForBlock);
	builder2.CreateBr(forIncBlock);

	//move inc block after last block of for
	forIncBlock->moveAfter(lastForBlock);
	//move break block after increment block
	forBreakBlock->moveAfter(forIncBlock);



	//build block to eval args to the for
	IRBuilder<> builderEval(forEvalBlock);

	//get values of the expressions
	Value* init = m_exp1->Codegen(&builderEval);
	Value* limit = m_exp2->Codegen(&builderEval);
	Value* step = ConstantFP::get(Type::DoubleTy, 1.0);
	if (m_exp3 != NULL)
	{
		 step = m_exp3->Codegen(&builderEval);
	}


	//get location for variable
	SymbolTableNode table = m_chunk->m_localSymbolTable->FindSymbolTableInLexicalScope(m_name->GetValue(), "");
	Value* varLoc = table->GetLLVMValue(m_name->GetValue());


	//set intial value of variable
	builderEval.CreateStore(init, varLoc);
	//go to the test block
	builderEval.CreateBr(forTestBlock);


	//build block to eval args to the varfor
	IRBuilder<> builderTest(forTestBlock);

	/*section 2.4.5 explains what to test for to decide to continue
      while (step > 0 and var <= limit) or (step <= 0 and var >= limit) do */
	Value* zeroVal = ConstantFP::get(Type::DoubleTy, 0.0);
	Value* var = builderTest.CreateLoad(varLoc);
	
	Value* stepGreterZero = builderTest.CreateFCmpOGT(step, zeroVal);
	Value* varLessEqLimit = builderTest.CreateFCmpOLE(var, limit);
	Value* leftSide = builderTest.CreateAnd(stepGreterZero, varLessEqLimit);

	Value* stepLessEqZero = builderTest.CreateFCmpOLE(step, zeroVal);
	Value* varGreatEqLimit = builderTest.CreateFCmpOGE(var, limit);
	Value* rightSide = builderTest.CreateAnd(stepLessEqZero, varGreatEqLimit);

	Value* full = builderTest.CreateOr(leftSide, rightSide);
	builderTest.CreateCondBr(full, forBlock, forBreakBlock);


	//build block for increment
	IRBuilder<> builderInc(forIncBlock);
	Value* var2 = builderInc.CreateLoad(varLoc);
	Value* varPlusInc = builderInc.CreateAdd(var2, step);
	builderInc.CreateStore(varPlusInc, varLoc);
	builderInc.CreateBr(forTestBlock);


	//this is the last block of this statement so return it
	return forBreakBlock;
}



