/****************************************************/
/* File: cfg.c                                      */
/* Control Flow Graphs, Loop Detection, Dom and     */
/* Post Dom Analysis, Free Code.                    */
/* for the LUA compiler                             */
/* Puyan                                            */
/****************************************************/

#include <stdlib.h>
#include "cfg.h"

CFGNode *CFGCreate(FUNC * f)
{
    return NULL;
}


/*
 * Takes a function, and returns the CFG for the function.
 */
CFG* GetCFGForFUNC(FUNC* func)
{
    if (!func) return; // Error
    if (func->funcCFG) return func->funcCFG;

    CFG* cfg = NULL;
    BLOCK* startBlock = func->block;
    BLOCK* currBlock = startBlock;

    do
    {
        AddCFGNode(&cfg, currBlock);
        cfg->func = func;
        func->funcCFG = cfg;
        currBlock = currBlock->next;
    } while (startBlock != currBlock && currBlock);

    return cfg;
}

/*
 * Adds a new to the CFG, using a basic block.
 */
void AddCFGNode(CFG** cfg, BLOCK* block)
{
    CFGNode* cfgnode  = NULL;
    char* fstSuccName = NULL;
    char* sndSuccName = NULL;
    BLOCK* currBlock = block;

    if (!block) return; //Error
    if (!block->lastInst) return; //Error
    if (!cfg) return; //Error

    while (currBlock->prev)
    {
        currBlock = currBlock->prev;
    }

    cfgnode = newCFGNode(block);
    *cfg = newCFG(cfgnode, *cfg);

    switch (block->lastInst->instType)
    {
        case UncondBrI:
        {
            UncondBrInst* uncondBrInst = (UncondBrInst *)block->lastInst->inst;
            fstSuccName = uncondBrInst->dst.name; // TODO: Consider a string copy here.
            break;
        }
        case CondBrI:
        {
            CondBrInst* condBrInst = (CondBrInst *)block->lastInst->inst;
            fstSuccName = condBrInst->dstTrue.name;  // TODO: Consider a string copy here.
            sndSuccName = condBrInst->dstFalse.name; // TODO: Consider a string copy here.
            break;
        }
        case RetI:
        {
            break;
        }
        default:
            // Error = TRUE;
            break;
    }



    do
    {

        if (block->lastInst->instType == RetI) break;

        if (!strcmp(currBlock->name, fstSuccName))
        {
            cfgnode->fstSuccNode = newCFGNode(currBlock);
            AddCFGNodePred(cfgnode, &(cfgnode->fstSuccNode->preds));

            if (block->lastInst->instType == UncondBrI || cfgnode->sndSuccNode) break;
        }

        if (sndSuccName && !strcmp(currBlock->name, sndSuccName))
        {
            cfgnode->sndSuccNode = newCFGNode(currBlock);
            AddCFGNodePred(cfgnode, &(cfgnode->sndSuccNode->preds));

            if (cfgnode->fstSuccNode) break;
        }

        currBlock = currBlock->next;

    } while (currBlock); // I am now assuming that these are not circular lists.

}

/*
 * Adds a node to a predecesor list.
 */
void AddCFGNodePred(CFGNode* node, CFGList** preds)
{
    CFGList* head = NULL;

    if (!node || !preds) return; // Error

    head = (CFGList*)malloc(sizeof(CFGList));

    if (!head)
    {
        printf("Out of Memory at %s:%d !!!", __FILE__, __LINE__);
        exit(0);
    }

    head->value = node;
    head->next = *preds;
    *preds = head;
}

void RemovePredFromCFGNode(CFGNode* node, char* predname)
{
    CFGList* currPred = NULL;

    if (!node) return;
    if (!node->preds) return;
    if (!predname) return;

    currPred = node->preds;

    if (!strcmp(currPred->value->basicBlock->name, predname))
    {
        node->preds = node->preds->next;
        // free
        return;
    }

    while (currPred->next)
    {
        if (!strcmp(currPred->next->value->basicBlock->name, predname))
        {
            currPred->next = currPred->next->next;
            // free
            return;
        }

        currPred = currPred->next;
    }
}

void AppendCFG(CFG** cfg1, CFG** cfg2)
{
    (*cfg1)->next = *cfg2;
}

/*
 * Allocates storage for a new CFG structure.
 */
CFG* newCFG(CFGNode* node, CFG* cfg)
{
    CFG* newCfg = NULL;
    
    if (!node) return; //Error
    
    newCfg = (CFG*)malloc(sizeof(CFG));

    if (!newCfg)
    {
        printf("Out of Memory at %s:%d !!!", __FILE__, __LINE__);
        exit(0);
    }

    newCfg->node = node;
    newCfg->backedges = NULL;
    newCfg->func = NULL;
    newCfg->next = NULL;

    if (cfg) newCfg->next = cfg;

    cfg = newCfg;

    return cfg;
}

CFGNode* newCFGNode(BLOCK* basicBlock)
{
    CFGNode* newCfgNode    = NULL;
    
    if (!basicBlock) return; // Error

    if (!basicBlock->cfg)
    {
        newCfgNode = (CFGNode*)malloc(sizeof(CFGNode));

        if (!newCfgNode)
        {
            printf("Out of Memory at %s:%d !!!", __FILE__, __LINE__);
            exit(0);
        }

        newCfgNode->basicBlock     = NULL;
        newCfgNode->preds          = NULL;
        newCfgNode->fstSuccNode    = NULL;
        newCfgNode->sndSuccNode    = NULL;
        newCfgNode->DOMSet = NULL;
        newCfgNode->PostDOMSet = NULL;
        newCfgNode->basicBlock     = basicBlock;
        basicBlock->cfg        = newCfgNode;
    }
    else
    {
        newCfgNode = basicBlock->cfg;
    }

    return newCfgNode;
}

void reverseCFGNodeList(CFG** cfg)
{
    CFG* current = NULL;
    CFG* stack = NULL;
    CFG* head = NULL;

    if (!cfg || !*cfg) return;

    head  = *cfg;
    stack = head;
    head = head->next;
    stack->next = NULL;
    current = head;

    while (current)
    {
        current = current->next;
        head->next = stack;
        stack = head;
        head = current;
    }

    *cfg = stack;
}

void PopulatePostDOMSets(CFGNode* cfgnode)
{
    CFGList* currPred = NULL;

    if (!cfgnode) return; // Error

    if (cfgnode->PostDOMSet) return;

    currPred = cfgnode->preds;

    InsertCFGNode(cfgnode, &cfgnode->PostDOMSet); // Check to see if it is already in the set.

    switch (cfgnode->basicBlock->lastInst->instType)
    {
        case UncondBrI:
        {
            CFGList* succPostDOMSet = NULL;

            if (!cfgnode->fstSuccNode)
            {
                printf("Null Pointer.\n");
                return;
            }

            succPostDOMSet = cfgnode->fstSuccNode->PostDOMSet; // TODO Check for NULL Pointers

            while (succPostDOMSet)
            {
                InsertCFGNode(succPostDOMSet->value, &cfgnode->PostDOMSet); // Check to see if it is already in the set.
                succPostDOMSet = succPostDOMSet->next;
            }
            break;
        }
        case CondBrI:
        {
            CFGList* succPostDOMSet_FstBr = NULL;

            if (!cfgnode->fstSuccNode)
            {
                printf("Null Pointer.\n");
                return;
            }

            succPostDOMSet_FstBr = cfgnode->fstSuccNode->PostDOMSet;

            if (succPostDOMSet_FstBr)
            {
                CFGList* succPostDOMSet_SndBr = NULL;

                if (!cfgnode->sndSuccNode)
                {
                    printf("Null Pointer.\n");
                    return;
                }

                succPostDOMSet_SndBr = cfgnode->sndSuccNode->PostDOMSet;

                while (succPostDOMSet_FstBr)
                {
                    if (succPostDOMSet_SndBr)
                    {
                        while (succPostDOMSet_SndBr)
                        {
                            if (succPostDOMSet_FstBr->value == succPostDOMSet_SndBr->value) // No need for a strcmp, the refereces should be the same.
                                InsertCFGNode(succPostDOMSet_FstBr->value, &cfgnode->PostDOMSet); // Check to see if it is already in the set.

                            succPostDOMSet_SndBr = succPostDOMSet_SndBr->next;
                        }
                    }
                    else
                    {
                        InsertCFGNode(succPostDOMSet_FstBr->value, &cfgnode->PostDOMSet); // Check to see if it is already in the set.
                    }

                    succPostDOMSet_FstBr = succPostDOMSet_FstBr->next;
                }
            }
            else
            {
                CFGList* succPostDOMSet_SndBr = NULL;

                if (!cfgnode->sndSuccNode)
                {
                    printf("Null Pointer.\n");
                    return;
                }

                succPostDOMSet_SndBr = cfgnode->sndSuccNode->PostDOMSet; // TODO Check for NULL Pointers

                while (succPostDOMSet_SndBr)
                {
                    InsertCFGNode(succPostDOMSet_SndBr->value, &cfgnode->PostDOMSet); // Check to see if it is already in the set.


                    succPostDOMSet_SndBr = succPostDOMSet_SndBr->next;
                }

            }
            break;
        }
        case RetI:
        {
            break;
        }
        default:
            break;
    }

    while (currPred)
    {
        PopulatePostDOMSets(currPred->value);
        currPred = currPred->next;
    }
}

/*
 * Populates the set of dominators for
 * each basic block node in the CFG.
 *
 * I make the assumption that the linked list CFG
 * starts from the entry basic block end ends with the exit.
 *
 * Use the reverseCFGNodeList() function to put the list in the correct order.
 */
void PopulateDOMSets(CFG** cfg)
{
    CFGNode* currNode = NULL;

    if (!cfg || !*cfg) return; // Error

    currNode = (*cfg)->node;

    int totalPreds = 0;
    CFGList* preds = currNode->preds;
    CFGList* currPred = preds;

    while (currPred)
    {
        CFGList* currPredDomSet = currPred->value->DOMSet;

        while (currPredDomSet)
        {
            currPredDomSet->value->basicBlock->breadcrumb = 0;
            currPredDomSet = currPredDomSet->next;
        }

        totalPreds++;
        currPred = currPred->next;
    }


    currPred = preds;

    while (currPred)
    {
        CFGList* currPredDomSet = currPred->value->DOMSet;

        while (currPredDomSet)
        {
            currPredDomSet->value->basicBlock->breadcrumb++;
            currPredDomSet = currPredDomSet->next;
        }

        currPred = currPred->next;
    }


    currPred = preds;
    InsertCFGNode(currNode, &currNode->DOMSet);

    while (currPred)
    {
        CFGList* currPredDomSet = currPred->value->DOMSet;

        while (currPredDomSet)
        {
            if (currPredDomSet->value->basicBlock->breadcrumb == totalPreds)
            {
                if (currNode != currPredDomSet->value)
                InsertCFGNode(currPredDomSet->value, &currNode->DOMSet);
            }
            
            currPredDomSet = currPredDomSet->next;
        }

        currPred = currPred->next;
    }


    // Some fixup code for conditional branches. 
    if (currNode->basicBlock->lastInst->instType == UncondBrI &&
        currNode->fstSuccNode->basicBlock->lastInst->instType == CondBrI &&
        !currNode->fstSuccNode->DOMSet)
    {
        CFGList* currDomSet = currNode->DOMSet;

        while (currDomSet)
        {
            InsertCFGNode(currDomSet->value, &currNode->fstSuccNode->DOMSet);
            currDomSet = currDomSet->next;
        }
    }

    PopulateDOMSets(&((*cfg)->next));
}

void InsertCFGNode(CFGNode* node, CFGList** list)
{
    CFGList* newList = NULL;
    CFGList* currList = NULL;

    if (!list) return; // Error
    if (!node) return; // Error

    currList = *list;

    // Making sure that this node has not been entered into the list.
    while (currList)
    {
        if (currList->value->basicBlock == node->basicBlock ||
                !strcmp(currList->value->basicBlock->name,  node->basicBlock->name))
        {
            return;
        }
        currList = currList->next;
    }

    newList = (CFGList*)malloc(sizeof(CFGList));

    if (!newList)
    {
        printf("Out of Memory at %s:%d !!!", __FILE__, __LINE__);
        exit(0);
    }

    newList->value = node;
    newList->next = NULL;

    if (!*list)
    {
        *list = newList;
    }
    else
    {
        newList->next = *list;
        *list = newList;
    }
}

CFGEdge* newCFGEdge(CFGNode* sourceNode, CFGNode* targetNode)
{
    CFGEdge* newEdge = NULL;

    if (!sourceNode) return;
    if (!targetNode) return;

    newEdge = (CFGEdge*)malloc(sizeof(CFGEdge));
    
    if (!newEdge)
    {
        printf("Out of Memory at %s:%d !!!", __FILE__, __LINE__);
        exit(0);
    }

    newEdge->source = sourceNode;
    newEdge->target = targetNode;

    return newEdge;
}

void InsertEdge(CFGEdgeList** edges, CFGEdge* edge)
{
    CFGEdgeList* newEdgeListEntry = NULL;
    CFGEdgeList* currEdgeList = NULL;

    if (!edges) return;
    if (!edge)  return;

    newEdgeListEntry = (CFGEdgeList*)malloc(sizeof(CFGEdgeList));

    if (!newEdgeListEntry)
    {
        printf("Out of Memory at %s:%d !!!", __FILE__, __LINE__);
        exit(0);
    }

    newEdgeListEntry->value = edge;
    newEdgeListEntry->next = NULL;

    if (*edges)
    {
        newEdgeListEntry->next = *edges;
    }

    *edges = newEdgeListEntry;
}

void PopulateBackEdges(CFG* cfg)
{
    CFGEdgeList* backedges = NULL;
    BLOCK* currBlock = NULL;
    CFGNode* currNode = NULL;

    if (!cfg) return;
    if (!cfg->node) return;
    if (!cfg->node->basicBlock) return;

    currBlock = cfg->node->basicBlock;

    while (currBlock->prev)
    {
        currBlock = currBlock->prev;
    }

    currNode = currBlock->cfg;

    while (currNode)
    {
        CFGList* currDOMNode = currNode->DOMSet;

        while (currDOMNode)
        {
            if (currDOMNode->value == currNode->fstSuccNode)
            {
                CFGEdge* temp = newCFGEdge(currNode, currNode->fstSuccNode);
                InsertEdge(&backedges, temp);
            }

            if (currDOMNode->value == currNode->sndSuccNode)
            {
                CFGEdge* temp =  newCFGEdge(currNode, currNode->sndSuccNode);
                InsertEdge(&backedges, temp);
            }

            currDOMNode = currDOMNode->next;
        }

        currBlock = currBlock->next;
        if (!currBlock) break;
        currNode = currBlock->cfg;
    }

    cfg->backedges = backedges;

    PopulateBackEdges(cfg->next);
}



Inst* ReplicateInst(Inst* original)
{
    Inst* copy = NULL;

    if (!original) return NULL;

    copy = (Inst *)malloc(sizeof(Inst));

    if (!copy)
    {
        printf("Out of Memory at %s:%d !!!", __FILE__, __LINE__);
        exit(0);
    }

    copy->instType = original->instType;
    copy->next = ReplicateInst(original->next);
    copy->prev = NULL;
    if (copy->next) copy->next->prev = copy;
    copy->parent = NULL; // TODO: Replicate?

    if (!original->inst)
    {
        printf("NULL Instruction at %s:%d !!!", __FILE__, __LINE__);
        exit(0);
    }


    switch(original->instType)
    {
        case AssignI:
            {
                AssignInst* inst = (AssignInst*)original->inst;
                AssignInst* newInst = (AssignInst*)malloc(sizeof(AssignInst));

                if (!newInst)
                {
                    printf("Out of Memory at %s:%d !!!", __FILE__, __LINE__);
                    exit(0);
                }

                newInst->src.name = strdup(inst->src.name);
                newInst->dst.name = strdup(inst->dst.name);
                newInst->prefix.name = strdup(inst->prefix.name);
                newInst->type = inst->type;
                copy->inst = newInst;

                break;
            }
        case UncondBrI:
            {
                UncondBrInst* inst = (UncondBrInst*)original->inst;
                UncondBrInst* newInst = (UncondBrInst*)malloc(sizeof(UncondBrInst));

                if (!newInst)
                {
                    printf("Out of Memory at %s:%d !!!", __FILE__, __LINE__);
                    exit(0);
                }

                newInst->dst.name = strdup(inst->dst.name);
                copy->inst = newInst;

                break;
            }
        case STI:
            {
                StoreInst* inst = (StoreInst*)original->inst;
                StoreInst* newInst = (StoreInst*)malloc(sizeof(StoreInst));

                if (!newInst)
                {
                    printf("Out of Memory at %s:%d !!!", __FILE__, __LINE__);
                    exit(0);
                }

                newInst->src.name = strdup(inst->src.name);
                newInst->dst.name = strdup(inst->dst.name);
                newInst->srcType = inst->srcType;
                newInst->dstType = inst->dstType;
                copy->inst = newInst;

                break;
            }
        case STArrayI:
            {
                StoreArrayInst* inst = (StoreArrayInst*)original->inst;
                StoreArrayInst* newInst = (StoreArrayInst*)malloc(sizeof(StoreArrayInst));

                if (!newInst)
                {
                    printf("Out of Memory at %s:%d !!!", __FILE__, __LINE__);
                    exit(0);
                }

                newInst->src.name = strdup(inst->src.name);
                newInst->dst.name = strdup(inst->dst.name);
                newInst->tabType = inst->tabType;
                newInst->dimen = inst->dimen;
                copy->inst = newInst;

                break;
            }
        case LDI:
            {
                LoadInst* inst = (LoadInst*)original->inst;
                LoadInst* newInst = (LoadInst*)malloc(sizeof(LoadInst));

                if (!newInst)
                {
                    printf("Out of Memory at %s:%d !!!", __FILE__, __LINE__);
                    exit(0);
                }

                newInst->src.name = strdup(inst->src.name);
                newInst->dst.name = strdup(inst->dst.name);
                newInst->srcType = inst->srcType;
                copy->inst = newInst;

                break;
            }
        case LDArrayI:
            {
                LoadArrayInst* inst = (LoadArrayInst*)original->inst;
                LoadArrayInst* newInst = (LoadArrayInst*)malloc(sizeof(LoadArrayInst));

                if (!newInst)
                {
                    printf("Out of Memory at %s:%d !!!", __FILE__, __LINE__);
                    exit(0);
                }

                newInst->src.name = strdup(inst->src.name);
                newInst->dst.name = strdup(inst->dst.name);
                newInst->tabType = inst->tabType;
                newInst->dimen = inst->dimen;
                copy->inst = newInst;

                break;
            }
        case CondBrI:
            {
                CondBrInst* inst = (CondBrInst*)original->inst;
                CondBrInst* newInst = (CondBrInst*)malloc(sizeof(CondBrInst));

                if (!newInst)
                {
                    printf("Out of Memory at %s:%d !!!", __FILE__, __LINE__);
                    exit(0);
                }

                newInst->src.name = strdup(inst->src.name);
                newInst->dstTrue.name = strdup(inst->dstTrue.name);
                newInst->dstFalse.name = strdup(inst->dstFalse.name);
                copy->inst = newInst;

                break;
            }
        case BinOpI:
            {
                BinOpInst* inst = (BinOpInst*)original->inst;
                BinOpInst* newInst = (BinOpInst*)malloc(sizeof(BinOpInst));

                if (!newInst)
                {
                    printf("Out of Memory at %s:%d !!!", __FILE__, __LINE__);
                    exit(0);
                }

                newInst->src1.name = strdup(inst->src1.name);
                newInst->src2.name = strdup(inst->src2.name);
                newInst->dst.name = strdup(inst->dst.name);
                newInst->type = inst->type;
                newInst->opc = inst->opc;
                copy->inst = newInst;

                break;
            }
        case CMPI:
            {
                CMPInst* inst = (CMPInst*)original->inst;
                CMPInst* newInst = (CMPInst*)malloc(sizeof(CMPInst));


                if (!newInst)
                {
                    printf("Out of Memory at %s:%d !!!", __FILE__, __LINE__);
                    exit(0);
                }

                newInst->src1.name = strdup(inst->src1.name);
                newInst->src2.name = strdup(inst->src2.name);
                newInst->dst.name = strdup(inst->dst.name);
                newInst->type = inst->type;
                newInst->cond = inst->cond;
                copy->inst = newInst;

                break;
            }
        case AllocI:
            {
                AllocInst* inst = (AllocInst*)original->inst;
                AllocInst* newInst  = (AllocInst*)malloc(sizeof(AllocInst));

                if (!newInst)
                {
                    printf("Out of Memory at %s:%d !!!", __FILE__, __LINE__);
                    exit(0);
                }

                newInst->dst.name = strdup(inst->dst.name);
                newInst->type = inst->type;
                copy->inst = newInst;

                break;
            }
        case AllocArrayStackI:
            {
                AllocArrayStackInst* inst = (AllocArrayStackInst*)original->inst;
                AllocArrayStackInst* newInst = (AllocArrayStackInst*)malloc(sizeof(AllocArrayStackInst));

                if (!newInst)
                {
                    printf("Out of Memory at %s:%d !!!", __FILE__, __LINE__);
                    exit(0);
                }

                newInst->dst.name = strdup(inst->dst.name);
                newInst->type = inst->type;
                newInst->dimen = inst->dimen;
                copy->inst = newInst;

                break;
            }
        case BitI:
            {
                BitInst* inst = (BitInst*)original->inst;
                BitInst* newInst = (BitInst*)malloc(sizeof(BitInst));

                if (!newInst)
                {
                    printf("Out of Memory at %s:%d !!!", __FILE__, __LINE__);
                    exit(0);
                }

                newInst->src1.name = strdup(inst->src1.name);
                newInst->src2.name = strdup(inst->src2.name);
                newInst->dst.name = strdup(inst->dst.name);
                newInst->type = inst->type;
                newInst->opc = inst->opc;
                copy->inst = newInst;

                break;
            }
        case InitSI:
            {
                InitStringInst* inst = (InitStringInst*)original->inst;
                InitStringInst* newInst = (InitStringInst*)malloc(sizeof(InitStringInst));

                if (!newInst)
                {
                    printf("Out of Memory at %s:%d !!!", __FILE__, __LINE__);
                    exit(0);
                }

                newInst->dst.name = strdup(inst->dst.name);
                newInst->string = strdup(inst->string);
                newInst->len = inst->len;
                copy->inst = newInst;

                break;
            }
        case LDStringI:
            {
                LDStringInst* inst = (LDStringInst*)original->inst;
                LDStringInst* newInst = (LDStringInst*)malloc(sizeof(LDStringInst));

                if (!newInst)
                {
                    printf("Out of Memory at %s:%d !!!", __FILE__, __LINE__);
                    exit(0);
                }

                newInst->src.name = strdup(inst->src.name);
                newInst->dst.name = strdup(inst->dst.name);
                newInst->len = inst->len;
                copy->inst = newInst;

                break;
            }
        case RetI:
            {
                RetInst* inst = (RetInst*)original->inst;
                RetInst* newInst = (RetInst*)malloc(sizeof(RetInst));

                printf("No Support for RetI %s:%d !!!", __FILE__, __LINE__);
                exit(0);

                if (!newInst)
                {
                    printf("Out of Memory at %s:%d !!!", __FILE__, __LINE__);
                    exit(0);
                }

                newInst->src.name = strdup(inst->src.name);
                newInst->typeList = inst->typeList; // TODO: Copy
                copy->inst = newInst;

                break;
            }
        case AllocStructI:
            {
                AllocStructInst* inst = (AllocStructInst*)original->inst;
                AllocStructInst* newInst = (AllocStructInst*)malloc(sizeof(AllocStructInst));

                printf("No Support for AllocStructI %s:%d !!!", __FILE__, __LINE__);
                exit(0);

                if (!newInst)
                {
                    printf("Out of Memory at %s:%d !!!", __FILE__, __LINE__);
                    exit(0);
                }

                newInst->dst.name = strdup(inst->dst.name);
                newInst->typeList = inst->typeList; // TODO: Copy
                copy->inst = newInst;

                break;
            }
        case AllocArrayI:
            {
                AllocArrayInst* inst = (AllocArrayInst*)original->inst;
                AllocArrayInst* newInst = (AllocArrayInst*)malloc(sizeof(AllocArrayInst));

                if (!newInst)
                {
                    printf("Out of Memory at %s:%d !!!", __FILE__, __LINE__);
                    exit(0);
                }

                newInst->dst.name = strdup(inst->dst.name);
                newInst->eleType = inst->eleType;
                newInst->dimen = inst->dimen;
                copy->inst = newInst;

                break;
            }
        case CallI:
            {
                CallInst* inst = (CallInst*)original->inst;
                CallInst* newInst = (CallInst*)malloc(sizeof(CallInst));

                printf("No Support for CallI %s:%d !!!", __FILE__, __LINE__);
                exit(0);

                if (!newInst)
                {
                    printf("Out of Memory at %s:%d !!!", __FILE__, __LINE__);
                    exit(0);
                }

                newInst->src.name = strdup(inst->src.name);
                newInst->dst.name = strdup(inst->dst.name);
                newInst->retList = inst->retList; // TODO: Copy
                newInst->argList = inst->argList; // TODO: Copy
                newInst->isStruct = inst->isStruct;
                copy->inst = newInst;

                break;
            }
        case GetPtrI:
            {
                GetPtrInst* inst = (GetPtrInst*)original->inst;
                GetPtrInst* newInst = (GetPtrInst*)malloc(sizeof(GetPtrInst));

                printf("No Support for GetPtrI %s:%d !!!", __FILE__, __LINE__);
                exit(0);

                if (!newInst)
                {
                    printf("Out of Memory at %s:%d !!!", __FILE__, __LINE__);
                    exit(0);
                }

                newInst->src.name = strdup(inst->src.name);
                newInst->dst.name = strdup(inst->dst.name);
                newInst->typeList = inst->typeList; // TODO: Copy
                newInst->index = inst->index;
                copy->inst = newInst;

                break;
            }
        case GetPtrArrayI:
            {
                GetPtrArrayInst* inst = (GetPtrArrayInst*)original->inst;
                GetPtrArrayInst* newInst = (GetPtrArrayInst*)malloc(sizeof(GetPtrArrayInst));

                if (!newInst)
                {
                    printf("Out of Memory at %s:%d !!!", __FILE__, __LINE__);
                    exit(0);
                }

                newInst->src.name = strdup(inst->src.name);
                newInst->dst.name = strdup(inst->dst.name);
                newInst->type = inst->type;
                newInst->dimen = inst->dimen;
                newInst->index = inst->index;
                copy->inst = newInst;

                break;
            }
        case ExtractI:
            {
                ExtractInst* inst = (ExtractInst*)original->inst;
                ExtractInst* newInst = (ExtractInst*)malloc(sizeof(ExtractInst));

                printf("No Support for ExtractI %s:%d !!!", __FILE__, __LINE__);
                exit(0);

                if (!newInst)
                {
                    printf("Out of Memory at %s:%d !!!", __FILE__, __LINE__);
                    exit(0);
                }

                newInst->src.name = strdup(inst->src.name);
                newInst->dst.name = strdup(inst->dst.name);
                newInst->typeList = inst->typeList; // TODO: Copy
                newInst->index = inst->index;
                copy->inst = newInst;

                break;
            }
        case PrintI:
            {
                PrintInst* inst = (PrintInst*)original->inst;
                PrintInst* newInst = (PrintInst*)malloc(sizeof(PrintInst));

                printf("No Support for PrintI %s:%d !!!", __FILE__, __LINE__);
                exit(0);

                if (!newInst)
                {
                    printf("Out of Memory at %s:%d !!!", __FILE__, __LINE__);
                    exit(0);
                }

                break;
            }
        case LDStructI:
            {
                LoadStructInst* inst = (LoadStructInst*)original->inst;
                LoadStructInst* newInst = (LoadStructInst*)malloc(sizeof(LoadStructInst));

                printf("No Support for LDStructI %s:%d !!!", __FILE__, __LINE__);
                exit(0);

                if (!newInst)
                {
                    printf("Out of Memory at %s:%d !!!", __FILE__, __LINE__);
                    exit(0);
                }

                break;
            }
        case ToFloatI:
            {
                ToFloatInst* inst = (ToFloatInst*)original->inst;
                ToFloatInst* newInst = (ToFloatInst*)malloc(sizeof(ToFloatInst));

                if (!newInst)
                {
                    printf("Out of Memory at %s:%d !!!", __FILE__, __LINE__);
                    exit(0);
                }

                newInst->src.name = strdup(inst->src.name);
                newInst->dst.name = strdup(inst->dst.name);
                copy->inst = newInst;

                break;
            }
        case ToIntI:
            {
                ToIntInst* inst = (ToIntInst*)original->inst;
                ToIntInst* newInst = (ToIntInst*)malloc(sizeof(ToIntInst));

                if (!newInst)
                {
                    printf("Out of Memory at %s:%d !!!", __FILE__, __LINE__);
                    exit(0);
                }

                newInst->src.name = strdup(inst->src.name);
                newInst->dst.name = strdup(inst->dst.name);
                copy->inst = newInst;

                break;
            }
        default:
            // Error = TRUE;
            break;
    }

    return copy;

}

BLOCK* ReplicateBlock(BLOCK* original)
{
    BLOCK* copy = NULL;
    Inst* currInst = NULL;

    if (!original) return NULL;

    copy = (BLOCK*) malloc(sizeof(BLOCK));


    if (!copy)
    {
        printf("Out of Memory at %s:%d !!!", __FILE__, __LINE__);
        exit(0);
    }


    copy->inst        = ReplicateInst(original->inst);

    currInst = copy->inst;

    while (currInst->next)
    {
        currInst = currInst->next;
    }

    copy->lastInst    = currInst;
    copy->exitInst    = copy->lastInst;

    copy->prev        = NULL;
    copy->next        = NULL;
    copy->parent      = original->parent;
    copy->dfg         = original->dfg;
    copy->cfg         = original->cfg;
    copy->name        = strdup(original->name);

    return copy;
}

void PushBlock(BLOCKList** stack, BLOCK* block)
{
    BLOCKList* currBLOCKList = NULL;

    if (!block) return;
    if (!stack) return;

    currBLOCKList = (BLOCKList*)malloc(sizeof(BLOCKList));

    if (!currBLOCKList)
    {
        printf("Out of Memory at %s:%d !!!", __FILE__, __LINE__);
        exit(0);
    }

    currBLOCKList->block = block;
    currBLOCKList->next = NULL;

    if (*stack)
    {
        currBLOCKList->next = *stack;
    }

    *stack = currBLOCKList;
}

BLOCK* PopBlock(BLOCKList** stack)
{
    BLOCK* retval = NULL;

    if (!stack) return NULL;
    if (!*stack) return NULL;

    retval = (*stack)->block;
    *stack = (*stack)->next;

    return retval;
}

BLOCK* UnRollLoop(CFGEdge* edge)
{
    BLOCK* currBB = NULL;
    BLOCK* currCopyBB = NULL;
    BLOCK* startCopyBBChain = NULL;
    BLOCKList* blockStack = NULL;

    if (!edge) return;
    if (!edge->source) return;
    if (!edge->target) return;

    PushBlock(&blockStack, edge->target->basicBlock);

    while (blockStack)
    {
        currBB = PopBlock(&blockStack);


        if (!currBB) break;

        if (!currBB->cfg)
        {
            printf("Corruption at %s:%d !!!", __FILE__, __LINE__);
            exit(0);
        }

        if (!currCopyBB)
        {
            currCopyBB = ReplicateBlock(currBB);
            startCopyBBChain = currCopyBB;
        }
        else
        {
            BLOCK* tempBB = ReplicateBlock(currBB);
            currCopyBB->next = tempBB;
            tempBB->prev = currCopyBB;
            currCopyBB = currCopyBB->next;
        }

        if (0 == strcmp(currBB->name, edge->source->basicBlock->name)) break;

        if (currBB->cfg->sndSuccNode) PushBlock(&blockStack, currBB->cfg->sndSuccNode->basicBlock);
        if (currBB->cfg->fstSuccNode) PushBlock(&blockStack, currBB->cfg->fstSuccNode->basicBlock);

    }

    return startCopyBBChain;

}


long EvalCMP(CMPInst *inst, char* src1, char* src2)
{
    long result;
    double src1d = strtod(src1, NULL);
    double src2d = strtod(src2, NULL);

    if(inst->type == double_float)
    {
        // fprintf(code, "%s = fcmp ", inst->dst.name);

        switch(inst->cond)
        {
            case EQ:
                // fprintf(code, "ueq ");
                result = (src1d == src2d);
                break;
            case NEQ:
                // fprintf(code, "une ");
                result = (src1d != src2d);
                break;
            case LE:
                // fprintf(code, "ule ");
                result = (src1d <= src2d);
                break;
            case GE:
                // fprintf(code, "uge ");
                result = (src1d >= src2d);
                break;
            case LT:
                // fprintf(code, "ult ");
                result = (src1d < src2d);
                break;
            case GT:
                // fprintf(code, "ugt ");
                result = (src1d > src2d);
                break;
            default:
                // Error = TRUE;
                break;
        }
    }
    else if(inst->type == i1)
    { 
        // fprintf(code, "%s = icmp ", inst->dst.name);
        switch(inst->cond) {
            case EQ:
                // fprintf(code, "eq ");
                result = (src1d == src2d);
                break;
            case NEQ:
                // fprintf(code, "ne ");
                result = (src1d != src2d);
                break;
            case LE:
                // fprintf(code, "ule ");
                result = (src1d <= src2d);
                break;
            case GE:
                // fprintf(code, "uge ");
                result = (src1d >= src2d);
                break;
            case LT:
                // fprintf(code, "ult ");
                result = (src1d < src2d);
                break;
            case GT:
                // fprintf(code, "ugt ");
                result = (src1d > src2d);
                break;
            default:
                // Error = TRUE;
                break;      
        }    
    }  
    // printLLVMType(inst->type);
    // fprintf(code, " %s, %s\n", inst->src1.name, inst->src2.name);
    return result;
}

#if 0

char* EvalBranchOutcome(BLOCK* block, Inst* inst_wrap, char* name, CFGEdgeList* backedges)
{

    CFGList* dom  = NULL;

    if (!name) return 1;
    if (!block) return 1;

/*
    dom = block->cfg->fstSuccNode->DOMSet;

    while (dom)
    {
        if (!strcmp(dom->value->basicBlock->name, block->name)) return name;

        dom = dom->next;
    }
*/

    // if (block->breadcrumb == -42) return name;

    // block->breadcrumb = -42;

    if (!inst_wrap)
    {
        CFGList* preds = block->cfg->preds;

        if (!preds) return name;

        while (preds)
        {
            char* predRet = NULL;
            int cmp;
            double dval;
            int len;
            CFGEdgeList* currEdge = backedges;

            while (currEdge)
            {
                if (!strcmp(currEdge->value->source->basicBlock->name, preds->value->basicBlock->name) &&
                    ! strcmp(currEdge->value->target->basicBlock->name, block->name)) return name;
                currEdge = currEdge->next;
            }


            predRet = EvalBranchOutcome(preds->value->basicBlock, preds->value->basicBlock->lastInst, name, backedges);
            cmp = strcmp(predRet, name);
            dval = strtod(predRet, NULL);
            len = strlen(predRet);



            if (predRet && cmp && ((dval != 0) || len == 1 ))
            {
                return predRet;
            }

            preds = preds->next;
        }

        return name;
    }

    switch(inst_wrap->instType)
    {
        case AssignI:
            {
                AssignInst* inst = (AssignInst*)inst_wrap->inst;

                // inst->src.name;
                // inst->dst.name;
                // inst->prefix.name;
                // inst->type;
                //

                if (!strcmp(inst->dst.name, name))
                {
                    return EvalBranchOutcome(block, inst_wrap->prev, inst->src.name, backedges);
                }

                break;
            }
        case UncondBrI:
            {
                // This will more than likely not be hit.
                // UncondBrInst* inst = (UncondBrInst*)inst_wrap->inst;

                // inst->dst.name;
                // copy->inst;
                //

                return EvalBranchOutcome(block, inst_wrap->prev, name, backedges);


                break;
            }
        case STI:
            {
                StoreInst* inst = (StoreInst*)inst_wrap->inst;

                // inst->src.name;
                // inst->dst.name;
                // inst->srcType;
                // inst->dstType;

                if (!strcmp(inst->dst.name, name))
                {
                    return EvalBranchOutcome(block, inst_wrap->prev, inst->src.name, backedges);
                }

                break;
            }
        case STArrayI:
            {
                StoreArrayInst* inst = (StoreArrayInst*)inst_wrap->inst;

                // inst->src.name;
                // inst->dst.name;
                // inst->tabType;
                // inst->dimen;
                // copy->inst;

                printf("No Support for StoreArrayI %s:%d !!!", __FILE__, __LINE__);
                exit(0);

                break;
            }
        case LDI:
            {
                LoadInst* inst = (LoadInst*)inst_wrap->inst;


                if (!strcmp(inst->dst.name, name))
                {

                    return EvalBranchOutcome(block, inst_wrap->prev, inst->src.name, backedges);
                }

                return EvalBranchOutcome(block, inst_wrap->prev, name, backedges);


                // inst->src.name;
                // inst->dst.name;
                // inst->srcType;

                break;
            }
        case LDArrayI:
            {
                LoadArrayInst* inst = (LoadArrayInst*)inst_wrap->inst;

                // inst->src.name;
                // inst->dst.name;
                // inst->tabType;
                // inst->dimen;

                printf("No Support for LoadArrayI %s:%d !!!", __FILE__, __LINE__);
                exit(0);

                break;
            }
        case CondBrI:
            {
                CondBrInst* inst = (CondBrInst*)inst_wrap->inst;


                return EvalBranchOutcome(block, inst_wrap->prev, name, backedges);


                // inst->src.name;
                // inst->dstTrue.name;
                // inst->dstFalse.name;

                printf("No Support for CondBrI %s:%d !!!", __FILE__, __LINE__);
                exit(0);

                break;
            }
        case BinOpI:
            {
                BinOpInst* inst = (BinOpInst*)inst_wrap->inst;


                if (!strcmp(inst->dst.name, name))
                {
                    double src1 = strtod(inst->src1.name, NULL);
                    double src2 = strtod(inst->src2.name, NULL);
                    double retval = src1 + src2; // TODO: Sanitize
                    char* retvalstr = NULL;

                    asprintf(&retvalstr, "%f", retval);


                    return retvalstr;
                }

                return EvalBranchOutcome(block, inst_wrap->prev, name, backedges);


                // inst->src1.name;
                // inst->src2.name;
                // inst->dst.name;
                // inst->type;
                // inst->opc;

                printf("No Support for BinOpI %s:%d !!!", __FILE__, __LINE__);
                exit(0);

                break;
            }
        case CMPI:
            {
                CMPInst* inst = (CMPInst*)inst_wrap->inst;

                if (!strcmp(inst->dst.name, name))
                {
                    char* src1 = EvalBranchOutcome(block, inst_wrap->prev, inst->src1.name, backedges);
                    char* src2 = EvalBranchOutcome(block, inst_wrap->prev, inst->src2.name, backedges);
                    double src1d = strtod(src1, NULL);
                    double src2d = strtod(src2, NULL);

                    if (src1d == 0 && strlen(src1) > 1) return 1;
                    if (src2d == 0 && strlen(src2) > 1) return 1;


                    return EvalCMP(inst, src1, src2);

                    // double src1 = strtod(src1str, NULL);
                    // double src2 = strtod(src2str, NULL);
                    // double retval = src1 + src2;
                    // char* retvalstr = NULL;

                    // asprintf(&retval, "%f", retval);

                    // return retval;

                }

                return EvalBranchOutcome(block, inst_wrap->prev, name, backedges);

                // inst->src1.name;
                // inst->src2.name;
                // inst->dst.name;
                // inst->type;
                // inst->cond;
                // copy->inst;

                break;
            }
        case AllocI:
            {
                AllocInst* inst = (AllocInst*)inst_wrap->inst;


                printf("No Support for AllocI %s:%d !!!", __FILE__, __LINE__);
                exit(0);


                // inst->dst.name = strdup(inst->dst.name);
                // inst->type = inst->type;

                break;
            }
        case AllocArrayStackI:
            {
                AllocArrayStackInst* inst = (AllocArrayStackInst*)inst_wrap->inst;

                printf("No Support for AllocArrayStackI %s:%d !!!", __FILE__, __LINE__);
                exit(0);

                // inst->dst.name = strdup(inst->dst.name);
                // inst->type = inst->type;
                // inst->dimen = inst->dimen;

                break;
            }
        case BitI:
            {
                BitInst* inst = (BitInst*)inst_wrap->inst;


                // inst->src1.name = strdup(inst->src1.name);
                // inst->src2.name = strdup(inst->src2.name);
                // inst->dst.name = strdup(inst->dst.name);
                // inst->type = inst->type;
                // inst->opc = inst->opc;

                break;
            }
        case InitSI:
            {
                InitStringInst* inst = (InitStringInst*)inst_wrap->inst;


                // inst->dst.name = strdup(inst->dst.name);
                // inst->string = strdup(inst->string);
                // inst->len = inst->len;

                break;
            }
        case LDStringI:
            {
                LDStringInst* inst = (LDStringInst*)inst_wrap->inst;


                // inst->src.name = strdup(inst->src.name);
                // inst->dst.name = strdup(inst->dst.name);
                // inst->len = inst->len;

                break;
            }
        case RetI:
            {
                RetInst* inst = (RetInst*)inst_wrap->inst;

                printf("No Support for RetI %s:%d !!!", __FILE__, __LINE__);
                exit(0);


                // inst->src.name = strdup(inst->src.name);
                // inst->typeList = inst->typeList; // TODO: Copy

                break;
            }
        case AllocStructI:
            {
                AllocStructInst* inst = (AllocStructInst*)inst_wrap->inst;

                printf("No Support for AllocStructI %s:%d !!!", __FILE__, __LINE__);
                exit(0);


                // inst->dst.name = strdup(inst->dst.name);
                // inst->typeList = inst->typeList; // TODO: Copy

                break;
            }
        case AllocArrayI:
            {
                AllocArrayInst* inst = (AllocArrayInst*)inst_wrap->inst;

                // inst->dst.name = strdup(inst->dst.name);
                // inst->eleType = inst->eleType;
                //inst->dimen = inst->dimen;

                break;
            }
        case CallI:
            {
                CallInst* inst = (CallInst*)inst_wrap->inst;

                printf("No Support for CallI %s:%d !!!", __FILE__, __LINE__);
                exit(0);


                // inst->src.name = strdup(inst->src.name);
                // inst->dst.name = strdup(inst->dst.name);
                // inst->retList = inst->retList; // TODO: Copy
                // inst->argList = inst->argList; // TODO: Copy
                // inst->isStruct = inst->isStruct;
                // copy->inst = inst;

                break;
            }
        case GetPtrI:
            {
                GetPtrInst* inst = (GetPtrInst*)inst_wrap->inst;

                printf("No Support for GetPtrI %s:%d !!!", __FILE__, __LINE__);
                exit(0);


                // inst->src.name = strdup(inst->src.name);
                // inst->dst.name = strdup(inst->dst.name);
                // inst->typeList = inst->typeList; // TODO: Copy
                // inst->index = inst->index;

                break;
            }
        case GetPtrArrayI:
            {
                GetPtrArrayInst* inst = (GetPtrArrayInst*)inst_wrap->inst;


                // inst->src.name = strdup(inst->src.name);
                // inst->dst.name = strdup(inst->dst.name);
                // inst->type = inst->type;
                // inst->dimen = inst->dimen;
                // inst->index = inst->index;

                break;
            }
        case ExtractI:
            {
                ExtractInst* inst = (ExtractInst*)inst_wrap->inst;

                printf("No Support for ExtractI %s:%d !!!", __FILE__, __LINE__);
                exit(0);


                // inst->src.name = strdup(inst->src.name);
                // inst->dst.name = strdup(inst->dst.name);
                // inst->typeList = inst->typeList; // TODO: Copy
                // inst->index = inst->index;

                break;
            }
        case PrintI:
            {
                PrintInst* inst = (PrintInst*)inst_wrap->inst;

                printf("No Support for PrintI %s:%d !!!", __FILE__, __LINE__);
                exit(0);


                break;
            }
        case LDStructI:
            {
                LoadStructInst* inst = (LoadStructInst*)inst_wrap->inst;

                printf("No Support for LDStructI %s:%d !!!", __FILE__, __LINE__);
                exit(0);


                break;
            }
        case ToFloatI:
            {
                ToFloatInst* inst = (ToFloatInst*)inst_wrap->inst;

                // inst->src.name = strdup(inst->src.name);
                // inst->dst.name = strdup(inst->dst.name);

                break;
            }
        case ToIntI:
            {
                ToIntInst* inst = (ToIntInst*)inst_wrap->inst;

                // inst->src.name = strdup(inst->src.name);
                // inst->dst.name = strdup(inst->dst.name);

                break;
            }
        default:
            // Error = TRUE;
            break;
    }

    return name;

}

void RemoveUnreachableBranchBlocks(CFG* cfg)
{
    BLOCK* currBlock = NULL;

    if (!cfg) return;
    if (!cfg->node) return;
    if (!cfg->node->basicBlock) return;

    currBlock = cfg->node->basicBlock;

    switch (currBlock->lastInst->instType)
    {
        case CondBrI:
            {
                Inst* original = currBlock->lastInst;
                CondBrInst* condBrInst = NULL;
                condBrInst = (CondBrInst *)original->inst;


                if (!EvalBranchOutcome(currBlock, currBlock->lastInst, condBrInst->src.name, cfg->backedges))
                {
                    // Replace with an Unconditional Branch
                    //
                    //
                    //


                    if (currBlock->prev->lastInst->instType == UncondBrI)
                    {


                        CFGList* preds = currBlock->cfg->preds;

                        currBlock->prev->next = currBlock->next;
                        UncondBrInst* ucinst = (UncondBrInst*)currBlock->prev->lastInst->inst;
                        ucinst->dst.name = strdup(condBrInst->dstFalse.name);

                        while (preds)
                        {
                            CFGEdgeList* backedges = cfg->backedges;
                            while (backedges)
                            {

                                if (!strcmp(preds->value->basicBlock->name,
                                            backedges->value->source->basicBlock->name) &&
                                    !strcmp(currBlock->name,
                                            backedges->value->target->basicBlock->name))
                                {
                                    CFGList* predsOfBackedge = backedges->value->source->basicBlock->cfg->preds;
                                    BLOCKList* stack = NULL;



                                    preds->value->basicBlock->ignore = 1;
                                    while (predsOfBackedge || stack)
                                    {

                                        if (predsOfBackedge)
                                        PushBlock(&stack, predsOfBackedge->value->basicBlock);

                                        if (stack && stack->block)
                                        {
                                            BLOCK* tmp = PopBlock(&stack);
                                            CFGList* BLOCKPreds = tmp->cfg->preds;

                                            tmp->ignore = 1;

                                            if (strcmp(tmp->name, backedges->value->target->basicBlock->name))
                                            {

                                                while (BLOCKPreds)
                                                {
                                                    PushBlock(&stack, BLOCKPreds->value->basicBlock);
                                                    BLOCKPreds = BLOCKPreds->next;
                                                }
                                            }

                                        }


                                        if (predsOfBackedge)
                                        predsOfBackedge = predsOfBackedge->next;
                                    }
                                }

                                backedges = backedges->next;
                            }

                            preds = preds->next;

                        }

                        // currBlock->prev->lastInst->instType

                    }
                    else if (currBlock->prev->lastInst->instType == CondBrI)
                    {
                        CFGList* preds = currBlock->cfg->preds;

                        currBlock->prev->next = currBlock->next;
                        CondBrInst* cinst = (CondBrInst*)currBlock->prev->lastInst->inst;
                        cinst->dstTrue.name = strdup(condBrInst->dstFalse.name);

                        while (preds)
                        {
                            CFGEdgeList* backedges = cfg->backedges;
                            while (backedges)
                            {

                                if (!strcmp(preds->value->basicBlock->name,
                                            backedges->value->source->basicBlock->name) &&
                                    !strcmp(currBlock->name,
                                            backedges->value->target->basicBlock->name))
                                {
                                    // preds->value->basicBlock->next = preds->value->basicBlock->next->next;
                                    //
                                    CFGList* predsOfBackedge = backedges->value->source->basicBlock->cfg->preds;
                                    BLOCKList* stack = NULL;



                                    preds->value->basicBlock->ignore = 1;
                                    while (predsOfBackedge || stack)
                                    {
                                        if (predsOfBackedge)
                                        PushBlock(&stack, predsOfBackedge->value->basicBlock);

                                        if (stack && stack->block)
                                        {
                                            BLOCK* tmp = PopBlock(&stack);
                                            CFGList* BLOCKPreds = tmp->cfg->preds;

                                            tmp->ignore = 1;

                                            if (strcmp(tmp->name, backedges->value->target->basicBlock->name))
                                            {

                                                while (BLOCKPreds)
                                                {
                                                    PushBlock(&stack, BLOCKPreds->value->basicBlock);
                                                    BLOCKPreds = BLOCKPreds->next;
                                                }
                                            }

                                        }

                                        if (predsOfBackedge)
                                        predsOfBackedge = predsOfBackedge->next;
                                    }

                                }

                                backedges = backedges->next;
                            }

                            preds = preds->next;

                        }

                       // printf("Not a UncondBrI %s:%d !!!", __FILE__, __LINE__);
                       //  exit(0);


                    }
                    else
                    {

                       printf("Instruction Not supported for branching.. %s:%d !!!", __FILE__, __LINE__);
                       exit(0);


                    }

                    /*
                    Inst* copy = NULL;
                    copy = (Inst *)malloc(sizeof(Inst));

                    if (!copy)
                    {
                        printf("Out of Memory at %s:%d !!!", __FILE__, __LINE__);
                        exit(0);
                    }

                    copy->instType = CondBrI;
                    copy->next = original->next;
                    copy->prev = original->prev;
                    copy->parent = original->parent;


                    CondBrInst* origInst = (CondBrInst*)original->inst;
                    UncondBrInst* newInst = (UncondBrInst*)malloc(sizeof(UncondBrInst));

                    if (!newInst)
                    {
                        printf("Out of Memory at %s:%d !!!", __FILE__, __LINE__);
                        exit(0);
                    }

                    // newInst->src.name = strdup(origInst->src.name);
                    newInst->dst.name = strdup(origInst->dstFalse.name);
                    copy->inst = newInst;


                    original->prev->next = newInst;
                    */

                }

                break;
            }
        default:
            break;
    }


    if (cfg->next)
    cfg->next->backedges = cfg->backedges;

    RemoveUnreachableBranchBlocks(cfg->next);
}
#endif

LOOPList* newLOOPList()
{
    LOOPList* newLOOPList = NULL;

    newLOOPList = (LOOPList*) malloc(sizeof(LOOPList));

    if (!newLOOPList)
    {
        printf("Out of Memory at %s:%d !!!", __FILE__, __LINE__);
        exit(0);
    }

    return newLOOPList;
}

void PushLOOP(LOOPList** looplist, CFGEdge* backedge)
{
    LOOP* loop = NULL;
    LOOPList* newlist = NULL;

    if (!looplist) return;
    if (!backedge) return;

    newlist = newLOOPList();
    loop = (LOOP*)malloc(sizeof(LOOP));

    if (!loop)
    {
        printf("Out of Memory at %s:%d !!!", __FILE__, __LINE__);
        exit(0);
    }

    newlist->value = loop;

    newlist->next = *looplist;
    *looplist = newlist;

    loop->body = backedge->target->fstSuccNode->basicBlock;
    loop->header = backedge->target->basicBlock;
    loop->preheader = backedge->target->preds->value->basicBlock;
    loop->backedge = backedge;

}

void PopulateLoops(CFG* cfg)
{
    CFGEdgeList* currEdge;
    LOOPList* newlist = NULL;

    if (!cfg) return;
    if (!cfg->backedges) return;

    currEdge = cfg->backedges;

    while (currEdge)
    {
        PushLOOP(&cfg->loops, currEdge->value);
        currEdge = currEdge->next;
    }

    PopulateLoops(cfg->next);
}

void RemoveDeadBackEdges(CFG* cfg)
{
    CFGEdgeList* currBackedge = NULL;
    CFGEdgeList* prevBackedge = NULL;

    if (!cfg) return;
    if (!cfg->backedges) return;

    // printf("dead backedge\n");

    currBackedge = cfg->backedges;

    while (currBackedge)
    {
        if (currBackedge->value->source->basicBlock->ignore ||
            currBackedge->value->target->basicBlock->ignore)
        {
            if (prevBackedge == currBackedge)
            {
                prevBackedge->next = prevBackedge->next->next;
            }
            else if (!prevBackedge)
            {
                cfg->backedges = currBackedge->next;
            }
        }

        prevBackedge = currBackedge;
        currBackedge = currBackedge->next;
    }
}

void freeCFGList(CFGList* list)
{
    CFGList* currList = NULL;

    if (!list) return;

    currList = list;

    while (currList)
    {
        CFGList* tmpToFree = currList;
        currList = currList->next;
        tmpToFree->value = NULL;
        tmpToFree->next = NULL;
        free(tmpToFree);
    }
}


void freeCFGNode(CFGNode* node)
{
    CFGNode* currNode;

    if (!node) return;

    freeCFGList(node->preds);
    freeCFGList(node->DOMSet);
    freeCFGList(node->PostDOMSet);
    node->DOMSet = NULL;
    node->PostDOMSet = NULL;
    node->basicBlock->cfg = NULL;
    node->basicBlock = NULL;
    node->fstSuccNode = NULL;
    node->preds = NULL;
    node->sndSuccNode = NULL;
    free(node);
}

void freeBackedges(CFGEdgeList* list)
{
   CFGEdgeList* currList = NULL;

    if (!list) return;

    currList = list;

    while (currList)
    {
        CFGEdge* tmpToFree  = currList->value;
        currList = currList->next;
        tmpToFree->source = NULL;
        tmpToFree->target = NULL;
        free(tmpToFree);
    }
}

void freeLoops(LOOPList* list)
{
    LOOPList* currList = NULL;

    if (!list) return;

    currList = list;

    while (currList)
    {
        LOOP* tmpToFree  = currList->value;
        currList = currList->next;
        tmpToFree->backedge = NULL;
        tmpToFree->body = NULL;
        tmpToFree->header = NULL;
        tmpToFree->preheader = NULL;
        free(tmpToFree);
    }
}

void freeCFG(CFG* cfg)
{
    CFG* cfgToFree = NULL;
    CFG* currCFG = cfg;
    CFGList* freedList = NULL;

    if (!cfg) return;

    while (currCFG)
    {

        CFGList* currFreed = freedList;

        /*
        while (currFreed)
        {
            if (currCFG->node == currFreed->value)
            {
                goto free_cfg;
            }
            currFreed = currFreed->next;
        }

        AddCFGNodePred(currCFG->node, &freedList);
        */

        //printf("cfg %x\n", currCFG);
        //printf("cfgnode %x\n", currCFG->node);

        freeCFGNode(currCFG->node);
        freeBackedges(currCFG->backedges);
        freeLoops(currCFG->loops);

     free_cfg:
        cfgToFree = currCFG;
        currCFG = currCFG->next;

        cfgToFree->node = NULL;
        cfgToFree->backedges = NULL;
        cfgToFree->loops = NULL;
        cfgToFree->func = NULL;
        cfgToFree->next = NULL;
        free(cfgToFree);
    }
}


void PopulateCFGStuff(CFG** cfg)
{
    if (!cfg) return;
    if (!*cfg) return;

    PopulatePostDOMSets((*cfg)->node);
    reverseCFGNodeList(cfg);
    PopulateDOMSets(cfg);
    reverseCFGNodeList(cfg);
    PopulateBackEdges(*cfg);
    PopulateLoops(*cfg);
    RemoveDeadBackEdges(*cfg);
}

