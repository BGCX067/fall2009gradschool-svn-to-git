#include <string>
#include <utility>
#include <map>

using namespace std;

#ifndef SYMBOL_CELL_H
#define SYMBOL_CELL_H
// (number (action (agent, object, location, co-agent, time)))
struct SymbolCell
{
    char* value;
    SymbolCell* next;
    SymbolCell* sub;
};

#endif // SYMBOL_CELL_H
