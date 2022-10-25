//
// Created by Mingxiang on 2022/10/9.
//
#include "LinkedBinaryTree.h"
#include <iostream>

using namespace std;

int main() {
    vector<char> orderVec = {'A', 'B', 'C', '#', '#', 'D', '#', '#', 'E', '#', '#'};
    LinkedBinaryTree<int> binaryTree(orderVec);
    return 0;
}