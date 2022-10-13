//
// Created by Mingxiang on 2022/10/9.
//
#include "LinkedBinaryTree.h"
#include <iostream>

using namespace std;
using namespace ProcessTreeNodeFuncSpace;

int main() {
    LinkedBinaryTree<int> binaryTree(1);
    binaryTree.preOrder(ProcessTreeNodeFuncSpace::output<int>);


    return 0;
}