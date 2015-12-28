// Ken Hartsook
// CS 8803 KBA
// Fall 2009
// Project 1

#ifndef VISITOR_CPP
#define VISITOR_CPP

#include <iostream>
#include <string>

#include "Visitor.h"

#include "NounFrame.h"
#include "ActionFrame.h"
#include "typedefs.h"

using namespace std;

//-----------------------------------------------------------------------------

void
VisitorPrint::visit(NounFrame & f)
{
	cout << "Noun: " << f.name << endl;
	for (int i = 0; i < f.slots.size(); i++)
	{
		cout << "  " << f.slots[i].name << " :: " << f.slots[i].value << endl;
	}
	for (int i = 0; i < f.connections.size(); i++)
	{
		cout << "  Involved-In: " << f.connections[i].action << endl;
	}
	cout << endl;
}

//-----------------------------------------------------------------------------

void
VisitorPrint::visit(ActionFrame & f)
{
	cout << "Action: " << f.action << endl;
	cout << "  Agents:    ";
	for (int i = 0; i < f.roles[AGENT].size(); i++)
		cout << f.roles[AGENT][i]->name;
	cout << endl;
	cout << "  Objects:   ";
	for (int i = 0; i < f.roles[OBJECT].size(); i++)
		cout << f.roles[OBJECT][i]->name;
	cout << endl;
	cout << "  Locations: ";
	for (int i = 0; i < f.roles[LOC].size(); i++)
		cout << f.roles[LOC][i]->name;
	cout << endl;
	cout << "  Coagents:  ";
	for (int i = 0; i < f.roles[COAGENT].size(); i++)
		cout << f.roles[COAGENT][i]->name;
	cout << endl;
	cout << "  Times: ";
	for (int i = 0; i < f.roles[TIME].size(); i++)
		cout << f.roles[TIME][i]->name;
	cout << endl;
	cout << endl;
}

#endif