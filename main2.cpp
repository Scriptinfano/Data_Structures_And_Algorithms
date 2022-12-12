#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

typedef struct {
    int number;
} person;

person createPerson(int num) {
    person thePerson;
    thePerson.number = num;
    return thePerson;
}

void delete_string(char str[], char ch) {
    int i = 2, j = 2;
    for (i = j = 0; j < 10; i++) {
        if (str[i] != ch)
            str[j++] = str[i];
    }
    str[j] = '\0';/*将结束符'\0'复制到最后被保留的字符后面*/
}

void print_string(char str[]) {
    printf("%s\n", str);
}

int main() {
    int i,j;
    int sum=0;
for(i=0,j=1;i<=j+1;i+=2,j--)
{
    printf("%d \n",i);
    sum++;
}
    printf("\n");
    printf("%d",sum);
    return 0;
}
