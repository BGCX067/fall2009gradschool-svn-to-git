/*
  Puyan Lotfi
  CS4240
  Homework 1: Lua Parser
  Nat Clark
*/

#pragma once

#include <string>
#include "typedefs.h"

interface IParseTreeNode
{
    virtual void addNodeRight(IParseTreeNode* node) = 0;
    virtual std::string generateOutputFormat() = 0;
    virtual bool isTerminal() = 0;
    virtual int getLineNumber() = 0;
};
