#include <stdio.h>

typedef struct {
    int array[4][4];
} DoubleArray;

int main() {
    DoubleArray objArray={{{12,13,13,2},{12,4,2,4},{12,42,13,14},{124,14,212,41}}};
/*
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            objArray.array[i][j] = i + j;

*/
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            printf("%d ", objArray.array[i][j]);


    return 0;
}
