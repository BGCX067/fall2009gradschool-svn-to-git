/*
(18  (cash( , washington-state-unemployment-check , , , )))
(19  (go-to(robert-e-ford , store , , , )))
(20  (give(robert-e-ford , fake-check , , clerk , )))
(21  (give(robert-e-ford , fake-id , , clerk , )))

(number (action (agent, object, location, co-agent, time)))
*/


%{



#include <iostream>
#include <list>
#include <map>
#include <string>
#include <cstring>
#include "frame.h"
#include "symbol_cell.h"

map<int, string> InitSlotOrderMap()
{
    map<int, string> slotOrderMap;
    slotOrderMap[1] = AGENT;
    slotOrderMap[2] = OBJECT;
    slotOrderMap[3] = LOCATION;
    slotOrderMap[4] = COAGENT;
    slotOrderMap[5] = TIME;
    return slotOrderMap;
}

map<int,string> SlotOrderMap = InitSlotOrderMap();
map<Frame*, map<Frame*, list<MetaFrame*> > >MetaRegistry;
FrameRegistry GlobalFrameRegistry;
FrameRegistry GlobalPlanRegistry;
list<string>  GlobalPlanList;
list<pair<string, string> > subplans;
Frame* currentParentFrame = NULL;
bool queueMeta = false;
bool metaReason2 = false;

// "action"
// "agent"
// "object"
// "location"
// "coagent"
// "time"

using namespace std;

void yyerror(char *);
int yylex();

%}

%union
{
    char* str;
    struct Frame* frame;
    struct SymbolCell* sym;
}

%token COMMA
%token LPAREN
%token RPAREN
%token BLANK
%token <str> SYMBOL

%type <frame> acevent
%type <sym> symbol
%type <sym> symbollist


%start acevents

%%

acevents:
acevent
{

}
| acevent acevents
{

};


acevent:
LPAREN symbol // event number
LPAREN symbol // event action
LPAREN symbollist RPAREN // frame body
RPAREN
RPAREN
{
    LoadSymbolsAsFrames($2, $4, $6);

    delete $2;
    delete $4;
    delete $6;
};

symbollist:
symbol symbollist
{
    SymbolCell* cell = $1;
    cell->next = $2;
    $$ = cell;
}
|
{
    $$ = NULL;
}
;

symbol:
SYMBOL
{
    SymbolCell* cell = new SymbolCell();
    cell->value = $1;
    cell->sub = NULL;
    cell->next = NULL;
    $$ = cell;
}
| COMMA
{
    SymbolCell* cell = new SymbolCell();
    cell->value = strdup(",");
    cell->sub = NULL;
    cell->next = NULL;
    $$ = cell;
}
| symbol LPAREN symbollist RPAREN
{
    SymbolCell* cell = $1;
    cell->sub = $3;
    $$ = cell;
}
|
;
