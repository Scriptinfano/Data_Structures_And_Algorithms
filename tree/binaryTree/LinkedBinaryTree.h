#pragma once

#include "BinaryTreeNode.h"
#include "D:\ClionProjects\Data_Structures_And_Algorithms\Queue\arrayQueue.h"
#include "D:\ClionProjects\Data_Structures_And_Algorithms\tree\TreeADT.h"
#include <iostream>


template<class T>
class LinkedBinaryTree : public BinaryTreeADT<BinaryTreeNode<T>> {
    using TreeNode = BinaryTreeNode<T>;
    using NodePointer = BinaryTreeNode<T> *;
private:
    NodePointer root;//树的根节点
    int treeSize;//树的节点个数
    static void (*visit)(NodePointer theNode);

    static void preOrder(NodePointer theNode) {
        if (theNode == nullptr) {
            return;
        }
        visit(theNode);
        preOrder(theNode->getLeftChild());
        preOrder(theNode->getRightChild());

    }

    static void inOrder(NodePointer theNode) {
        if (theNode == nullptr)return;
        inOrder(theNode->getLeftChild());
        visit(theNode);
        inOrder(theNode->getRightChild());

    }

    static void postOrder(NodePointer theNode) {
        if (theNode == nullptr)return;
        postOrder(theNode->getLeftChild());
        postOrder(theNode->getRightChild());
        visit(theNode);

    }

    static void levelOrder(NodePointer theNode) {
        ArrayQueue<NodePointer> queue;
        while (theNode != nullptr) {
            visit(theNode);
            if (theNode->getLeftChild() != nullptr)
                queue.push_infinite(theNode->getLeftChild());
            if (theNode->getRightChild() != nullptr)
                queue.push_infinite(theNode->getRightChild());
            try {
                theNode = queue.front();
            } catch (QueueEmptyException &) {
                return;
            }
            queue.pop();
        }
    }

    static void dispose(NodePointer theNode) {
        delete theNode;
    }

    void erase() {
        postOrder(dispose);
        root = nullptr;
        treeSize = 0;
    }

public:
    LinkedBinaryTree(const T &theElement) {
        root = new TreeNode(theElement);
    }

    ~LinkedBinaryTree() { erase(); }

    //访问并输出指定的节点
    void output(NodePointer theNode) {
        cout << theNode->getElement() << " ";
    }

    //访问根节点
    NodePointer getRoot() const {
        return root;
    }

    //插入节点
    void insertNode(NodePointer theNode){
        NodePointer currentNode=root;
        NodePointer preNode;
        while(currentNode!= nullptr){
            preNode=currentNode;
            if(currentNode->getElement()>theNode->getElement()){
                currentNode=currentNode->getLeftChild();
            } else {
                currentNode=currentNode->getRightChild();
            }
            
        }
    }

    bool empty() const override {
        return treeSize == 0;
    }

    int size() const override {
        return treeSize;
    }


    void preOrder(void (*pFunction)(NodePointer)) override {
        visit = pFunction;
        preOrder(root);
    }

    void inOrder(void (*pFunction)(NodePointer)) override {
        visit = pFunction;
        inOrder(root);
    }

    void postOrder(void (*pFunction)(NodePointer)) override {
        visit = pFunction;
        postOrder(root);
    }

    void levelOrder(void (*pFunction)(NodePointer)) override {
        visit = pFunction;
        levelOrder(root);
    }

};

namespace ProcessTreeNodeFuncSpace {

    template<class T>
    void output(BinaryTreeNode<T> *theNode) {
        cout << theNode->getElement() << " ";
    }


}
