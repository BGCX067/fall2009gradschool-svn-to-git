#include "expression_node_bool.h"

CExpressionNodeBool::CExpressionNodeBool(bool value)
{
	m_value = value;
}

CExpressionNodeBool::~CExpressionNodeBool()
{
}

bool CExpressionNodeBool::GetValue()
{
	return m_value;
}

void CExpressionNodeBool::PrintNode(ostream& file, int tabCount)
{
	PrintTabs(file, tabCount);
	file << "( " << m_value << " )" << endl;
}

void CExpressionNodeBool::GenerateSymbolTables(SymbolTableNode parent)
{
    if (NULL == parent) return; // TODO: Throw an exception

    m_localSymbolTable = parent;
}

string CExpressionNodeBool::GetExpressionType()
{
    return VAR_BOOLEAN_ENTRY_TYPE;
}

Value*  CExpressionNodeBool::Codegen(IRBuilder<>* builder)
{
	if (m_value)
	{
		return ConstantInt::get(Type::Int1Ty, 1);
	}
	else
	{
		return ConstantInt::get(Type::Int1Ty, 0);
	}
}

