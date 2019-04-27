#include "tLib.h"

void tNodeInit (tNode * node)
{
	node->nextNode = node;
	node->preNote = node;
}

#define firstNode headNode.nextNode
#define lastNode headNode.preNote

void tListInit (tList * list)
{
	list->firstNode = & (list->headNode);
	list->lastNode = & (list->headNode);
	list->nodeCount = 0;
}

uint32_t tListCount (tList * list)
{
	return list->nodeCount;
}

tNode * tListFirst (tList * list)
{
	tNode * node = (tNode *) 0;
	if(list->nodeCount != 0)
	{
		node = list->firstNode;
	}
	return node;
}

tNode * tListLast (tList * list)
{
	tNode * node = (tNode *) 0;
	if(list->nodeCount != 0)
	{
		node = list->lastNode;
	}
	return node;
}

tNode * tListPre (tList * list, tNode * node)
{
	if (node->preNote == node)
	{
		return (tNode *) 0;
	}
	else 
	{
		return node->preNote;
	}
}

tNode * tListNext (tList * list, tNode * node)
{
	if (node->nextNode == node)
	{
		return (tNode *)0;
	}
	else 
	{
		return node->nextNode;
	}
}

void tListRemoveAll (tList * list)
{
	uint32_t count;
	tNode * nextNote;
	
	nextNote = list->firstNode;
	for (count = list->nodeCount; count !=0; count--)
	{
		tNode * currentNote = nextNote;
		nextNote = nextNote->nextNode;
		
		currentNote->nextNode = currentNote;
		currentNote->preNote = currentNote;
	}
	list->firstNode = &(list->headNode);
	list->lastNode = &(list->headNode);
	list->nodeCount = 0;
}

void tListAddFirst (tList * list, tNode * node)
{
	node->preNote = list->firstNode->preNote;
	node->nextNode = list->firstNode;
	
	list->firstNode->preNote = node;
	list->firstNode = node;
	list->nodeCount++;
}

void tListAddLast (tList * list, tNode * node)
{
	node->nextNode = &(list->headNode);
	node->preNote = list->lastNode;
	
	list->lastNode->nextNode = node;
	list->lastNode = node;
	list->nodeCount++;
}

tNode * tListRemoveFirst (tList * list)
{
	tNode * node = (tNode *)0;
	if(list->nodeCount != 0)
	{
		node = list->firstNode;
		node->nextNode->preNote = &(list->headNode); //
		list->firstNode = node->nextNode;
		list->nodeCount--;
	}
	return node;
}
void tListInsertAfter (tList * list, tNode * nodeAfter, tNode * nodeToInsert)
{
	nodeToInsert->preNote =nodeAfter;
	nodeToInsert->nextNode = nodeAfter->nextNode;
	
	nodeAfter->nextNode->preNote = nodeToInsert;
	nodeAfter->nextNode = nodeToInsert;
	
	list->nodeCount++;
}
void tListRemove (tList * list, tNode * node)
{
	node->preNote->nextNode = node->nextNode;
	node->nextNode->preNote = node->preNote;
	list->nodeCount--;
}

