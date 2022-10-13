#pragma once

#include "BinaryTreeNode.h"
//#include "D:\ClionProjects\Data_Structures_And_Algorithms\Queue\arrayQueue.h"
#include "D:\ClionProjects\Data_Structures_And_Algorithms\tree\TreeADT.h"
#include <iostream>
#include <queue>
#include <stack>
#include <vector>

using namespace std;

template<class T>
class LinkedBinaryTree : public BinaryTreeADT<BinaryTreeNode<T>> {
    using TreeNode = BinaryTreeNode<T>;
    using NodePointer = BinaryTreeNode<T> *;
private:
    NodePointer root;//树的根节点
    int treeSize;//树的节点个数
    static void (*visit)(NodePointer theNode);

    static void preOrder(NodePointer theNode) {
        if (theNode == nullptr)return;
        visit(theNode);
        LinkedBinaryTree<T>::preOrder(theNode->getLeftChild());
        LinkedBinaryTree<T>::preOrder(theNode->getRightChild());

    }

    static void inOrder(NodePointer theNode) {
        if (theNode == nullptr)return;
        LinkedBinaryTree<T>::inOrder(theNode->getLeftChild());
        visit(theNode);
        LinkedBinaryTree<T>::inOrder(theNode->getRightChild());

    }

    static void postOrder(NodePointer theNode) {
        if (theNode == nullptr)return;
        LinkedBinaryTree<T>::postOrder(theNode->getLeftChild());
        LinkedBinaryTree<T>::postOrder(theNode->getRightChild());
        visit(theNode);

    }

    static void levelOrder(NodePointer theNode) {
        std::queue<NodePointer> pointerQueue;
        while (theNode != nullptr) {
            visit(theNode);
            if (theNode->getLeftChild() != nullptr)
                pointerQueue.push(theNode->getLeftChild());
            if (theNode->getRightChild() != nullptr)
                pointerQueue.push(theNode->getRightChild());
            if (pointerQueue.empty())
                return;
            else theNode = pointerQueue.front();
            pointerQueue.pop();
        }
    }

    static void dispose(NodePointer theNode) {
        delete theNode;
    }

    //被析构函数调用
    void erase() {
        postOrder(dispose);
        root = nullptr;
        treeSize = 0;
    }

    void countSize(NodePointer p, int &currentSize) {
        if (p != nullptr)return;
        currentSize++;
        countSize(p->getLeftChild(), currentSize);
        countSize(p->getRightChild(), currentSize);
    }

public:
    explicit LinkedBinaryTree(const T &theElement) {
        root = new TreeNode(theElement);
        treeSize = 1;
        visit = nullptr;
    }

    explicit LinkedBinaryTree() {
        root = new TreeNode();
        treeSize = 0;
        visit = nullptr;
    }

    ~LinkedBinaryTree() { erase(); }

    NodePointer getRoot() const {
        return root;
    }

    //访问并输出指定的节点
    void output(NodePointer theNode) {
        std::cout << theNode->getElement() << " ";
    }

    //插入节点，每插入一个节点treeSize++，每插入一个节点都要保证二叉树是完全二叉树
    void insertNode(NodePointer theNode) {
        //TODO 向二叉树插入节点

    }

    bool empty() const override {
        return treeSize == 0;
    }

    //直接返回内部统计树节点变量
    int size() const override {
        return treeSize;
    }

    //用算法统计二叉树中的节点个数
    int size_algorithm() {
        int size = 0;
        countSize(root, size);
        return size;
    }

    void preOrder(void (*pFunction)(NodePointer)) override {
        visit = pFunction;
        LinkedBinaryTree<T>::preOrder(root);//调用类内定义的静态函数
    }

    void inOrder(void (*pFunction)(NodePointer)) override {
        visit = pFunction;
        LinkedBinaryTree<T>::inOrder(root);//调用类内定义的静态函数
    }

    void postOrder(void (*pFunction)(NodePointer)) override {
        visit = pFunction;
        LinkedBinaryTree<T>::postOrder(root);//调用类内定义的静态函数
    }

    void levelOrder(void (*pFunction)(NodePointer)) override {
        visit = pFunction;
        LinkedBinaryTree<T>::levelOrder(root);//调用类内定义的静态函数
    }

    //二叉树遍历的非递归实现，每个函数返回遍历的结果
    vector<int> preOrder_noRecursion() {
        stack<NodePointer> nodeStack;
        vector<int> result;//存放遍历的结果
        nodeStack.push(root);//根节点入栈
        while (!nodeStack.empty()) {
            NodePointer p = nodeStack.pop();
            if (p != nullptr)
                result.push_back(p->getElement());
            else continue;
            nodeStack.push(p->getRightChild());//一定要先放右再放左，出栈时才能达到先左后右的顺序
            nodeStack.push(p->getLeftChild());
        }
        return result;
    }

    vector<int> inOrder_noRecursion() {
        stack<NodePointer> nodeStack;
        vector<int> result;
        NodePointer p = root;//根节点指针
        while (p != nullptr || !nodeStack.empty()) {
            if (p != nullptr) {
                nodeStack.push(p);
                p = p->getLeftChild();
            } else {
                p = nodeStack.pop();
                result.push_back(p->getElement());
                p = p->getRightChild();
            }
        }
        return result;
    }

    vector<int> postOrder_noRecursion() {
        //对前序遍历的代码进行一点改进即可实现后序结果的输出
        //因为前序是根左右，将左后颠倒变为根右左，在反转即得到左右根，即得到了后序遍历

        stack<NodePointer> nodeStack;
        vector<int> result;//存放遍历的结果
        nodeStack.push(root);//根节点入栈
        while (!nodeStack.empty()) {
            NodePointer p = nodeStack.pop();
            if (p != nullptr)
                result.push_back(p->getElement());
            else continue;
            nodeStack.push(p->getLeftChild());//对调前序遍历中左右孩子入栈的顺序，最后在颠倒数组即可实现后序遍历
            nodeStack.push(p->getRightChild());
        }
        reverse(result.begin(), result.end());//颠倒数组
        return result;

    }

    //计算叶子节点的个数，调用时需要传入树的根节点
    int getLeafSize(NodePointer p) {
        int leftLeaf = 0, rightLeaf = 0;
        if (p == nullptr)return 0;
        if (p->getLeftChild() == nullptr && p->getRightChild() == nullptr)return 1;
        leftLeaf = getLeafSize(p->getLeftChild());
        rightLeaf = getLeafSize(p->getRightChild());
        return leftLeaf + rightLeaf;
    }

    int getLeafSize() {
        int leftLeaf = 0, rightLeaf = 0;
        leafCount(root, leftLeaf, rightLeaf);
        return leftLeaf + rightLeaf;
    }

    //求二叉树高度，二叉树的高度是树中任意一个节点到叶子节点的距离，求二叉树高度需要使用后序遍历
    int getHeight(NodePointer p) {
        if (p == nullptr)
            return 0;//返回的其实是p所指向的子节点的高度，只不过此时p是null且指向了叶子节点，因为叶子节点没有子节点所以应该返回0
        else {
            //求二叉树的高度采用后序遍历
            int leftHigh = getHeight(p->getLeftChild());//遍历左
            int rightHigh = getHeight(p->getRightChild());//遍历右
            int high = (leftHigh > rightHigh ? leftHigh : rightHigh) + 1;//树高度应为其左右子树高度的较大值加1
            return high;
            //上面四行代码可以合并成一行：return 1+max(getHeight(p->getLeftChild()),getHeight(p->getRightChild()));
        }
    }

    //求二叉树的深度，二叉树的深度是树中任意一个节点到根节点的距离，求二叉树深度需要使用前序遍历
    //根节点的高度就是二叉树的最大深度
    //TODO 求二叉树的深度，编写相关代码

    //寻找指定节点的双亲节点，在以theRoot为根节点的二叉树中寻找节点target的父节点
    NodePointer getParent(NodePointer theRoot, NodePointer target) {
        NodePointer p = nullptr;
        if (theRoot == nullptr)return nullptr;
        if (theRoot->getLeftChild() == target || theRoot->getRightChild() == target)
            return theRoot;
        p = getParent(theRoot->getLeftChild(), target);//在左子树中递归寻找
        if(p!= nullptr)return p;//在左子树中找到了
        else return getParent(theRoot->getRightChild(),target);//在左子树中没有找到，在右子树中递归查找
    }

    //TODO 打印输出二叉树，编写相关代码

private:

    //TODO 自己写的，未经测试
    void leafCount(NodePointer p, int &leftSize, int &rightSize) {
        if (p == nullptr || p->getLeftChild() == nullptr && p->getRightChild() == nullptr)
            return;
        else if (p->getLeftChild() != nullptr) {
            leftSize++;
        } else {
            rightSize++;
        }
        leafCount(p->getLeftChild(), leftSize, rightSize);
        leafCount(p->getRightChild(), leftSize, rightSize);
    }


};

namespace ProcessTreeNodeFuncSpace {

    template<class T>
    void output(BinaryTreeNode<T> *theNode) {
        std::cout << theNode->getElement() << " ";
    }

    template<class T>
    void output_leaf(BinaryTreeNode<T> *theNode) {
        if (theNode->getLeftChild() == nullptr && theNode->getRightChild() == nullptr) {
            cout << theNode->getElement();
        }
    }


}
