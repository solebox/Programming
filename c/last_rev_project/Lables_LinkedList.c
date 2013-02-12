#include <malloc.h>
#include <string.h>
#include "Global_Defines.h"
#include "Lables_LinkedList.h"

/* creates a lable node for the linked list*/
labelNode *CreateLabelNode()
{
	labelNode *newNode = (labelNode*) malloc(sizeof(labelNode));
	
	if (!newNode) 
		return NULL;
	newNode->next = NULL;

	return newNode;
}
/*function adds a lable element to the list*/
labelNode *AddLabelItem(labelNode *head,char* labelName, char v10[],char v12[],char type)
{
	labelNode *currentNode,*newNode;
	char *errmsg=NULL;
	if(FindLabel(head,labelName)!=NULL)
	{
		FIX_NULL_STRING(errmsg);
		strcpy(errmsg,labelName);
		ErrorHandler(CompilingError,errmsg);
		strcat(errmsg," - label already defined");
		ErrorHandler(CompilingError,errmsg);
		return NULL;
	}
	newNode=CreateLabelNode();
	currentNode=head;
	
	newNode->next=NULL;
	newNode->Label_Name=(char*)malloc(strlen(labelName)*(sizeof(char)));
	strcpy(newNode->Label_Name,labelName);
	strcpy(newNode->Value_10,v10);
	strcpy(newNode->Value_12,v12);
	newNode->label_type=type;
		while(currentNode->next!=NULL)
		currentNode=currentNode->next;
	currentNode->next=newNode;
	return head;
}
/*find label node in list*/
labelNode *FindLabel(labelNode *head,char* labelToFind)
{
	labelNode *position;
	if(head==NULL)
		return NULL;
	position=head->next;
	while(position!=NULL)
	{
		if(strcmp(position->Label_Name,labelToFind)==0)
			return position;
		position=position->next;
	}
	return NULL;
}
/* function calculates wht address should be inserted for the label*/
void CalculateAddressesForLabels(labelNode *head,int ICAddress)
{
	labelNode *currentNode;
	int num;
	if(head==NULL)
		return;
	currentNode=head->next;
	while(currentNode!=NULL)
	{
		if(currentNode->label_type=='d')
		{
			num=ConvertCharToInt(currentNode->Value_10);
			num+=ICAddress;
			strcpy(currentNode->Value_10,ConvertIntToCharByBase(num,ConversionToAddress,10));
			strcpy(currentNode->Value_12,ConvertIntToCharByBase(num,ConversionToAddress,12));
		}
			currentNode=currentNode->next;
	}
}
