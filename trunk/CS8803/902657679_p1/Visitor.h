// Ken Hartsook
// CS 8803 KBA
// Fall 2009
// Project 1

#ifndef VISITOR_H
#define VISITOR_H

#include "typedefs.h"

class NounFrame;
class ActionFrame;

//-----------------------------------------------------------------------------

class Visitor
{
public:
	virtual void visit(NounFrame & f) = 0;
	virtual void visit(ActionFrame & af) = 0;
};

//-----------------------------------------------------------------------------

class VisitorTree : Visitor
{
public:
	virtual void visit(NounFrame & f);
	virtual void visit(ActionFrame & f);

protected:
	KBMarked marked;
};

//-----------------------------------------------------------------------------

class VisitorPrint : Visitor
{
public:

	virtual void visit(NounFrame & f);
	virtual void visit(ActionFrame & f);

};

#endif