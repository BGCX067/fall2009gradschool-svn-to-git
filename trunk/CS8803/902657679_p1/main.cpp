// Ken Hartsook
// CS 8803 KBA
// Fall 2009
// Project 1

#define _CRTDBG_MAP_ALLOC

#include<iostream>
#include<fstream>
#include<string>
#include<sstream>

#include<vector>
#include<map>

#include "typedefs.h"
#include "AbstractFrame.h"
#include "ActionFrame.h"
#include "NounFrame.h"
#include "ActionHolder.h"
#include "KnowledgeBase.h"
#include "Operators.h"
#include "Visitor.h"

#ifdef WIN32
	#include <stdlib.h>
	#include <crtdbg.h>
	#ifdef _DEBUG
		#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
		#define new DEBUG_NEW
	#endif
#endif

using namespace std;

//-----------------------------------------------------------------------------

// SET THESE CONSTANTS

char FACTS[] = "proj1facts.txt";
char EVENTS[] = "proj1events.txt";
char OPERATORS[] = "operators.txt";

//-----------------------------------------------------------------------------

void readInputFiles(vector<ActionHolder> & actionHolders, char* FACTS, char* EVENTS);
void printCausalChains(vector<ActionHolder> & actionHolders);
bool queryKb();
int dfs(AbstractFrame* af, KBMarked & marked, vector<AbstractFrame*> & tree);
vector< vector<AbstractFrame*> > get_trees();
void solve(vector<ActionHolder> & actionHolders, int i, vector<bool> & marked, vector<int> & chain);

//-----------------------------------------------------------------------------

// main
//
// main() accomplishes three tasks:
//	1. it reads in the input files
//  2. tests operators on events in queue to generate causal chains
//	3. provides user with a prompt for querying the knowledge base
int main (int argc, char * argv[])
{

	// Memory leak checker
	#ifdef WIN32
		_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	#endif

	try
	{
		Operators::initialize(OPERATORS);
		KB::initialize();

		vector<ActionHolder> actionHolders;
		readInputFiles(actionHolders, FACTS, EVENTS);

		/*
		for (int i = 0; i < actionHolders.size(); i++)
			ActionFrame * af = new ActionFrame(actionHolders[i]);
		vector< vector<AbstractFrame*> > trees = get_trees();
		*/

		printCausalChains(actionHolders);

		bool cont = true;
		do
		{
			cont = queryKb();
		} while (cont);

	}
	catch (exception e)
	{
		cout << e.what() << endl;
	}

	KB::cleanup();

	return 0;
}

//-----------------------------------------------------------------------------

// readInputFiles
//
// Reads facts and events from the input files
void readInputFiles(vector<ActionHolder> & actionHolders, char* FACTS, char* EVENTS)
{
	try
	{
		fstream fs(FACTS, fstream::in);
		while (!fs.eof())
		{
			char buffer[100];
			fs.getline(buffer, 100);
			if (strcmp(buffer,""))
			{
				ActionHolder ah(buffer, FACT);
				ah.apply();
				ActionFrame* af = new ActionFrame(ah); //adds self to KB
			}
		}
		fs.close();
	}
	catch (...)
	{
		std::cout << "Error reading file" << std::endl;
	}

	try
	{
		fstream fs2(EVENTS, fstream::in);
		while (!fs2.eof())
		{
			char buffer[100];
			fs2.getline(buffer, 100);
			if (strcmp(buffer,""))
			{
				ActionHolder ah(buffer, EVENT);
				actionHolders.push_back(ah);
			}
		}
		fs2.close();
	}
	catch (...)
	{
        std::cout << "Error reading file" <<    std::endl;
	}
}

//-----------------------------------------------------------------------------

// printCausalChains
//
// Applies operators in order to find causal chains amongst events in the
//	actionHolders queue
void printCausalChains(vector<ActionHolder> & actionHolders)
{
	vector<bool> marked;
	for (int i = 0; i < actionHolders.size(); i++)
	{
		marked.push_back(false);
	}

	bool progress = true;
	while (progress)
	{
		progress = false;

		// find all events whose preconditions match the global start state
		// these are the beginnings of causal chains
		vector<int> initials;
		for (int i = 0; i < actionHolders.size(); i++)
		{
			// legal chain starter - don't apply it yet
			if (actionHolders[i].isValid() && !marked[i])
			{
				progress = true;
				marked[i] = true;
				initials.push_back(i);
			}
		}

		// find as many chains as we can legitimately
		for (int i = 0; i < initials.size(); i++)
		{
			vector<int> chain;

			// solve applies the actions effects to the world
			solve(actionHolders, initials[i], marked, chain);

			cout << "---------------------------------------------------" << endl;
			system("pause");
			cout << "---------------------------------------------------" << endl;
		}

		// if no progress, we force remaining events to start chains
		if (!progress)
		{
			for (int i = 0; i < actionHolders.size(); i++)
			{
				if (marked[i])
					continue;

				vector<int> chain;
				solve(actionHolders, i, marked, chain);
				progress = true;

				cout << "---------------------------------------------------" << endl;
				system("pause");
				cout << "---------------------------------------------------" << endl;
			}
		}
	}
}

//-----------------------------------------------------------------------------

// queryKb
//
// Prompts the user for a noun or action for which they'd like to see the
//	frame, and then displays all matching frames.
bool queryKb()
{
	char buffer[100];
	cout << endl << endl << endl << endl << endl << endl << endl;
	cout << "Please enter a noun or action title to display, or \"quit\": " << endl;
	cin.getline(buffer, 100);
	if (strcmp(buffer,"quit") == 0)
	{
		return 0;
	}
	cout << endl;

	string title(buffer);
	VisitorPrint v;

	map<string,NounFrame>::iterator iter = KB::nouns.begin();
	for (iter; iter != KB::nouns.end(); ++iter)
	{
		if (iter->first == title)
		{
			v.visit(iter->second);
		}
	}

	map<string,ActionFrame*>::iterator iter2 = KB::events.begin();
	for (iter2; iter2 != KB::events.end(); ++iter2)
	{
		if (iter2->second->action == title)
		{
			v.visit(*iter2->second);
		}
	}

	map<string,ActionFrame*>::iterator iter3 = KB::facts.begin();
	for (iter3; iter3 != KB::facts.end(); ++iter3)
	{
		if (iter3->second->action == title)
		{
			v.visit(*iter3->second);
		}
	}

	cout << "---------------------------------------------------" << endl;
	system("pause");
	cout << "---------------------------------------------------" << endl;

	return 1;
}

//-----------------------------------------------------------------------------

// dfs
//
// Marks nodes in the knowledge base as found and adds them to the current tree
//	being searched
int dfs(AbstractFrame* af, KBMarked & marked, vector<AbstractFrame*> & tree)
{
	map<AbstractFrame*,bool>::iterator it = marked.m.find(af);
	if (it != marked.m.end())
		return 0;
	marked.m[af] = true;
	tree.push_back(af);

	int sum = 1;

	FrameIteratorBridge i (af->begin());
	FrameIteratorBridge e (af->end());
	for (i; i != e; ++i)
	{
		sum += dfs(*i, marked, tree);
	}

	return sum;
}

//-----------------------------------------------------------------------------

// get_trees()
//
// Examines all connected links in the knowledge base and locates disconnected
//	graphs among them
// Return value is a vector of vectors, where each vector is a connected
//	subgraph and its items are the frames in that subgraph
vector< vector<AbstractFrame*> > get_trees()
{
	vector< vector<AbstractFrame*> > trees;
	int index = 0;
	vector<AbstractFrame*> temp;
	trees.push_back(temp);

	KBMarked marked;

	map<string,NounFrame>::iterator it = KB::nouns.begin();
	for (it; it != KB::nouns.end(); it++)
	{
		int result = dfs(&(it->second), marked, trees[index]);
		if (result > 0)
		{
			index++;
			vector<AbstractFrame*> temp;
			trees.push_back(temp);
		}
	}

	return trees;
}

//-----------------------------------------------------------------------------

// solve
//
// Cycles through the current world state and attempts to find events in the
//	list which can be applied; these are then added to a causal chain
void solve(vector<ActionHolder> & actionHolders, int i, vector<bool> & marked, vector<int> & chain)
{
	// apply initial event
	cout << actionHolders[i].action << endl;
	actionHolders[i].apply();
	cout << endl;

	marked[i] = true;
	ActionFrame * af = new ActionFrame(actionHolders[i]);

	chain.push_back(i);

	bool progress = false;
	do
	{
		progress = false;
		for (int i = 0; i < actionHolders.size(); i++)
		{
			if (marked[i])
				continue;
			if (actionHolders[i].isValid())
			{
				cout << actionHolders[i].action << endl;
				actionHolders[i].apply();
				cout << endl;

				marked[i] = true;
				progress = true;
				ActionFrame * af = new ActionFrame(actionHolders[i]);

				chain.push_back(i);
				break;
			}
		}

	} while (progress == true);

	// Can't add anything else to this chain, so we assume it is done
}