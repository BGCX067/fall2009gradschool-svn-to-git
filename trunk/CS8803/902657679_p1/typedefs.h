// Ken Hartsook
// CS 8803 KBA
// Fall 2009
// Project 1

#ifndef TYPEDEFS_H
#define TYPEDEFS_H

#include<ostream>
#include<string>
#include<vector>
#include<map>

class AbstractFrame;
class AbstractFrame;
class NounFrame;

using namespace std;

enum TYPE
{
	FACT, EVENT, FRAME
};

enum ROLE
{
	AGENT, OBJECT, LOC, COAGENT, TIME, NUM_ROLES
};

struct KBMarked
{
	map<AbstractFrame*,bool> m;
};

struct Condition
{
	string curRole;
	string slot;
	string filler;

	Condition(string r, string s, string f)
		: curRole(r), slot(s), filler(f)
	{}
};

struct Operator
{
	string action;
	vector<Condition> pre;
	vector<Condition> post;

	Operator() {}

	Operator(string a)
		: action(a)
	{}
};

#endif