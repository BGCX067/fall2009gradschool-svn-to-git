#include "statement_node_function_definition.h"
#include "statement_node_return.h"

CStatementNodeFunctionDefinition::CStatementNodeFunctionDefinition(NameNodeList names, FunctionBodyNode functionBody)
{
	m_names = names;
	m_functionBody = functionBody;
}

CStatementNodeFunctionDefinition::~CStatementNodeFunctionDefinition()
{
}



NameNodeList CStatementNodeFunctionDefinition::GetNames()
{
	return m_names;
}


FunctionBodyNode CStatementNodeFunctionDefinition::GetFunctionBody()
{
	return m_functionBody;
}




string CStatementNodeFunctionDefinition::FullName()
{
	string retStr;
	NameNodeIter it;
	for (it=m_names->begin(); it!=m_names->end(); it++)
	{
		NameNode name = *it;
		retStr += name->GetValue();
	}

	return retStr;
}


void CStatementNodeFunctionDefinition::PrintNode(ostream& file, int tabCount)
{
	PrintTabs(file, tabCount);
	file << "( Function " << endl;

	NameNodeIter it;
	for (it=m_names->begin(); it!=m_names->end(); it++)
	{
		NameNode name = *it;
		name->PrintNode(file, tabCount+1);
	}

	m_functionBody->PrintNode(file, tabCount+1);

	PrintTabs(file, tabCount);
	file << ")" << endl;
}

void CStatementNodeFunctionDefinition::GenerateSymbolTables(SymbolTableNode parent)
{
    if (NULL == parent)
    {
        for (list<NameNode>::iterator childIter = m_names->begin(); childIter != m_names->end(); childIter++)
        {
            (*childIter)->GenerateSymbolTables(NULL);
        }

        m_functionBody->GenerateSymbolTables(NULL);
        return; // TODO: Throw an exception
    }

    m_localSymbolTable = parent;

    //Adds function names to function symbol table
    //Functions default to a local symbol table (not a global one)
    for (list<NameNode>::iterator childIter = m_names->begin(); childIter != m_names->end(); childIter++)
    {
		m_localSymbolTable->insertFunctionEntry((*childIter)->GetValue(), this);
        //~ m_localSymbolTable->insertTableEntry((*childIter)->GetValue(), FUNCTION_INSERT_TYPE);
    }

    for (list<NameNode>::iterator childIter = m_names->begin(); childIter != m_names->end(); childIter++)
    {
        (*childIter)->GenerateSymbolTables(m_localSymbolTable);
    }

    m_functionBody->GenerateSymbolTables(m_localSymbolTable);
}

BasicBlock* CStatementNodeFunctionDefinition::Codegen(BasicBlock* block, Function* function, BasicBlock* breakBlock)
{
	if (m_names->size() != 1)
	{
		std::cout << "Multipart function names not supported." << endl;
	}
// 	Function* func =
            m_functionBody->Codegen(m_names->front()->GetValue());

	return block;
}


string CStatementNodeFunctionDefinition::GetStatementType()
{
    StatementNodeList  functionStatments = m_functionBody->GetBlock()->GetStatements();


    for (list<StatementNode>::iterator statIter = functionStatments->begin();
         statIter != functionStatments->end();
         statIter++)
    {
        if ((*statIter)->GetNodeType() == "laststat" &&
            (*statIter)->GetStatementType() == "VALUE")
        {
            ExpressionNodeList expressions = ((StatementNodeReturn)(*statIter))->GetExpressions();

            for (list<ExpressionNode>::iterator expsIter = expressions->begin();
                 expsIter != expressions->end();
                 expsIter++)
            {
                return (*expsIter)->GetExpressionType();

            }

//                     ->GetExpressionType();

        }
    }

    return "UNIT";
}

