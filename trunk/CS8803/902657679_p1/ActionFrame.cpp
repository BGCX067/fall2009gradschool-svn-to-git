#ifndef ACTION_FRAME_CPP
#define ACTION_FRAME_CPP

#include <sstream>

#include "ActionFrame.h"
#include "KnowledgeBase.h"

//-----------------------------------------------------------------------------
//	ActionFrame
//-----------------------------------------------------------------------------

ActionFrame::ActionFrame(const ActionHolder & ah)
{
	initialize(ah);
}

//-----------------------------------------------------------------------------

ActionFrame::ActionFrame(char* str, TYPE type)
{
	ActionHolder ah(str, type);
	initialize(ah);
}

//-----------------------------------------------------------------------------

void
ActionFrame::initialize(const ActionHolder & ah)
{
	this->action = ah.action;
	this->type = ah.type;

	for (int j = 0; j < NUM_ROLES; j++)
		for (int i = 0; i < ah.roles[j].size(); i++)
			this->roles[j].push_back(addNoun(ah.roles[j][i], this, AGENT));

	map<string, ActionFrame*> * mp;
	if (this->type == FACT)
	{
		mp = &KB::facts;
	}
	else if (this->type == EVENT)
	{
		mp = &KB::events;
	}
	else
	{
		throw;
	}

	// ensure uniqueness of key
	map<string, ActionFrame*> & m = *mp;
	if (m.find(this->action) == m.end())
	{
		m[this->action] = this;
	}
	else
	{
		int i = 1;
		stringstream num;
		num << i;
		string next = action + num.str();
		while (m.find(next) != m.end())
		{
			i++;
			num << i;
			next = action + num.str();
		}
		m[next] = this;
	}
}

//-----------------------------------------------------------------------------

NounFrame*
ActionFrame::addNoun(string key, ActionFrame* af, ROLE role)
{
	NounFrame & f = KB::nouns[key];
	f.name = key;
	connection fi;
	fi.action = af->action;
	fi.af = af;
	fi.role = role;
	fi.type = af->type;
	f.connections.push_back(fi);

	return &f;
}

//-----------------------------------------------------------------------------

void
ActionFrame::print(ostream& out)
{
	/*
	out << "---Frame---" << endl;
	out << "Action:\t\t" << action << endl;
	out << "Agents:\t\t";
	for (int i = 0; i < agents.size(); i++)
		out << agents[i] << ", ";
	out << endl;
	out << "Objects:\t\t";
	for (int i = 0; i < objects.size(); i++)
		out << objects[i] << ", ";
	out << endl;
	out << "Locations:\t\t";
	for (int i = 0; i < locations.size(); i++)
		out << locations[i] << ", ";
	out << endl;
	out << "Coagents:\t\t";
	for (int i = 0; i < coagents.size(); i++)
		out << coagents[i] << ", ";
	out << endl;
	out << "Times:\t\t";
	for (int i = 0; i < times.size(); i++)
		out << times[i] << ", ";
	out << endl << endl;
	*/
}

//-----------------------------------------------------------------------------

void
ActionFrame::accept(Visitor & v)
{
	v.visit(*this);
}

//-----------------------------------------------------------------------------

FrameIterator*
ActionFrame::begin()
{
	return new ActionFrameIterator(this);
}

//-----------------------------------------------------------------------------

FrameIterator*
ActionFrame::end()
{
	return new ActionFrameIterator(this, -1);
}

//-----------------------------------------------------------------------------
//	ActionFrameIterator
//-----------------------------------------------------------------------------

ActionFrameIterator::ActionFrameIterator(ActionFrame* cur, int p, ROLE r)
{
	frame = cur;
	role = r;
	pos = p;
	if (p < 0)
		role = NUM_ROLES;
	safety();
}

//-----------------------------------------------------------------------------

ActionFrameIterator::~ActionFrameIterator()
{

}

//-----------------------------------------------------------------------------

AbstractFrame*
ActionFrameIterator::operator*()
{
	if (role >= 0 && role < NUM_ROLES)
	{
		return frame->roles[role][pos];
	}
	else
	{
		return 0;
	}
}

//-----------------------------------------------------------------------------

const AbstractFrame*
ActionFrameIterator::operator*() const
{
	if (role >= 0 && role < NUM_ROLES)
	{
		return frame->roles[role][pos];
	}
	else
	{
		return 0;
	}
}

//-----------------------------------------------------------------------------

FrameIterator&
ActionFrameIterator::operator++()
{
	pos++;
	safety();
	return *this;
}

//-----------------------------------------------------------------------------

AbstractFrame*
ActionFrameIterator::getFrame() const
{
	return frame;
}

//-----------------------------------------------------------------------------

// Make sure that we are always on a valid index of the vectors
void
ActionFrameIterator::safety()
{
	if (role < 0 || role >= NUM_ROLES)
	{
		pos = -1;
		role = NUM_ROLES;
		return;
	}
	while (pos >= frame->roles[this->role].size())
	{
		pos = 0;
		role = (ROLE)(role + 1);
		if (role == NUM_ROLES)
		{
			pos = -1;
			break;
		}
	}
}


#endif