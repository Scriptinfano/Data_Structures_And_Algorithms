//
// Created by Mingxiang on 2022/10/13.
//
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int arr[] = {4, 5, 8, 10, 13};
    int size1 = sizeof(arr) / sizeof(arr[0]);
    int arr2[] = {3, 4, 6, 7, 9, 11};
    int size2 = sizeof(arr2) / sizeof(arr2[0]);
    vector<int> mergeArray;
    int *i = &arr[0], *j = &arr2[0];
    while (i < arr + size1 && j < arr2 + size2) {
        if (*i < *j) {
            mergeArray.push_back(*i);
            i++;
        } else if (*i > *j) {
            mergeArray.push_back(*j);
            j++;
        } else {
            mergeArray.push_back(*i);
            i++;
            j++;
        }
    }
    if (i == arr + size1)
        while (j < arr2 + size2) {
            mergeArray.push_back(*j);
            j++;
        }
    else
        while (i < arr + size1) {
            mergeArray.push_back(*i);
            i++;
        }
    for (int i: mergeArray)
        cout << i << " ";


    return 0;
}