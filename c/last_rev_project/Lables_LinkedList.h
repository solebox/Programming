#ifndef _LabelsLinkedList_
#define _LabelsLinkedList_
#include <stdio.h>
#include "miscellaneous.h"

typedef struct{
	char* Label_Name;
	char Value_10[MAX_ADDRESS_DIGITS+1];
	char Value_12[MAX_ADDRESS_DIGITS+1];
	char label_type;
	struct labelNode *next;
}labelNode;
typedef struct 
{
	labelNode *next;
}LinkedList_Labels;


labelNode *CreateLabelNode();
labelNode *AddLabelItem(labelNode *head,char* labelName, char v10[],char v12[],char type);
labelNode *FindLabel(labelNode *head,char* labelToFind);
void CalculateAddressesForLabels(labelNode *head,int ICAddress);

#endif
