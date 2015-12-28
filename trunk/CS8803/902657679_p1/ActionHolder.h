// Ken Hartsook
// CS 8803 KBA
// Fall 2009
// Project 1

#ifndef ACTION_HOLDER_H
#define ACTION_HOLDER_H

#include <string>
#include <vector>

#include "typedefs.h"

using namespace std;

class ActionHolder
{
public:

	ActionHolder(char* str, TYPE type);

	int id;
	string action;
	vector<string> roles[NUM_ROLES];
	TYPE type;

	void parseNouns(istringstream& buffer, char* sbuff, ROLE role);

	bool isValid();
	bool isValid(const NounFrame & noun, Condition c);

	bool lookupValue(string & filler);

	void apply();

	ROLE getRole(string s);

};

#endif