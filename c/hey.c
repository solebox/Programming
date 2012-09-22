#include <stdio.h>
#include <stdlib.h>
#include <time.h>
unsigned int integer = 0;
unsigned long longint = 0;
unsigned char character = 0;
int main(void)
{
    srand(80); 
    printf("%d \n",rand());
    printf("%d \n",rand());
    printf("%d \n",rand());
    printf("%u \n",sizeof(long int));
    printf("%u \n",sizeof(char));
	printf("hello world\n");
    if (1)
        if (0)
            printf("second if\n");
        else
            printf("kaka2\n");
	return 0;
}
