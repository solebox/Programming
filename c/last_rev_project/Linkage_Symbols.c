#include <malloc.h>
#include <string.h>
#include "Linkage_Symbols.h"

linkageNode *CreateLinkageNode()
{
	linkageNode *newNode = (linkageNode*) malloc(sizeof(linkageNode));
	
	if (!newNode) 
	{
		ErrorHandler(OutOfMemory,"while creating linkage list");
	}
	newNode->next = NULL;
	newNode->directive=NONE;
	newNode->lineNumber=NULL;
	newNode->name=NULL;
	return newNode;
}
void AddLinkageItem(LinkedList_Linkage *head,enum Directive what_directive,char* directiveName,char *lineNumber)
{
	linkageNode *lastNode,*newNode;
	char *errmsg=NULL;
	
	if(what_directive==ENTRY)
		if(FindLinkage(head,directiveName,what_directive)!=NULL)
		{
			ALLOCATE_STRING(errmsg,100);
			strcpy(errmsg,"The entry '");
			strcat(errmsg,directiveName);
			strcat(errmsg,"' already declared\n");

			ErrorHandler(CompilingError,errmsg);
			return;
		}
			
	newNode=CreateLinkageNode();
	ALLOCATE_STRING(newNode->name,strlen(directiveName));
	strcpy(newNode->name,directiveName);
	ALLOCATE_STRING(newNode->lineNumber,strlen(lineNumber));
	strcpy(newNode->lineNumber,lineNumber);
	newNode->directive=what_directive;
	lastNode=GoToEndOfLinkageList(head);
	newNode->next=NULL;
	if(lastNode==NULL)
		head->next=newNode;
	else
		lastNode->next=newNode;
	
}
linkageNode *GoToEndOfLinkageList(LinkedList_Linkage *head)
{
	linkageNode *current;
	if(head->next==NULL)
		return NULL;
	current=head->next;
	while(current->next!=NULL)
		current=current->next;
	
	return current;
}
linkageNode *FindLinkage(LinkedList_Linkage *head,char* directiveName,enum Directive directiveToFind)
{
	linkageNode *position;
	if(head->next==NULL)
		return NULL;
	position=head->next;
	while(1)
	{
		if(position->directive==directiveToFind && strcmp(position->name,directiveName)==0)
			return position;
		else if(position->next==NULL)
			return NULL;
		else 
			position=position->next;
	}
	return NULL;
}
void UpdateEntryLabels(LinkedList_Linkage *linkage,labelNode *labels)
{
	linkageNode *position;
	labelNode* tmpLabel;
	char* errmsg=NULL;
	if(linkage->next==NULL)
		return;
	position=linkage->next;
	while(position!=NULL)
	{
		if(position->directive==ENTRY)
		{
			tmpLabel=FindLabel(labels,position->name);
			if(tmpLabel!=NULL)
			{
				strcpy(position->lineNumber,tmpLabel->Value_12);
			}
			else
			{
				ALLOCATE_STRING(errmsg,100);
				strcpy(errmsg,"the label '");
				strcat(errmsg,position->name);
				strcat(errmsg,"' wasn't defined though it was declared as entry");
				ErrorHandler(CompilingError,errmsg);
			}
		}
		position=position->next;
	}
}
enum Boolean IsLinkageListEmpty(LinkedList_Linkage *head)
{
	if(head->next==NULL)
		return TRUE;
	return FALSE;
}
linkageNode *RetreiveLinkageItem(LinkedList_Linkage *head)
{
	linkageNode *temp;
	if(IsLinkageListEmpty(head))
		return NULL;
	temp=head->next;
	head->next=head->next->next;
	return temp;

}	
void RemoveItemFromLinkageList(LinkedList_Linkage *L,char* lineNumber,char* name)
{
	linkageNode *node,*temp,*prev;
	temp=L->next;

	while(temp!=NULL)
	{
		if(temp==L->next)
		{
			if(strcmp(temp->lineNumber,lineNumber)==0 &&strcmp(temp->name,name)==0)
			{
				node=temp;
				L->next=node->next;
				free(node);
				return;
			}
			else
			{
				prev=temp;
				temp=temp->next;
			}
		}
		else 
		{
			if(strcmp(temp->lineNumber,lineNumber)==0 &&strcmp(temp->name,name)==0)
			{
				node=temp;
				prev->next=temp->next;
				free(node);
				return;
			}
			else
			{
				prev=temp;
				temp=temp->next;
			}
		}
	}
}
char *FindMinimalLineInLinkageList(LinkedList_Linkage *L)
{
	char *min=NULL;
	linkageNode *temp;
	temp=L->next;
	FIX_NULL_STRING(min);
	strcpy(min,"0");
	min[0]='9'+1;
	while(temp!=NULL)
	{
		if(strcmp(temp->lineNumber,min)==-1)
			strcpy(min,temp->lineNumber);
		temp=temp->next;
	}
	return min;

}

