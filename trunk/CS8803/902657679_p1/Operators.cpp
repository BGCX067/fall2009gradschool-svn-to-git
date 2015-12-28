// Ken Hartsook
// CS 8803 KBA
// Fall 2009
// Project 1

#ifndef OPERATORS_CPP
#define OPERATORS_CPP

#include <fstream>

#include "Operators.h"

map<string, Operator>
Operators::m;

void
Operators::initialize(char* file)
{
	fstream fs(file, fstream::in);
	while (!fs.eof())
	{
		char buffer[100];
		fs.getline(buffer, 100);
		if (strcmp(buffer,"") == 0 || buffer[0] == '#')
		{
			continue;
		}
		else
		{
			string action(buffer);
			Operator oper(action);

			fs.getline(buffer, 100);
			while (strcmp(buffer,"") != 0)
			{
				//fs.getline(buffer, 100);
				char * tok = strtok(buffer, " \t");
				if (strcmp(tok, "pre") == 0)
				{
					tok = strtok(0, " \t");
					string noun(tok);
					tok = strtok(0, " \t");
					string slot(tok);
					tok = strtok(0, " \t");
					string filler(tok);
					Condition c(noun, slot, filler);
					oper.pre.push_back(c);
				}
				else if (strcmp(tok, "post") == 0)
				{
					tok = strtok(0, " \t");
					string noun(tok);
					tok = strtok(0, " \t");
					string slot(tok);
					tok = strtok(0, " \t");
					string filler(tok);
					Condition c(noun, slot, filler);
					oper.post.push_back(c);
				}
				else
				{
					throw "Bad Operators file - cond. must be pre or post";
				}
				fs.getline(buffer, 100);
			}
			Operators::m[action] = oper;
		}
			
	}
	fs.close();
}

#endif