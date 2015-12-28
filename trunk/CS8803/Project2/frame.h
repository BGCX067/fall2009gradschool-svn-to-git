#include <string>
#include <map>
#include "symbol_cell.h"

using namespace std;

#ifndef FRAME_H
#define FRAME_H
// (number (action (agent, object, location, co-agent, time)))

#define ACTION   "action"
#define AGENT    "agent"
#define OBJECT   "object"
#define LOCATION "location"
#define COAGENT  "co-agent"
#define TIME     "time"

struct Frame
{
    Frame();
    virtual ~Frame();
    void GetAllAssociatedFrames();
    void PrintFrame();
    void SetActionSlot  (string action)      { fillers[ACTION]   = action;   }
    void SetAgentSlot   (string agent)       { fillers[AGENT]    = agent;    }
    void SetObjectSlot  (string object)      { fillers[OBJECT]   = object;   }
    void SetLocationSlot(string location)    { fillers[LOCATION] = location; }
    void SetCoAgentSlot (string coagent)     { fillers[COAGENT]  = coagent;  }
    void SetTimeSlot    (string time)        { fillers[TIME]     = time;     }
    map<string,string> fillers;
    list<string> subframes;
    bool   startsSubplan;
    bool   hasIntention;
    bool subplanFileLink;
    string next_frame;
    string frame_name;
    string frame_group;
};

struct MetaFrame
{
    list<Frame*> preds;
    list<Frame*> succs;
    string reason;
    void print()
    {
        for (list<Frame*>::iterator iter = preds.begin();
             iter != preds.end();
             iter++)
        {
            cout << (*iter)->fillers[ACTION] << endl;
        }

        cout << reason << endl;

        for (list<Frame*>::iterator iter = succs.begin();
             iter != succs.end();
             iter++)
        {
            cout << (*iter)->fillers[ACTION] << endl;
        }
    }
};

typedef map<string, list<Frame*> > FrameRegistry;
void printIntentionFrame(Frame* intentionFrame, string frequentAgent, string planAgentType, string frequentobject, string secondHighestAgent);
void LoadSymbolsAsFrames(SymbolCell* event_metadata, SymbolCell* event_action, SymbolCell* event_data);
void PrintFrames(list<Frame*> frames);
void PrintGlobalFrameRegistry();
void PrintGlobalPlanRegistry();
void MatchPlansWithEvents();

#endif // FRAME_H
