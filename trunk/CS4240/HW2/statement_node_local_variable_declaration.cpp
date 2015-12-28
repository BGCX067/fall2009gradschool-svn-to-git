#include "statement_node_local_variable_declaration.h"
#include "name_node.h"

CStatementNodeLocalVariableDeclaration::CStatementNodeLocalVariableDeclaration(NameNodeList names, ExpressionNodeList expressions)
{
	m_names = names;
	m_expressions = expressions;
}

CStatementNodeLocalVariableDeclaration::~CStatementNodeLocalVariableDeclaration()
{
}


NameNodeList CStatementNodeLocalVariableDeclaration::GetNames()
{
	return m_names;
}

ExpressionNodeList CStatementNodeLocalVariableDeclaration::GetExpressions()
{
	return m_expressions;
}

void CStatementNodeLocalVariableDeclaration::PrintNode(ostream& file, int tabCount)
{
	PrintTabs(file, tabCount);
	file << "( LocalVariable " << endl;

	NameNodeIter it;
	for (it=m_names->begin(); it!=m_names->end(); it++)
	{
		NameNode name = *it;
		name->PrintNode(file, tabCount+1);
	}

	ExpressionNodeIter it2;
	for (it2=m_expressions->begin(); it2!=m_expressions->end(); it2++)
	{
		ExpressionNode expression = *it2;
		expression->PrintNode(file, tabCount+1);
	}

	PrintTabs(file, tabCount);
	file << ")" << endl;
}

void CStatementNodeLocalVariableDeclaration::GenerateSymbolTables(SymbolTableNode parent)
{
    if (NULL == parent && NULL == m_localSymbolTable) return; // TODO: Throw an exception

    if (NULL == m_localSymbolTable)
        m_localSymbolTable = parent;

    CNameNodeList::iterator   nameiter = m_names->begin();
    CExpressionNodeList::iterator expiter = m_expressions->begin();

    for (;
          nameiter != m_names->end() &&
          expiter != m_expressions->end();
          nameiter++,
          expiter++)
    {
        (*nameiter)->GenerateSymbolTables(m_localSymbolTable);
        (*expiter)->GenerateSymbolTables(m_localSymbolTable);

        NameNode name = *nameiter;
		string expType = (*expiter)->GetExpressionType();

		if (expType == "UNIT")
		{
			EXIT_WITH_ERROR("Not allowed to assign to expressions or functions that return type UNIT: " + name->GetValue());
		}

		if (NULL != parent)
		{
			m_localSymbolTable->insertTableEntry(name->GetValue(), expType);
		}
		else
		{
			m_localSymbolTable->UpdateLocalValueType(name->GetValue(), expType);
		}

    }
/*
    for (list<NameNode>::iterator childIter = m_names->begin(); childIter != m_names->end(); childIter++)
    {
        m_localSymbolTable->insertTableEntry((*childIter)->GetValue(), "unknown"); // TODO: Put unknown in a macro somewhere.
    }*/

    if (NULL != parent)

    {
        for (list<NameNode>::iterator childIter = m_names->begin(); childIter != m_names->end(); childIter++)
        {
            (*childIter)->GenerateSymbolTables(m_localSymbolTable);
        }

        for (list<ExpressionNode>::iterator childIter = m_expressions->begin(); childIter != m_expressions->end(); childIter++)
        {
            (*childIter)->GenerateSymbolTables(m_localSymbolTable);
        }
    }
    else
    {
        for (list<NameNode>::iterator childIter = m_names->begin(); childIter != m_names->end(); childIter++)
        {
            (*childIter)->GenerateSymbolTables(NULL);
        }

        for (list<ExpressionNode>::iterator childIter = m_expressions->begin(); childIter != m_expressions->end(); childIter++)
        {
            (*childIter)->GenerateSymbolTables(NULL);
        }
    }
}


BasicBlock* CStatementNodeLocalVariableDeclaration::Codegen(BasicBlock* block, Function* function, BasicBlock* breakBlock)
{
	//code gen for this is just like node assign
	//so we cheat and create a node assign and do its codegen

	//it wants a varnodelist and we have namenode list so need to name some varnodes too
	CVariableNodeList variables;
	NameNodeIter it;
	for (it=m_names->begin(); it!=m_names->end(); it++)
	{
		NameNode name = *it;
		variables.push_back(new CVariableNodeName(name));
	}

	//create assign node and do codegen
	CStatementNodeAssign fakeAssign(&variables, m_expressions);
	BasicBlock* retVal = fakeAssign.Codegen(block, function, breakBlock);

	//delete all those VariableNodes we made
	VariableNodeIter it2;
	for (it2=variables.begin(); it2!=variables.end(); it2++)
	{
		VariableNodeName varNode = (VariableNodeName)(*it2);
		delete varNode;
	}

	return retVal;
}



