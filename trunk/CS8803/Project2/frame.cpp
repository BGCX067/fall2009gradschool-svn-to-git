#include <iostream>
#include <string>
#include <map>
#include <list>
#include <utility>
#include <sstream>
#include <ostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include "frame.h"


using namespace std;

typedef map<Frame*, map<Frame*, list<MetaFrame*> > >  METAAAAA;
typedef map<Frame*, list<MetaFrame*> >  METAAAA;

extern map<int,string> SlotOrderMap;
extern map<Frame*, map<Frame*, list<MetaFrame*> > > MetaRegistry;
extern FrameRegistry GlobalFrameRegistry;
extern FrameRegistry GlobalPlanRegistry;
extern list<string>  GlobalPlanList;
extern list<pair<string, string> > subplans;
extern Frame* currentParentFrame;
extern bool queueMeta;
extern bool metaReason2;
Frame* prev = NULL;

list<string> globalMetaInfo;

int tabcount = 0;

void printTabs()
{
    for (int i = 0; i<tabcount; i++)
    {
        cout << "\t";
    }
}

Frame::Frame()
{
    next_frame = "";
    frame_name = "";
    frame_group = "";
}

Frame::~Frame()
{
}

void clearMeta()
{
    cout << "META REASONER SAYS: " << endl;

    for (list<string>::iterator iter = globalMetaInfo.begin();
            iter != globalMetaInfo.end();
            iter++)
    {
        cout << "\n\t - " << *iter;
    }

    globalMetaInfo.clear();
}

void printMeta(string str)
{
    if (!queueMeta)
    {
        cout << endl;
        cout << "\t\t\t\t\t\t\t\t\t\t\t\t";
        cout << "   META REASONER SAYS: " << str;
    }
    else
    {
        for (list<string>::iterator iter = globalMetaInfo.begin();
                iter != globalMetaInfo.end();
                iter++)
        {
            if (!strcmp(str.c_str(), (*iter).c_str()))
            {
                return;
            }
        }

        globalMetaInfo.push_back(str);
    }
}

void Frame::PrintFrame()
{


    if (prev && metaReason2)
    {
        METAAAAA::iterator findPrev = MetaRegistry.find(prev);

        if (findPrev != MetaRegistry.end())
        {
            METAAAA::iterator findCurr = MetaRegistry[prev].find(this);

            if (findCurr != MetaRegistry[prev].end())
            {
                cout << endl;
                cout << "\t\t\t\t\t\t\t\t\t\t\t\t";
                cout << "   ORACLE SAYS: " << fillers[AGENT] << " " << (MetaRegistry[prev])[this].front()->reason;
            }
        }
    }

    prev = this;

    cout << endl;


    printTabs();
    cout << "( " << frame_name << " " << next_frame << " " << frame_group << " ";
    cout << " ( " << fillers[ACTION] << ","
        << " ( "
        << fillers[AGENT] << ","
        << fillers[OBJECT] << ","
        << fillers[LOCATION] << ","
        << fillers[COAGENT] << ","
        << fillers[TIME] << ","
        << " ))) ";

}

void Frame::GetAllAssociatedFrames()
{
    cout << "All associated frames" << endl;

    map<Frame*, bool> visitedFrames;
    list<string> keysToVisit;

    for (map<string,string>::iterator fillersIter = fillers.begin();
            fillersIter != fillers.end();
            fillersIter++)
    {
        if (fillersIter->first != ACTION)
            keysToVisit.push_back(fillersIter->second);
    }

    visitedFrames[this] = true;

    PrintFrame();

    while (true)
    {
        list<string> visitedKeys;

        if (keysToVisit.size() <= 0) break;

        for (list<string>::iterator keysToVisitIter = keysToVisit.begin();
                keysToVisitIter != keysToVisit.end();
                keysToVisitIter++)
        {

            list<Frame*> frames = GlobalFrameRegistry[*keysToVisitIter];

            visitedKeys.push_back(*keysToVisitIter);

            for (list<Frame*>::iterator framesIter = frames.begin();
                    framesIter != frames.end();
                    framesIter++)
            {
                map<Frame*, bool>::iterator visitedFramesIter = visitedFrames.find(*framesIter);

                if (visitedFramesIter == visitedFrames.end())
                {
                    visitedFrames[*framesIter] = true;
                    (*framesIter)->PrintFrame();

                    for (map<string,string>::iterator fillersIter = (*framesIter)->fillers.begin();
                            fillersIter != (*framesIter)->fillers.end();
                            fillersIter++)
                    {
                        if (fillersIter->first != ACTION)
                            keysToVisit.push_back(fillersIter->second);
                    }

                }
            }
        }

        for (list<string>::iterator visitedKeysIter = visitedKeys.begin();
                visitedKeysIter != visitedKeys.end();
                visitedKeysIter++)
        {
            keysToVisit.remove(*visitedKeysIter);
        }


    }
}

void LoadSymbolsAsFrames(SymbolCell* event_metadata, SymbolCell* event_action, SymbolCell* event_data)
{
    bool handleACPlan = false;
    string current_plan_event;
    string next_plan_event;
    string plan_name;
    Frame* frame = new Frame();
    FrameRegistry* registry = NULL;

    if (event_metadata != NULL && string(event_metadata->value) == string("ACPLAN"))
    {
        handleACPlan = true;

        if (event_metadata->sub != NULL)
        {
            current_plan_event = event_metadata->sub->value;
        }
        else
        {
            cout << "Malformed Frame." << endl;
            return;
        }


        if (event_metadata->sub->next != NULL)
        {
            next_plan_event = event_metadata->sub->next->value;
        }
        else
        {
            cout << "Malformed Frame." << endl;
            return;
        }

        if (event_metadata->sub->next->next != NULL)
        {
            plan_name = event_metadata->sub->next->next->value;
        }
        else
        {
            cout << "Malformed Frame." << endl;
            return;
        }


        frame->frame_name = current_plan_event;
        frame->next_frame = next_plan_event;
        frame->frame_group = plan_name;
        registry = &GlobalPlanRegistry;


        (*registry)[current_plan_event].push_back(frame);
        //(*registry)[next_plan_event].push_back(frame);
        (*registry)[plan_name].push_back(frame);

        bool issubplan = false;


        if (event_metadata->sub->next->next->next != NULL)
        {
            if (event_metadata->sub->next->next->next->next != NULL)
            {
                string subdenot = event_metadata->sub->next->next->next->value;
                string subvalue = event_metadata->sub->next->next->next->next->value;

                if (subdenot == "SUBPLAN")
                {
                    cout << "We have a subplan" << endl;
                    subplans.push_back(pair<string,string>(current_plan_event, subvalue+".txt"));
                    issubplan = true;
                }
                else if (subdenot == "ISSUBPLAN")
                {
                    issubplan = true;
                }
            }
            else
            {
                cout << "Subframe without a file." << endl;
            }
        }

        bool contains = false;

        if (!issubplan)
        {

            for (list<string>::iterator iter = GlobalPlanList.begin();
                    iter != GlobalPlanList.end();
                    iter++)
            {
                if (*iter == plan_name)
                {
                    contains = true;
                    break;
                }
            }

            if (!contains)
                GlobalPlanList.push_back(plan_name);
        }
    }
    else if (event_metadata != NULL && string(event_metadata->value) == string("QUEUEMETA"))
    {
        queueMeta = true;
    }
    else if (event_metadata != NULL && string(event_metadata->value) == string("META"))
    {

        if (!event_metadata) return;
        if (!event_metadata->sub) return;
        if (!event_action) return;
        if (!event_data) return;

        metaReason2 = true;

        MetaFrame* metaframe = new MetaFrame();


        SymbolCell* currCell = event_metadata->sub;

        {
            list<Frame*> toFilter = GlobalFrameRegistry[currCell->value];
            list<Frame*> filtered;
            currCell = currCell->next;

            if (!currCell) filtered = toFilter;

            for (list<Frame*>::iterator iter = toFilter.begin();
                    iter != toFilter.end();
                    iter++)
            {
                Frame* tmpFrame = *iter;
                SymbolCell* cellStart = currCell;

                while (cellStart)
                {
                    for (map<string,string>::iterator fillersIter = tmpFrame->fillers.begin();
                            fillersIter != tmpFrame->fillers.end();
                            fillersIter++)
                    {
                        if (fillersIter->second == cellStart->value)
                            filtered.push_back(tmpFrame);
                    }

                    cellStart = cellStart->next;
                }
            }

            metaframe->preds = filtered;
        }


        metaframe->reason = event_action->value;



        currCell = event_data;



        {
            list<Frame*> toFilter = GlobalFrameRegistry[currCell->value];
            list<Frame*> filtered;
            currCell = currCell->next;

            if (!currCell) filtered = toFilter;

            for (list<Frame*>::iterator iter = toFilter.begin();
                    iter != toFilter.end();
                    iter++)
            {
                Frame* tmpFrame = *iter;
                SymbolCell* cellStart = currCell;

                while (cellStart)
                {
                    for (map<string,string>::iterator fillersIter = tmpFrame->fillers.begin();
                            fillersIter != tmpFrame->fillers.end();
                            fillersIter++)
                    {
                        if (fillersIter->second == cellStart->value)
                            filtered.push_back(tmpFrame);
                    }

                    cellStart = cellStart->next;
                }
            }

            metaframe->succs = filtered;
        }



        for (list<Frame*>::iterator prediter = metaframe->preds.begin();
                prediter != metaframe->preds.end();
                prediter++)
        {
            for (list<Frame*>::iterator succiter = metaframe->succs.begin();
                    succiter != metaframe->succs.end();
                    succiter++)
            {
                (MetaRegistry[*prediter])[*succiter].push_back(metaframe);
            }
        }

        return;
    }
    else
    {
        registry = &GlobalFrameRegistry;
    }

    if (NULL == registry)
    {
        cout << "Malformed Registry" << endl;
        return;
    }


    if (currentParentFrame)
        currentParentFrame->subframes.push_back(current_plan_event);


    string actionFiller(event_action->value);
    list<string> insertedKeys;

    frame->SetActionSlot(actionFiller);
    (*registry)[actionFiller].push_back(frame);
    insertedKeys.push_back(actionFiller);

    int symbolCount = 1;

    for (SymbolCell* current = event_data;
            current;
            current = current->next)
    {
        string currentValueStr(current->value);
        if (currentValueStr == string(","))
        {
            //symbolCount++;
            continue;
        }

        frame->fillers[SlotOrderMap[symbolCount]] = currentValueStr;

        bool foundKey = false;

        for (list<string>::iterator iter = insertedKeys.begin();
                iter != insertedKeys.end();
                iter++)
        {
            if (*iter == currentValueStr)
            {
                foundKey = true;
                break;
            }

        }

        if (!foundKey)
        {
            (*registry)[currentValueStr].push_back(frame);
            insertedKeys.push_back(actionFiller);
        }

        if (current->sub)
        {
            for (SymbolCell* current_sub = current->sub;
                    current_sub;
                    current_sub = current_sub->next)
            {
                string currentSubValueStr(current_sub->value);
                if (currentSubValueStr == string(",")) continue;

                bool foundKey = false;

                for (list<string>::iterator iter = insertedKeys.begin();
                        iter != insertedKeys.end();
                        iter++)
                {
                    if (*iter == currentSubValueStr)
                    {
                        foundKey = true;
                        break;
                    }
                }

                if (!foundKey)
                {
                    (*registry)[currentSubValueStr].push_back(frame);
                    insertedKeys.push_back(actionFiller);
                }
            }
        }

        symbolCount++;
    }
}

void PrintFrames(list<Frame*> frames)
{
    for (list<Frame*>::iterator iter = frames.begin();
            iter != frames.end();
            iter++)
    {
        (*iter)->PrintFrame();
    }
}

void PrintGlobalFrameRegistry()
{
    for (FrameRegistry::iterator iter = GlobalFrameRegistry.begin();
            iter != GlobalFrameRegistry.end();
            iter++)
    {
        PrintFrames(iter->second);
    }
}

void PrintGlobalPlanRegistry()
{
    for (FrameRegistry::iterator iter = GlobalPlanRegistry.begin();
            iter != GlobalPlanRegistry.end();
            iter++)
    {
        PrintFrames(iter->second);
    }

}


void MatchPlansWithEvents()
{
    for (list<string>::iterator planiter = GlobalPlanList.begin();
            planiter != GlobalPlanList.end();
            planiter++)
    {
        tabcount = 0;
        cout << endl << endl << endl << "----------------------------------------------------------------" << endl << endl;

        cout << "Another Chain: " << *planiter << endl;

        FrameRegistry::iterator planRegIter = GlobalPlanRegistry.find(*planiter);

        if (planRegIter != GlobalPlanRegistry.end())
        {

            string planname = *planiter;
            string currentPlanEvent = planname + "ACPLAN-START";

            list<Frame*> matching_frames;
            Frame* intentionFrame = NULL;
            list<string> subframes;
            int i = 1;

            while (currentPlanEvent != (planname + "ACPLAN-END"))
            {
                Frame* planEvent = NULL;

                if (subframes.size() > 0)
                {
                    currentPlanEvent = subframes.front();
                    subframes.pop_front();
                }

                planEvent = *(GlobalPlanRegistry[currentPlanEvent].begin());

                if (planEvent == NULL)
                {
                    cout << currentPlanEvent << endl;
                    cout << "NULL" << endl;
                }

                if (planEvent->subframes.size() > 0)
                {
                    list<string> backlist;

                    for (list<string>::iterator iter = subframes.begin();
                            iter != subframes.end();
                            iter++)
                    {
                        backlist.push_back(*iter);
                    }

                    subframes.clear();

                    bool trip = false;

                    for (list<string>::iterator iter = planEvent->subframes.begin();
                            iter != planEvent->subframes.end();
                            iter++)
                    {
                        //        cout << *iter << endl;
                        // cout << "SUBFRAME PUSHBACK: " << *iter << endl;
                        subframes.push_back(*iter);

                        if (iter == planEvent->subframes.begin() && !trip)
                        {
                            GlobalPlanRegistry[*iter].front()->startsSubplan = true;
                            trip = true;
                        }
                    }

                    planEvent->subframes.clear(); // XXX

                    // cout << "SUBFRAME PUSHBACK: " << planEvent->next_frame << endl;
                    subframes.push_back(planEvent->next_frame);

                    if (backlist.size() > 0)
                        backlist.pop_front();

                    for (list<string>::iterator iter = backlist.begin();
                            iter != backlist.end();
                            iter++)
                    {
                        // cout << "SUBFRAME PUSHBACK: " << *iter << endl;
                        subframes.push_back(*iter);
                    }

                    continue;
                }

                map<Frame*, int> frameFreqStat;


                for (map<string, string>::iterator filleriter =  planEvent->fillers.begin();
                        filleriter != planEvent->fillers.end();
                        filleriter++)
                {
                    if (filleriter->second != "BLANK") // TODO
                    {
                        bool setSubStart = false;
                        for (list<Frame*>::iterator iter = GlobalFrameRegistry[filleriter->second].begin();
                                iter != GlobalFrameRegistry[filleriter->second].end();
                                iter++)
                        {
                            if (planEvent->startsSubplan && !setSubStart) 
                            {
                                (*iter)->startsSubplan = true;
                                setSubStart = true;
                            }
                            frameFreqStat[*iter] = 0;
                        }
                    }
                }

                for (map<string, string>::iterator filleriter =  planEvent->fillers.begin();
                        filleriter != planEvent->fillers.end();
                        filleriter++)
                {
                    if (filleriter->second != "BLANK")  // TODO
                    {
                        for (list<Frame*>::iterator iter = GlobalFrameRegistry[filleriter->second].begin();
                                iter != GlobalFrameRegistry[filleriter->second].end();
                                iter++)
                        {
                            frameFreqStat[*iter]++;
                        }
                    }
                }

                int freq = 0;
                Frame* statFrame = NULL;

                for (map<Frame*, int>::iterator iterframestat = frameFreqStat.begin();
                        iterframestat != frameFreqStat.end();
                        iterframestat++)
                {
                    if (iterframestat->second > freq)
                    {
                        freq = iterframestat->second;
                        statFrame = iterframestat->first;
                    }
                }


                i++;
                /*
                   cout << "Setting next frame: " << planEvent->next_frame << endl;
                   cout << "Setting next frame: " << planEvent->frame_name << endl;
                   cout << "Setting next frame: " << planEvent->frame_group << endl;*/
                string prevPlanEvent = currentPlanEvent;
                currentPlanEvent = planEvent->next_frame;

                if (freq > 0 && currentPlanEvent != (planname + "ACPLAN-END"))
                {
                    statFrame->hasIntention = false;
                    matching_frames.push_back(statFrame);
                }
                else if ((planname+"ACPLAN-END") == currentPlanEvent)
                {
                }
                else
                {
                    statFrame = GlobalPlanRegistry[prevPlanEvent].front();
                    statFrame->hasIntention = true;
                    matching_frames.push_back(statFrame);
                }

                if (currentPlanEvent == (planname + "ACPLAN-END"))
                {
                    intentionFrame = planEvent;
                }


            }

            for (list<string>::iterator iter = subframes.begin();
                    iter != subframes.end();
                    iter++)
            {
                cout << *iter << endl;
            }

            // Got List of matching events

            map<string, int> agentFreq;
            string planAgentType = intentionFrame->fillers[AGENT];
            string frequentAgent;
            int highestAgentFreq = 0;

            for (list<Frame*>::iterator iter = matching_frames.begin();
                    iter != matching_frames.end();
                    iter++)
            {
                agentFreq[(*iter)->fillers[intentionFrame->fillers[AGENT]]] = 0;
            }

            for (list<Frame*>::iterator iter = matching_frames.begin();
                    iter != matching_frames.end();
                    iter++)
            {
                agentFreq[(*iter)->fillers[intentionFrame->fillers[AGENT]]]++;
            }

            for (map<string, int>::iterator iter = agentFreq.begin();
                    iter != agentFreq.end();
                    iter++)
            {
                if (iter->second > highestAgentFreq)
                {
                    highestAgentFreq = iter->second;
                    frequentAgent = iter->first;
                }
            }

            string secondHighestAgent;
            int secondhighestAgentFreq = 0;

            for (map<string, int>::iterator iter = agentFreq.begin();
                    iter != agentFreq.end();
                    iter++)
            {
                if (iter->second > secondhighestAgentFreq && iter->first != frequentAgent)
                {
                    secondhighestAgentFreq = iter->second;
                    secondHighestAgent = iter->first;
                }
            }


            map<string, int> objectFreq;
            string planobjectType = intentionFrame->fillers[OBJECT];
            string frequentobject;
            int highestobjectFreq = 0;

            for (list<Frame*>::iterator iter = matching_frames.begin();
                    iter != matching_frames.end();
                    iter++)
            {
                objectFreq[(*iter)->fillers[intentionFrame->fillers[OBJECT]]] = 0;
            }

            for (list<Frame*>::iterator iter = matching_frames.begin();
                    iter != matching_frames.end();
                    iter++)
            {
                objectFreq[(*iter)->fillers[intentionFrame->fillers[OBJECT]]]++;
            }


            for (map<string, int>::iterator iter = objectFreq.begin();
                    iter != objectFreq.end();
                    iter++)
            {
                if (iter->second > highestobjectFreq)
                {
                    highestobjectFreq = iter->second;
                    frequentobject = iter->first;
                }
            }


            char* retvalstr = NULL;

            asprintf(&retvalstr, "%d", highestAgentFreq);
            string dummymetaout = "Most Frequent Agent: " + frequentAgent + " occurs " + retvalstr + " times in this chain.";
            printMeta(dummymetaout);
            free(retvalstr);
            retvalstr = NULL;


            asprintf(&retvalstr, "%d", secondhighestAgentFreq);
            dummymetaout = "Second most Frequent Agent: " + secondHighestAgent + " occurs " + retvalstr + " times in this chain.";
            printMeta(dummymetaout);
            free(retvalstr);
            retvalstr = NULL;


            asprintf(&retvalstr, "%d", highestobjectFreq);
            dummymetaout = "Most Frequent Object: " + frequentobject + " occurs " + retvalstr + " times in this chain.";
            printMeta(dummymetaout);
            free(retvalstr);
            retvalstr = NULL;

            for (list<Frame*>::iterator iter = matching_frames.begin();
                    iter != matching_frames.end();
                    iter++)
            {

                if ((*iter)->hasIntention)
                {
                    if ((*iter)->startsSubplan)
                    {
                        printMeta("Starting an HTN SubScript...");
                        cout << "\nSub Script: " << endl;
                        tabcount++;
                    }

                    printIntentionFrame(*iter, frequentAgent, planAgentType, frequentobject, secondHighestAgent);
                    tabcount--;
                }
                else
                {
                    // Some Fixup code to adjust the agent incase of an event collision.
                    if (GlobalFrameRegistry[(*iter)->fillers[ACTION]].front()->fillers[AGENT] != frequentAgent &&
                            GlobalFrameRegistry[(*iter)->fillers[ACTION]].size() > 1
                       )
                    {
                        string tmp = "Running Fixup Code, because the current agent (" + GlobalFrameRegistry[(*iter)->fillers[ACTION]].front()->fillers[AGENT] 
                            + ") is not the most frequently used agent in this chain (" + frequentAgent + ")";

                        printMeta(tmp);
                        Frame* foundFrame = NULL;

                        for (list<Frame*>::iterator collisionIter = GlobalFrameRegistry[(*iter)->fillers[ACTION]].begin();
                                collisionIter != GlobalFrameRegistry[(*iter)->fillers[ACTION]].end();
                                collisionIter++)
                        {
                            if ((*collisionIter)->fillers[AGENT] == frequentAgent)
                            {
                                foundFrame = *collisionIter;
                                break;
                            }
                        }

                        if (foundFrame)
                        {
                            if ((*iter)->startsSubplan)
                            {
                                ostringstream ost;

                                ost << " ( " << foundFrame->fillers[ACTION] << ","
                                    << " ( "
                                    << foundFrame->fillers[AGENT] << ","
                                    << foundFrame->fillers[OBJECT] << ","
                                    << foundFrame->fillers[LOCATION] << ","
                                    << foundFrame->fillers[COAGENT] << ","
                                    << foundFrame->fillers[TIME] << ","
                                    << " )) ";

                                string tmp = "AICOP was right, there is a better option for this match, and it was: " + ost.str();

                                printMeta(tmp);
                                cout << "\nSub Script: " << endl;
                                tabcount++;
                            }

                            foundFrame->PrintFrame();
                        }
                        else
                        {
                            printMeta("AICOP was wrong, using original matching frame.");
                            if ((*iter)->startsSubplan)
                            {
                                cout << "\nSub Script: " << endl;
                                tabcount++;
                            }

                            (*iter)->PrintFrame();
                        }

                    }
                    else
                    {
                        printMeta("No mismatch between current script frame and most frequent agents used in script.");
                        if ((*iter)->startsSubplan)
                        {
                            cout << "\nSub Script: " << endl;
                            tabcount++;
                        }

                        (*iter)->PrintFrame();
                    }
                }
            }

            printIntentionFrame(intentionFrame, frequentAgent, planAgentType, frequentobject, secondHighestAgent);

       }

        clearMeta();
    }
}


void printIntentionFrame(Frame* intentionFrame, string frequentAgent, string planAgentType, string frequentobject, string secondHighestAgent)
{

    if (intentionFrame)
    {
        printTabs();
        string metaout1 = frequentAgent + " is the most frequent agent, so it must be central to intentions of actors in this chain.";
        printMeta(metaout1);
        cout <<endl <<  "Intention of " << frequentAgent << ": " << endl << "\t";
        printTabs();
        cout << intentionFrame->fillers[ACTION] << " ";

        for (map<string, string>::iterator iter = intentionFrame->fillers.begin();
                iter != intentionFrame->fillers.end();
                iter++)
        {
            if (iter->first != ACTION && iter->first != planAgentType && iter->second != "BLANK" && iter->second != "")
            {
                cout << endl;
                if (iter->second == "coagent")
                {
                    printMeta("Script has an intention for a specific Co-Agent");
                    printTabs();
                    cout << secondHighestAgent << " " << endl;
                    string metaout = "AICOP's Second Most Frequent Agent was " + secondHighestAgent + " so that is probably a correct actor to use as the co-agent.";
                    printMeta(metaout);
                }
                else if (iter->second == "object")
                {
                    printMeta("Script has intention for a specific Object");
                    printTabs();
                    cout << frequentobject << " " << endl;
                    string metaout = "AICOP's Most Frequent object was " + frequentobject + " so that is probably the correct object to use.";
                    printMeta(metaout);

                }
                else
                {
                    printMeta("Script has no specific information about which actor the intension belongs too. Assuming it is the Agent (the most frequent agent) mentioned above.");
                    printTabs();
                    cout << iter->second << " " << endl;

                }
            }
        }

    }
    cout << endl << endl;
}



