/*
  Puyan Lotfi
  CS4240
  Homework 1: Lua Parser
  Nat Clark
*/

#pragma once

#include <string>
#include <sstream>

class NumberNode : public ParseTreeNode
{
public:
    NumberNode (int lineNumber = 0, float value = 0.0) :
        ParseTreeNode("Number", lineNumber, true), 
        m_value(value) { }
    virtual ~NumberNode () { }
    virtual int getLineNumber() { return m_lineNumber; }
    virtual std::string generateOutputFormat()
    {
            std::ostringstream ost;
            ost << "(" << m_nodeType << " " << m_lineNumber << " ";
            ost << m_value;
            ost << ")";
            
            return ost.str();
    }
    
private:
    float m_value;

};
