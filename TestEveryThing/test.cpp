//
// Created by Mingxiang on 2022/10/13.
//
#include <iostream>

using namespace std;
void printArray(int array[],int arraySize){
    for (int i = 0; i < arraySize; i++) {
        cout<<array[i]<<" ";
    }
}
int main() {
    int array[]={1,5,6,4,2,5};
    int arraySize=sizeof(array)/sizeof (array[0]);
    printArray(array,arraySize);
}