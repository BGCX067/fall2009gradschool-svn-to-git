#include "variable_node_prefix_dot.h"

CVariableNodePrefixDot::CVariableNodePrefixDot(PrefixNode prefix, NameNode name)
{
	m_prefix = prefix;
	m_name = name;
}

CVariableNodePrefixDot::~CVariableNodePrefixDot()
{
}


PrefixNode CVariableNodePrefixDot::GetPrefix()
{
	return m_prefix;
}

NameNode CVariableNodePrefixDot::GetName()
{
	return m_name;
}


void CVariableNodePrefixDot::PrintNode(ostream& file, int tabCount)
{
	PrintTabs(file, tabCount);
	file << "( Variable " << endl;

	m_prefix->PrintNode(file, tabCount+1);
	m_name->PrintNode(file, tabCount+1);

	PrintTabs(file, tabCount);
	file << ")" << endl;
}

void CVariableNodePrefixDot::GenerateSymbolTables(SymbolTableNode parent)
{
    if (NULL == parent)
    {
        m_prefix->GenerateSymbolTables(NULL);
        m_name->GenerateSymbolTables(NULL);
        return; // TODO: Throw an exception
    }

    m_localSymbolTable = parent;

    m_prefix->GenerateSymbolTables(m_localSymbolTable);
    m_name->GenerateSymbolTables(m_localSymbolTable);
}

list<BaseNode> CVariableNodePrefixDot::GetChildren()
{
    list<BaseNode> children;
    children.push_front(m_prefix);
    children.push_front(m_name);
    return children;
}

Value* CVariableNodePrefixDot::Codegen(IRBuilder<>* builder, bool locationOnly)
{
	std::cout << "tables are NOT supported" << endl;
	return NULL;
}

