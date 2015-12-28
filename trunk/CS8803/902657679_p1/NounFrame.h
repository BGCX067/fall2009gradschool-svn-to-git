// Ken Hartsook
// CS 8803 KBA
// Fall 2009
// Project 1

#ifndef NOUN_FRAME_H
#define NOUN_FRAME_H

#include <string>
#include <vector>

#include "AbstractFrame.h"
#include "ActionFrame.h"

using namespace std;

enum TYPE;
enum ROLE;
class NounFrameIterator;

struct connection
{
	string action;
	AbstractFrame * af;
	TYPE type;
	ROLE role;
};

struct slot
{
	string name;
	string value;

	slot(string n, string v)
		: name(n), value(v)
	{}
};

//-----------------------------------------------------------------------------
//	NounFrame
//-----------------------------------------------------------------------------

class NounFrame : public AbstractFrame
{
public:

	string name;
	vector<slot> slots;
	vector<connection> connections;

	virtual void accept(Visitor& v);

	virtual FrameIterator* begin();
	virtual FrameIterator* end();

	virtual void setSlot(string slot, string filler);
};

//-----------------------------------------------------------------------------
//	NounFrameIterator
//-----------------------------------------------------------------------------

class NounFrameIterator : public FrameIterator
{
public:
	NounFrameIterator(NounFrame* cur, int p = 0);
	virtual ~NounFrameIterator();

	virtual AbstractFrame* operator*();
	virtual const AbstractFrame* operator*() const;

	virtual FrameIterator& operator++();

protected:

	virtual AbstractFrame* getFrame() const;

	NounFrame* frame;
	int pos;
};

#endif