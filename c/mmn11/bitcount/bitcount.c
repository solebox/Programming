#include <stdio.h>

int bit_count(unsigned int num); /* counts lit bits in an unsigned integer */
int main(){ /*gets user inputed unsigned integer num then outputs
the number of the lit bits in that specific value's representation in the 
memory */ 
	unsigned int num;
	scanf("%u",&num);
	printf("the bits that are on:%u\n",bit_count(num));
	
	return 0;	
}
/*the function gets unsigned int num then counts the amount of lit bits
in it and returns the count , e.g: for 9 the output will be 2*/
int bit_count(unsigned int num){
	int count = 0;
	while (num){
		if (num & 1){
			count++;	
		}
		num>>=1;
	}	
	return count;	
}
