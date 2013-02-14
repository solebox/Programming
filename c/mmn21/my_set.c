#include "header.h"
/*this calls all the functions that reside in the data_struct.c file and shows only the main logic of the program*/
int main(){
	int num;
	initialize_set(); /* initializes the datastructure by creating an empty array on the heap with malloc*/
		while (scanf("%d",&num) == 1) /*while we get input and not EOF*/
			if (!in_set(num)) /* if the number is not in the set*/
				add_to_set(num); /*add it to the set*/
	print_set(); /*output the resulting set to stdout*/
	freeset();/*free the allocated memory :)*/
	return 0;	
}
