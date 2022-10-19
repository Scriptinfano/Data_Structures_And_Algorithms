#pragma once
#include "BinaryTreeNode.h"
#include <iostream>
using namespace std;

namespace ProcessTreeNodeFuncSpace {

    template<class T>
    void output(BinaryTreeNode<T> *theNode) {
        cout << theNode->getElement() << " ";
    }

    template<class T>
    void output_leaf(BinaryTreeNode<T> *theNode) {
        if (theNode->getLeftChild() == nullptr && theNode->getRightChild() == nullptr) {
            cout << theNode->getElement();
        }
    }

    template<class T>
    T getLeaf(BinaryTreeNode<T>*theNode){
        if (theNode->getLeftChild() == nullptr && theNode->getRightChild() == nullptr) {
            return theNode->getElement();
        } else return 0;

    }


}
