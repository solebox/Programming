#include <stdio.h>

#ifndef _LinkageLinkedList_
#define _LinkageLinkedList_
#include "Enums.h"
#include "Global_Defines.h"
#include "miscellaneous.h"
#include "Lables_LinkedList.h"

typedef struct{
	enum Directive directive;
	char* name;
	char* lineNumber;
	struct linkageNode *next;
}linkageNode;
typedef struct 
{
	linkageNode *next;
}LinkedList_Linkage;


linkageNode *CreateLinkageNode();
void AddLinkageItem(LinkedList_Linkage *head,enum Directive what_directive,char* directiveName,char *lineNumber);
linkageNode *FindLinkage(LinkedList_Linkage *head,char* directiveName,enum Directive directiveToFind);
linkageNode *GoToEndOfLinkageList(LinkedList_Linkage *head);
void UpdateEntryLabels(LinkedList_Linkage *linkage,labelNode *labels);
linkageNode *RetreiveLinkageItem(LinkedList_Linkage *head);
enum Boolean IsLinkageListEmpty(LinkedList_Linkage *head);
char *FindMinimalLineInLinkageList(LinkedList_Linkage *L);
void RemoveItemFromLinkageList(LinkedList_Linkage *L,char* lineNumber,char* name);
#endif
