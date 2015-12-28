/*
  Puyan Lotfi
  CS4240
  Homework 1: Lua Parser
  Nat Clark
*/

#pragma once

#include <vector>
#include <string>
#include "IParseTreeNode.h"

class ParseTreeNode : public IParseTreeNode
{
public:
    ParseTreeNode(std::string nodeType, int lineNumber = 0, bool isTerminal = false) :
        m_nodeType(nodeType) ,
        m_lineNumber(lineNumber), 
        m_isTerminal(isTerminal) {}
    virtual ~ParseTreeNode() { }
    virtual int getLineNumber() { return m_lineNumber; }
    virtual void addNodeRight(IParseTreeNode* node);
    virtual std::string generateOutputFormat();
    virtual bool isTerminal();

protected:
    int m_lineNumber;
    std::string m_nodeType;
    bool m_isTerminal;
    std::vector<IParseTreeNode*> m_innerNodes;
    
};
