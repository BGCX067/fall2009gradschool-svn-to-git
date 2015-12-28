// Ken Hartsook
// CS 8803 KBA
// Fall 2009
// Project 1

#ifndef ACTION_FRAME_H
#define ACTION_FRAME_H

#include <string>
#include <vector>
#include <ostream>

#include "AbstractFrame.h"
#include "ActionHolder.h"

// forward declarations
enum TYPE;

using namespace std;

//-----------------------------------------------------------------------------
//	ActionFrame
//-----------------------------------------------------------------------------

class ActionFrame : public AbstractFrame
{
public:

	ActionFrame(char* str, TYPE type);
	ActionFrame(const ActionHolder & ah);

	int id;
	string action;
	vector<NounFrame*> roles[NUM_ROLES];
	TYPE type;

	virtual void print(ostream& out);
	virtual void accept(Visitor& v);

	virtual FrameIterator* begin();
	virtual FrameIterator* end();

protected:

	void initialize(const ActionHolder & ah);

	//void parseNouns(istringstream& buffer, char* sbuff, ROLE role);
	static NounFrame* addNoun(string key, ActionFrame* af, ROLE role);

};

//-----------------------------------------------------------------------------
//	ActionFrameIterator
//-----------------------------------------------------------------------------

class ActionFrameIterator : public FrameIterator
{
public:
	ActionFrameIterator(ActionFrame* cur, int p = 0, ROLE r = AGENT);
	virtual ~ActionFrameIterator();

	virtual AbstractFrame* operator*();
	virtual const AbstractFrame* operator*() const;

	virtual FrameIterator& operator++();

protected:

	virtual AbstractFrame* getFrame() const;
	ActionFrame* frame;

	ROLE role;
	int pos;

	virtual void safety();
};

#endif