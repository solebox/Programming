#include <stdio.h>

int bit_count(unsigned int num); /* a function that counts how many bits are on in an unsigned integer*/ 
int int_bitsize(void); /*a method that counts how many bits are allocated in the memory for one unsigned int*/
unsigned int bit_shift(unsigned int num); /* a method that takes an int
counts how many bits it has lit and then creates a new one with the same 
amount of bits lit only they are all indented to the left
e.x: 00011 will result in: 11000 
     and so will 01001 */

int main(){ /* shows the output of bit_shift for 0, 4 and 9*/
	printf("%u\n",bit_shift(0));
	printf("%u\n",bit_shift(4));
	printf("%u\n",bit_shift(9));
	return 0;
}
/*gets an unsigned int num and returns the amount of lit bits in it*/
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
/* returns the amount of bits an unsigned int gets allocated for it in 
the given system and compiler */
int int_bitsize(){
	unsigned int int1,counter;
	for(int1 = 1, counter = 0; int1 ; int1<<=1,counter++);
	return counter;
}
/* gets an unsigned int num and returns a new unsigned int with the same
amount of bits only shifted to the left
by counting the amount of lit bits in the input int then inserting them
into a new int (temp) one by one by using the "|" operator and shifting them
to the left using the "<<" operator
e.g: 000101 will return 110000 */
unsigned int bit_shift(unsigned int num){
	int on_bitcount = bit_count(num);
	int total_bitcount = int_bitsize();
	int counter;
	unsigned int temp = 0;
	if (num == 0)
		return 0;
	for (counter = 1; (counter < total_bitcount) && (counter < on_bitcount); counter++){
	        temp = temp | 1;
		temp<<=1;
	}
	temp = temp | 1;
	temp<<=(total_bitcount-counter);
	return temp;
}
