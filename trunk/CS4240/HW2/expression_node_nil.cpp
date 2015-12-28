#include "expression_node_nil.h"

CExpressionNodeNil::CExpressionNodeNil()
{
}

CExpressionNodeNil::~CExpressionNodeNil()
{
}

void CExpressionNodeNil::PrintNode(ostream& file, int tabCount)
{
	PrintTabs(file, tabCount);
	file << "( nil ) " << endl;
}


void CExpressionNodeNil::GenerateSymbolTables(SymbolTableNode parent)
{
    if (NULL == parent) return; // TODO: Throw an exception

    m_localSymbolTable = parent;
}

string CExpressionNodeNil::GetExpressionType()
{
    return VAR_NIL_ENTRY_TYPE;
}

Value*  CExpressionNodeNil::Codegen(IRBuilder<>* builder)
{
	//TODO: treating nil just like a bool false right now this might not work
	return ConstantInt::get(Type::Int1Ty, 0);
}

