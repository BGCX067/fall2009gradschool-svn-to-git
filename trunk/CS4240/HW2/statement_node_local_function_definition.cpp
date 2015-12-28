#include "statement_node_local_function_definition.h"
#include "statement_node_return.h"

CStatementNodeLocalFunctionDefinition::CStatementNodeLocalFunctionDefinition(NameNode name, FunctionBodyNode functionBody)
{
	m_name = name;
	m_functionBody = functionBody;
}

CStatementNodeLocalFunctionDefinition::~CStatementNodeLocalFunctionDefinition()
{
}


NameNode CStatementNodeLocalFunctionDefinition::GetName()
{
	return m_name;
}

FunctionBodyNode CStatementNodeLocalFunctionDefinition::GetFunctionBody()
{
	return m_functionBody;
}

void CStatementNodeLocalFunctionDefinition::PrintNode(ostream& file, int tabCount)
{
	PrintTabs(file, tabCount);
	file << "( LocalFunction " << endl;

	m_name->PrintNode(file, tabCount+1);
	m_functionBody->PrintNode(file, tabCount+1);

	PrintTabs(file, tabCount);
	file << ")" << endl;
}

void CStatementNodeLocalFunctionDefinition::GenerateSymbolTables(SymbolTableNode parent)
{
    if (NULL == parent)
    {

        m_name->GenerateSymbolTables(NULL);
        m_functionBody->GenerateSymbolTables(NULL);
        return; // TODO: Throw an exception
    }

    m_localSymbolTable = parent;

    //Adds function names to function symbol table
    //Functions default to a local symbol table (not a global one)
    m_localSymbolTable->insertFunctionEntry(m_name->GetValue(), this);
    //~ m_localSymbolTable->insertTableEntry(m_name->GetValue(), FUNCTION_INSERT_TYPE); // TODO: Put unknown in a macro somewhere.

    m_name->GenerateSymbolTables(m_localSymbolTable);
    m_functionBody->GenerateSymbolTables(m_localSymbolTable);
}


BasicBlock* CStatementNodeLocalFunctionDefinition::Codegen(BasicBlock* block, Function* function, BasicBlock* breakBlock)
{
// 	Function* func =
            m_functionBody->Codegen(m_name->GetValue());

	//TODO: generate code to set local var to function so that it can be called now
	return block;
}


string CStatementNodeLocalFunctionDefinition::GetStatementType()
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
        }
    }

    return "UNIT";
}

