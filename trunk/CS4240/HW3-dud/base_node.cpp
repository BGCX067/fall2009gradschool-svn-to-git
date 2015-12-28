#include "base_node.h"

CBaseNode::CBaseNode()
{
    m_localSymbolTable = NULL;
}

CBaseNode::~CBaseNode()
{
}


int CBaseNode::GetLineNum()
{
	return m_linenum;
}

void CBaseNode::PrintTabs(ostream& file, int tabCount)
{
	int i;
	for(i=0; i<tabCount; i++)
	{
		file << "\t";
	}
}

