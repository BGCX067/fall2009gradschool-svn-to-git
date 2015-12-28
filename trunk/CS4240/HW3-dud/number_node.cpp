#include "number_node.h"
#include <string>
using namespace std;

CNumberNode::CNumberNode(yyvalType* yyvaltype)
{
	m_value = atof(yyvaltype->value);
	m_linenum = yyvaltype->linenum;
}
CNumberNode::~CNumberNode()
{
}


double CNumberNode::GetValue()
{
	return m_value;
}

void CNumberNode::PrintNode(ostream& file, int tabCount)
{
	PrintTabs(file, tabCount);
	file << "( " << m_value << " )" << endl;


}


Value*  CNumberNode::Codegen()
{
	return ConstantFP::get(Type::DoubleTy, m_value);
}



void CNumberNode::GenerateSymbolTables(SymbolTableNode parent)
{
    if (NULL == parent) return; // TODO: Throw an exception

    m_localSymbolTable = parent;
}
