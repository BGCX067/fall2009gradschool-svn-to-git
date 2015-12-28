#include "expression_node_dots.h"

CExpressionNodeDots::CExpressionNodeDots()
{
}

CExpressionNodeDots::~CExpressionNodeDots()
{
}

void CExpressionNodeDots::PrintNode(ostream& file, int tabCount)
{
	PrintTabs(file, tabCount);
	file << "( ... )" << endl;
}

void CExpressionNodeDots::GenerateSymbolTables(SymbolTableNode parent)
{
    if (NULL == parent) return; // TODO: Throw an exception

    m_localSymbolTable = parent;
}

string CExpressionNodeDots::GetExpressionType()
{
    EXIT_WITH_ERROR("Currently not supporting vararg type checking.");
}

Value* CExpressionNodeDots::Codegen(IRBuilder<>* builder)
{
	std::cout << "varargs are NOT supported" << endl;
	return NULL;
}

