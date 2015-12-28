// Ken Hartsook
// CS 8803 KBA
// Fall 2009
// Project 1

#ifndef OPERATORS_H
#define OPERATORS_H

#include <vector>
#include <map>
#include <string>

#include "typedefs.h"

using namespace std;

class Operators
{
public:

	static void initialize(char* file);
	static map<string,Operator> m;

};

#endif