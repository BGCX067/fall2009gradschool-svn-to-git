#ifndef KNOWLEDGE_BASE_H
#define KNOWLEDGE_BASE_H

#include <map>
#include <string>

#include "NounFrame.h"
#include "ActionFrame.h"

// Singleton
class KB
{
public:
	static map<string,NounFrame> nouns;
	static map<string,ActionFrame*> facts;
	static map<string,ActionFrame*> events;

	static void initialize();
	static void cleanup();
};

#endif