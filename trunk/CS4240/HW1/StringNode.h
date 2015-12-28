/*
  Puyan Lotfi
  CS4240
  Homework 1: Lua Parser
  Nat Clark
*/

#pragma once

#include <string>

class StringNode : public ParseTreeNode
{
public:
    StringNode (int lineNumber = 0, std::string value = "FuBar") :
        ParseTreeNode("String", lineNumber, true), 
        m_value("\"" + value + "\"") { }
    virtual ~StringNode () { }
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
    std::string m_value;

};
