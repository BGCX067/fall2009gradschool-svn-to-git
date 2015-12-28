#include "expression_node_table_constructor.h"

CExpressionNodeTableConstructor::CExpressionNodeTableConstructor(FieldNodeList fields)
{
	m_fields = fields;
}

CExpressionNodeTableConstructor::~CExpressionNodeTableConstructor()
{
}



FieldNodeList CExpressionNodeTableConstructor::GetFields()
{
	return m_fields;
}

void CExpressionNodeTableConstructor::PrintNode(ostream& file, int tabCount)
{
	PrintTabs(file, tabCount);
	file << "( Table Constructor " << endl;

	FieldNodeIter it;
	for (it=m_fields->begin(); it!=m_fields->end(); it++)
	{
		FieldNode field = *it;
		field->PrintNode(file, tabCount+1);
	}

	PrintTabs(file, tabCount);
	file << ")" << endl;
}

void CExpressionNodeTableConstructor::GenerateSymbolTables(SymbolTableNode parent)
{
    if (NULL == parent)
    {
        for (list<FieldNode>::iterator childIter = m_fields->begin(); childIter != m_fields->end(); childIter++)
        {
            (*childIter)->GenerateSymbolTables(NULL);
        }
        return; // TODO: Throw an exception
    }

    m_localSymbolTable = parent;

    for (list<FieldNode>::iterator childIter = m_fields->begin(); childIter != m_fields->end(); childIter++)
    {
        (*childIter)->GenerateSymbolTables(m_localSymbolTable);
    }
}

string CExpressionNodeTableConstructor::GetExpressionType()
{
    EXIT_WITH_ERROR("Table Constructors not supported in type inference.");
}

Value* CExpressionNodeTableConstructor::Codegen(IRBuilder<>* builder)
{
	std::cout << "tables are NOT supported" << endl;
	return NULL;
}


