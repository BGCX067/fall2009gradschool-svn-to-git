// Ken Hartsook
// CS 8803 KBA
// Fall 2009
// Project 1

#ifndef KNOWLEDGE_BASE_CPP
#define KNOWLEDGE_BASE_CPP

#include "KnowledgeBase.h"

map<string,NounFrame> KB::nouns;
map<string,ActionFrame*> KB::facts;
map<string,ActionFrame*> KB::events;

void
KB::initialize()
{
	{
	NounFrame & noun = nouns["robbers"];
	slot s("inCar","true");
	noun.slots.push_back(s);
	}

	{
	NounFrame & noun = nouns["dog"];
	slot s("location","market");
	noun.slots.push_back(s);
	}

	{
	NounFrame & noun = nouns["employee"];
	slot s("inCar","false");
	noun.slots.push_back(s);
	}

	{
	NounFrame & noun = nouns["robert-e-ford"];
	slot s("wants-to-go","store");
	noun.slots.push_back(s);
	}

}

void 
KB::cleanup()
{
	map<string,ActionFrame*>::iterator i = KB::facts.begin();
	for (i; i != KB::facts.end(); i++)
		delete (*i).second;
	i = KB::events.begin();
	for (i; i != KB::events.end(); i++)
		delete (*i).second;
	KB::nouns.clear();
	KB::facts.clear();
	KB::events.clear();
}

#endif