#include <stdio.h>
#include <string.h>

typedef struct{
    char a[29];    
    struct Person *b;
}Person;
int main(){
    Person kaka = {"woyo"};
    Person lala = {"lala",&((struct Person)kaka)};
    return 0; 
}
