#include <stdio.h>
#include <stdlib.h>
#define NUM 45 
int fibo(int *a,int n);
int main(){
   int *a;
   int i = 0;
   a = malloc(NUM*100);
   fibo(a,NUM);
   for (i = 0; i <= NUM; i++){
    printf("%d\n",a[i]);
   }
   free(a);
   return 0;    
}
int fibo(int *a,int n){
     if (n == 0 || n == 1)
        return a[n] = 1;
     else{
        return (a[n] =  fibo(a,n-1)+fibo(a,n-2));
     }
}

