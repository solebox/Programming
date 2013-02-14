#include "header.h"
static int *set; 
static int setsize = 0;
/* we have to start from some malloc to be able to use realloc later hence we use this method to initialize the data struct*/
void initialize_set(){
	set = (int *)malloc(sizeof(int));
	setsize = 0; /* the logical size is 0 but the actual memsize is 1*intsize a small secrifice to pay :) */
}
void add_to_set(int num){ /*this method adds a number to the set , no questions asked. if the needed memory wont allocate it will crash the program nicely*/
	int *temp;
	setsize += 1; /*increment setsize , we are adding a number :)*/
	temp = (int *)realloc(set,setsize*sizeof(int));/* enlarge the datastructure by one */
	if (temp != NULL) /*if we did get more memory let set point to it*/
		set = temp;
	else{/*if we didnt , crash and burn but tell us about it and give a nice exit code for linux :)*/
		printf("Fatal Error: it seems that for some reason we cant use anymore Virtual memory,"\
		"preparing for crash in 3, 2, 1 .... thank you for using EverSoft(TM), \"the software that never fails\","\
		"and have a nice day :)");
		exit(1);
	}
	*(set+setsize-1) = num;	/*finally put the number in its rightful place , i could have used the array syntax but i wanted to show i know pointer :P*/
}
void print_set(){/*output the set to stdout*/
	int i;
	for (i = 0; i < setsize;i++)/*simpy iterated over the array like it would over a regular array on the stack and prints out what is needed*/
		printf(i < setsize-1?"%d ":"%d\n",set[i]);/*i used the trinary expression to make things look nice :P*/
}
int in_set(int num){ /*checks if a given int is in the set , returns status:1/0 to say if it is true or false */
	int i;
	int status = FALSE;/*false till said otherwise*/
	for (i = 0; i < setsize;i++)/* iterate over the array*/
		if(set[i] == num)/*if the number is in the set*/
			status = TRUE;/*status = 1 (true)*/
	return status;
}
void freeset(){/*simply frees the allocated space, needed since the set is encapsulated :)*/
	free(set);	
}
