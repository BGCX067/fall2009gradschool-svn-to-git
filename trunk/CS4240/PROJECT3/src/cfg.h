/****************************************************/
/* File: cfg.h                                      */
/* The control flow graph interface to the          */
/* LUA compiler                                     */
/* Puyan                                            */
/****************************************************/

#ifndef CFG_H
#define CFG_H

#include "code.h"

typedef struct cfglist
{
    struct cfgnode* value;
    struct cfglist* next;
} CFGList;

typedef struct cfgedgelist
{
    struct cfgedge* value;
    struct cfgedgelist* next;
} CFGEdgeList;

typedef struct cfgnode
{
    struct cfglist* preds;
    BLOCK* basicBlock;
    CFGList* DOMSet;
    CFGList* PostDOMSet;
    struct cfgnode* fstSuccNode;
    struct cfgnode* sndSuccNode;
} CFGNode;

typedef struct cfgedge
{
    struct cfgnode* source;
    struct cfgnode* target;
} CFGEdge;

typedef struct cfg
{
    struct cfgnode* node;
    struct cfgedgelist* backedges;
    struct looplist* loops;
    FUNC* func;
    struct cfg* next;
} CFG;

typedef struct blocklist
{
    BLOCK* block;
    struct blocklist* next;
} BLOCKList;

typedef struct loop
{
    BLOCK* preheader;
    BLOCK* header;
    struct cfgedge* backedge;
    BLOCK* body;
    // if necessary, we may need to add invariant variable, exit inst, exit condition here in the future.
} LOOP;

typedef struct looplist
{
    struct loop* value;
    struct looplist* next;
} LOOPList;


// You can add these functions into cfg.c:

void     PopulatePostDOMSets(CFGNode* cfg);
void     PopulateDOMSets(CFG** cfg);
void     PopulateBackEdges(CFG* cfg);

LOOPList* newLOOPList();
void PushLOOP(LOOPList** looplist, CFGEdge* backedge);
void PopulateLoops(CFG* cfg);

void PopulateCFGStuff(CFG** cfg);

void RemoveDeadBackEdges(CFG* cfg);

//char* EvalBranchOutcome(BLOCK* block, Inst* inst, char* name, CFGEdgeList* backedges);

Inst* ReplicateInst(Inst* original);
BLOCK* ReplicateBlock(BLOCK* original);

void PushBlock(BLOCKList** stack, BLOCK* block);
BLOCK* PopBlock(BLOCKList** stack);

BLOCK* UnRollLoop(CFGEdge* edge);

CFGEdge* DetectBackEdge(CFG* cfg);
CFGList* DetectDominant(CFGNode* node);
CFGList* DetectPostDominant(CFGNode* node);
CFGNode* DetectImmediateDominant(CFGNode* node);
CFGNode* DetectImmediatePostDominant(CFGNode* node);
LOOP*    DetectLoop(CFG* cfg);

void AddCFGNodePred(CFGNode* node, CFGList** preds);
CFG* GetCFGForFUNC(FUNC* func);
void AddCFGNode(CFG** cfg, BLOCK* block);
CFG* newCFG(CFGNode* node, CFG* cfg);
CFGNode* newCFGNode(BLOCK* basicBlock);
void reverseCFGNodeList(CFG** cfg);
void InsertCFGNode(CFGNode* node, CFGList** list);
CFGNode* CFGCreate(FUNC* f);

#endif

