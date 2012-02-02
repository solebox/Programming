#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main(){
    char *input = (char *)malloc(20*sizeof(char));
    input = realloc(input,30*sizeof(char));
    char *part;
    char *string_array[5];
    int i = 1;
    fgets(input,30,stdin);
    string_array[0] = strtok(input,",");
    for (i = 1; i < 5; i++){
        string_array[i] = strtok(NULL,",");    
    }
    for (i = 0; i < 5; i++){
        if (string_array[i]){
            string_array[i] = strtok(string_array[i]," ");
            printf("%s",string_array[i]);
        }
    }
    free(input);
    return 0;    
}
