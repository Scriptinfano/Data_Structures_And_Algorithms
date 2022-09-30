#include <stdio.h>
#include <malloc.h>
int main()
{
    int *p=(int*) malloc(sizeof(int));
    *p=12;
    printf("%d",*p);



    return 0;
}