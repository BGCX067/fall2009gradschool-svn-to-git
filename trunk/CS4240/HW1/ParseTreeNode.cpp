/*
  Puyan Lotfi
  CS4240
  Homework 1: Lua Parser
  Nat Clark
*/

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "ParseTreeNode.h"

void ParseTreeNode::addNodeRight(IParseTreeNode* node)
{
    m_innerNodes.push_back(node);
}

std::string ParseTreeNode::generateOutputFormat()
{
    std::ostringstream ost;
    ost << "(" << m_nodeType << " " << m_lineNumber << " ";
    for (int i = 0; i < m_innerNodes.size(); i++)
    {
        if (NULL != m_innerNodes[i])
        {
            ost << m_innerNodes[i]->generateOutputFormat();
        }
        else
        {
            std::cout << "Bad node " << __LINE__ << std::endl;
        }
    }
    
    ost << ")";
    
    return ost.str();
}

bool ParseTreeNode::isTerminal()
{
    return m_isTerminal;
}
