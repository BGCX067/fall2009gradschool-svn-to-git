// Ken Hartsook
// CS 8803 KBA
// Fall 2009
// Project 1

#ifndef ACTION_HOLDER_CPP
#define ACTION_HOLDER_CPP

#include <iostream>
#include <sstream>

#include "ActionHolder.h"
#include "Operators.h"
#include "KnowledgeBase.h"
#include "NounFrame.h"

//-----------------------------------------------------------------------------

ActionHolder::ActionHolder(char* str, TYPE type)
{
	this->type = type;
	istringstream buffer(str,istringstream::in);
	char trash;
	char sbuff[80];
	char* tok;
	buffer >> trash; // toss away first paren
	buffer >> this->id; // store id number
	buffer >> trash; // next paren
	buffer.get(sbuff, 80, '(');
	buffer.ignore(1);
	this->action = string(sbuff);

	for (int i = 0; i < NUM_ROLES; i++)
		parseNouns(buffer, sbuff, (ROLE)i);
}

//-----------------------------------------------------------------------------

void
ActionHolder::parseNouns(istringstream& buffer, char* sbuff, ROLE role)
{
	buffer.get(sbuff, 80, ',');
	char * tok = strtok(sbuff, " ()");
	while (tok != 0)
	{
		string noun(tok);

		this->roles[role].push_back(noun);

		tok = strtok(0, " ()");
	}
	buffer.ignore(1);
}

//-----------------------------------------------------------------------------

bool
ActionHolder::isValid(const NounFrame & noun, Condition c)
{
	string filler = c.filler;
	if (filler[0] == '%')
	{
		if (lookupValue(filler))
		{
			
		}
		else
		{
			return true;
		}
	}

	for (int i = 0; i < noun.slots.size(); i++)
	{
		if (c.slot == noun.slots[i].name && filler == noun.slots[i].value)
		{
			return true;
		}
		else if (c.slot == noun.slots[i].name && filler != noun.slots[i].value)
		{
			return false;
		}
	}

	// TODO
	// Verify this is what we want to do if we don't have the slot
	return false;
}

//-----------------------------------------------------------------------------

ROLE
ActionHolder::getRole(string s)
{
	if (s == "%AGENT")
		return AGENT;
	if (s == "%OBJECT")
		return OBJECT;
	if (s == "%LOC")
		return LOC;
	if (s == "%COAGENT")
		return COAGENT;
	if (s == "%TIME")
		return TIME;
	throw "Malformed Role string";
}

//-----------------------------------------------------------------------------

bool
ActionHolder::isValid()
{
	Operator o = Operators::m[this->action];
	if (o.action == "")
		return false;

	// go through and verify each precondition
	for (int i = 0; i < o.pre.size(); i++)
	{
		// if referring to a role
		if (o.pre[i].curRole[0] == '%')
		{
			ROLE r = getRole(o.pre[i].curRole);
			for (int j = 0; j < this->roles[r].size(); j++)
			{
				if (KB::nouns.find(roles[r][j]) == KB::nouns.end())
					return false;
				const NounFrame & noun = KB::nouns[this->roles[r][j]];
				if (!isValid(noun, o.pre[i]))
					return false;
			}
		}
		else // referring to a constant
		{
			const NounFrame & noun = KB::nouns[o.pre[i].curRole];
			if (!isValid(noun, o.pre[i]))
				return false;
		}
	}

	return true;
}

//-----------------------------------------------------------------------------

void
ActionHolder::apply()
{
	Operator o = Operators::m[this->action];

	// apply each postcondition
	for (int i = 0; i < o.post.size(); i++)
	{
		const Condition & c = o.post[i];

		// resolve filler value
		// if this postcondition setting is based on a value from the action,
		//	look that value up
		// if it wasn't provided, skip to the next postcondition
		string value = c.filler;
		if (value[0] == '%')
		{
			if (lookupValue(value))
			{

			}
			else
			{
				continue;
			}
		}

		// resolve noun value
		NounFrame * noun;
		if (c.curRole[0] == '%')
		{
			ROLE r = getRole(c.curRole);

			// now apply it to each noun of the specified type
			for (int j = 0; j < this->roles[r].size(); j++)
			{
				noun = &KB::nouns[this->roles[r][j]];
				noun->name = roles[r][j];
				noun->setSlot(c.slot, value);
				cout << "   " << noun->name << " -> " << c.slot << " : " << value << endl;
			}
		}
		else // referring to an atom
		{
			noun = &KB::nouns[c.curRole];
			noun->name = c.curRole;
			noun->setSlot(c.slot, value);
			cout << "   " << noun->name << " -> " << c.slot << " : " << value << endl;
		}
	}
}

//-----------------------------------------------------------------------------

bool
ActionHolder::lookupValue(string & filler)
{
	// TODO
	// Fix all of these so that they don't just pull the first one, but
	//	actually scan the list for a valid match?
	if (filler == "%AGENT")
	{
		if (this->roles[AGENT].size() == 0)
			return false;
		filler = this->roles[AGENT][0];
	}
	else if (filler == "%OBJECT")
	{
		if (this->roles[OBJECT].size() == 0)
			return false;
		filler = this->roles[OBJECT][0];
	}
	else if (filler == "%LOC")
	{
		if (this->roles[LOC].size() == 0)
			return false;
		filler = this->roles[LOC][0];
	}
	else if (filler == "%COAGENT")
	{
		if (this->roles[COAGENT].size() == 0)
			return false;
		filler = this->roles[COAGENT][0];
	}
	else if (filler == "%TIME")
	{
		if (this->roles[TIME].size() == 0)
			return false;
		filler = this->roles[TIME][0];
	}
	else
	{
		throw "Malformed Filler Reference";
	}
}

#endif