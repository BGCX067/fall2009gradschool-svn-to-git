#include "statement_node_if.h"

CStatementNodeIf::CStatementNodeIf(ExpressionNodeList expressions, ChunkNodeList chunks)
{
	m_expressions = expressions;
	m_chunks = chunks;
}

CStatementNodeIf::~CStatementNodeIf()
{
}

ExpressionNodeList CStatementNodeIf::GetExpressions()
{
	return m_expressions;
}

ChunkNodeList CStatementNodeIf::GetChunks()
{
	return m_chunks;
}


void CStatementNodeIf::PrintNode(ostream& file, int tabCount)
{
	PrintTabs(file, tabCount);
	file << "( If " << endl;

	ExpressionNodeIter it;
	for (it=m_expressions->begin(); it!=m_expressions->end(); it++)
	{
		ExpressionNode expression = *it;
		expression->PrintNode(file, tabCount+1);
	}

	ChunkNodeIter it2;
	for (it2=m_chunks->begin(); it2!=m_chunks->end(); it2++)
	{
		ChunkNode chunk = *it2;
		chunk->PrintNode(file, tabCount+1);
	}

	PrintTabs(file, tabCount);
	file << ")" << endl;
}

void CStatementNodeIf::GenerateSymbolTables(SymbolTableNode parent)
{
    if (NULL == parent)
    {

        for (list<ExpressionNode>::iterator childIter = m_expressions->begin(); childIter != m_expressions->end(); childIter++)
        {
            (*childIter)->GenerateSymbolTables(NULL);
        }

        for (list<ChunkNode>::iterator childIter = m_chunks->begin(); childIter != m_chunks->end(); childIter++)
        {
            (*childIter)->GenerateSymbolTables(NULL);
        }

        return; // TODO: Throw an exception
    }

    m_localSymbolTable = parent;

    for (list<ExpressionNode>::iterator childIter = m_expressions->begin(); childIter != m_expressions->end(); childIter++)
    {
        (*childIter)->GenerateSymbolTables(m_localSymbolTable);
    }

    for (list<ChunkNode>::iterator childIter = m_chunks->begin(); childIter != m_chunks->end(); childIter++)
    {
        (*childIter)->GenerateSymbolTables(m_localSymbolTable);
    }
}




BasicBlock* CStatementNodeIf::Codegen(BasicBlock* block, Function* function, BasicBlock* breakBlock)
{


	//block after all the if blocks
	BasicBlock* afterIf = BasicBlock::Create("AfterIfBlock", function);

	//blocks for evaluating wich if to do
	list<BasicBlock*> evalBlocks;
	int evalNum = 1;

	//block after all the if blocks
	ExpressionNodeIter it;
	for (it=m_expressions->begin(); it!=m_expressions->end(); it++)
	{
		//ExpressionNode expression = *it;

		stringstream evalName;
		string evalNameStr;
		evalName << "EVAL " << evalNum++ << "_";
		evalNameStr=evalName.str();

		//create eval blocks (dont add evals yet through)
		BasicBlock* evalBlock = BasicBlock::Create(evalNameStr, function);
		//add to block list
		evalBlocks.push_back(evalBlock);
	}

	//in the block passed to us to work we just jump to the first eval block
	BasicBlock* evalBlock1 = evalBlocks.front();
	IRBuilder<> builderForPassed(block);
	builderForPassed.CreateBr(evalBlock1);


	//last block of all the if statment needed to move AfterIfBlock after it
	BasicBlock* lastIfBlock;


	//blocks for the choices of the if statement
	list<BasicBlock*> ifBlocks;
	int ifNum = 1;

	//make a block for each chunk
	ChunkNodeIter it2;
	for (it2=m_chunks->begin(); it2!=m_chunks->end(); it2++)
	{
		ChunkNode chunk = *it2;

		stringstream chunkName;
		string chunkNameStr;
		chunkName << "IF " << ifNum++ << "_";
		chunkNameStr=chunkName.str();

		//create first block for the if
		BasicBlock* ifBlock = BasicBlock::Create(chunkNameStr, function);
		//add to block list
		ifBlocks.push_back(ifBlock);

		//create the if chunk returns the last block of the if
		lastIfBlock = chunk->Codegen(ifBlock, function, breakBlock);

		//last block for if chunk needs to Branch to afterIf block
		IRBuilder<> builder2(lastIfBlock);
		builder2.CreateBr(afterIf);

	}

	//move the afterIf block to after the lastIfBlock
	afterIf->moveAfter(lastIfBlock);

	//determine if the if statement has an else
	bool hasElse = false;
	if (m_chunks->size() > m_expressions->size())
	{
		hasElse = true;
	}

	//get block for this evaluation
	BasicBlock* evalBlockOn = NULL;
	if (evalBlocks.size() > 0)
	{
		evalBlockOn = evalBlocks.front();
		evalBlocks.pop_front();
	}

	//and the evaluation after this one
	BasicBlock* nextEvalBlock = NULL;
	if (evalBlocks.size() > 0)
	{
		nextEvalBlock = evalBlocks.front();
		evalBlocks.pop_front();
	}


	//get if to go to if the evaluation of evalBlockOn is true
	BasicBlock* ifBlock = NULL;
	if (ifBlocks.size() > 0)
	{
		ifBlock = ifBlocks.front();
		ifBlocks.pop_front();
	}

	//eval each expression
	for (it=m_expressions->begin(); it!=m_expressions->end(); it++)
	{
		ExpressionNode expression = *it;


		//builder for the eval block
		IRBuilder<> builder(evalBlockOn);

		//get value of evaluation
		Value* val = expression->Codegen(&builder);

		//the value returned is not a bool or nil. so its true
		/* Both false and nil are considered false. All values different from
		   nil and false are considered true (in particular, the number 0 and
   		   the empty string are also true). */
		if (val->getType() != Type::Int1Ty)
		{
			val = ConstantInt::get(Type::Int1Ty, 1);
		}

		if (nextEvalBlock != NULL)
		{
			//if val is true well branch to its if otherwise well try the next evalBlock
			builder.CreateCondBr(val, ifBlock, nextEvalBlock);
		}
		else //we cant try the next eval block so do else block or afterIf
		{
			if (hasElse)
			{
				//else will be the only block left in ifBlocks
				BasicBlock* elseBlock = ifBlocks.front();

				//if val is true well branch to its if otherwise well do else
				builder.CreateCondBr(val, ifBlock, elseBlock);
			}
			else
			{
				//if val is true well branch to its if otherwise well goto after If
				builder.CreateCondBr(val, ifBlock, afterIf);
			}
		}


		//got to next eval block
		evalBlockOn = nextEvalBlock;
		nextEvalBlock = NULL;
		if (evalBlocks.size() > 0)
		{
			nextEvalBlock = evalBlocks.front();
			evalBlocks.pop_front();
		}


		//and next if block
		ifBlock = NULL;
		if (ifBlocks.size() > 0)
		{
			ifBlock = ifBlocks.front();
			ifBlocks.pop_front();
		}
	}


	//this is the last block of this statement so return it
	return afterIf;
}


