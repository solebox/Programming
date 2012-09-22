#include <stdio.h>
#include <string.h>
typedef struct 
{
    char name[20];
    struct person;
    struct person *child1, *child2, *child3;
} Person;

void main()
{
    Person child1 = {"gili"};
    Person child2 = {"itai"};
    Person child3 = {"tom"};
    Person father = {"dad", &child1, &child2, &child3};
    printf("%s has son: %s, %s, %s",father.name, father.child1->name,
          father.&child2->name, 
          father.&child3->name);
}
