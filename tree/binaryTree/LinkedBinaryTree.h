#pragma once

#include "BinaryTreeNode.h"
//#include "D:\ClionProjects\Data_Structures_And_Algorithms\Queue\arrayQueue.h"
#include "D:\ClionProjects\Data_Structures_And_Algorithms\tree\TreeADT.h"
#include <iostream>
#include <queue>
#include <stack>
#include <vector>

using namespace std;

//用链表实现的二叉树，可线索化
template<class T>
class LinkedBinaryTree : public BinaryTreeADT<BinaryTreeNode<T>> {
    using TreeNode = BinaryTreeNode<T>;
    using NodePointer = BinaryTreeNode<T> *;

private://私有成员变量
    NodePointer root;//树的根节点
    int treeSize;//树的节点个数
    static void (*visit)(NodePointer theNode);

    bool hasThread;//指示是否经过线索化

private://私有静态函数
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


public:
    explicit LinkedBinaryTree(const T &theElement) {
        root = new TreeNode(theElement);
        treeSize = 1;
        visit = nullptr;
        hasThread = false;
    }

    explicit LinkedBinaryTree() {
        root = new TreeNode();
        treeSize = 0;
        visit = nullptr;
        hasThread = false;
    }

    enum construct_mode {
        PREORDER,
        INORDER,
        POSTORDER
    };

    //传入一个代表前序序列或中序序列或后序序列的遍历结果的数组，根据数组来构造二叉树
    explicit LinkedBinaryTree(const vector<char> &orderVec, enum construct_mode theMode) {
        NodePointer p = root;
        create(*orderVec.begin(), p, theMode);

    }

private:
    void create(const char &theElement, NodePointer &p, enum construct_mode theMode) {
        switch (theMode) {
            case PREORDER: {
                //传入的vec代表前序序列
                if (theElement == '#')

            }
                break;
            case INORDER: {
                //传入的vec代表中序序列
            }
                break;
            case POSTORDER: {
                //传入的vec代表后序序列
            }
                break;
        }

    }

public:
    ~LinkedBinaryTree() { erase(); }

    NodePointer getRoot() const {
        return root;
    }

public:
    //插入节点，每插入一个节点treeSize++，每插入一个节点都要保证二叉树是完全二叉树
    void insertNode(const T &theElement) {
        //TODO 向二叉树插入节点
        auto newNode = new TreeNode(theElement);

    }

    //判断二叉树是否为空
    bool empty() const override {
        return treeSize == 0 && root == nullptr;
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

    //使用前序遍历的方式对每个节点执行某操作，参数是函数指针，指向要对节点做操作的函数
    void preOrder(void (*pFunction)(NodePointer)) override {
        visit = pFunction;
        LinkedBinaryTree<T>::preOrder(root);//调用类内定义的静态函数
    }

    //使用中序遍历的方式对每个节点执行某操作，参数是函数指针，指向要对节点做操作的函数
    void inOrder(void (*pFunction)(NodePointer)) override {
        visit = pFunction;
        LinkedBinaryTree<T>::inOrder(root);//调用类内定义的静态函数
    }

    //使用后序遍历的方式对每个节点执行某操作，参数是函数指针，指向要对节点做操作的函数
    void postOrder(void (*pFunction)(NodePointer)) override {
        visit = pFunction;
        LinkedBinaryTree<T>::postOrder(root);//调用类内定义的静态函数
    }

    //使用后序遍历的方式对每个节点执行某操作，参数是函数指针，指向要对节点做操作的函数
    void levelOrder(void (*pFunction)(NodePointer)) override {
        visit = pFunction;
        LinkedBinaryTree<T>::levelOrder(root);//调用类内定义的静态函数
    }

    //二叉树遍历的非递归实现，每个函数返回遍历的结果

    //前序遍历的非递归实现
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

    //中序遍历的非递归实现
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

    //后序遍历的非递归实现
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

    //使用递归的方式计算叶子节点的个数
    int getLeafSize() {
        int leftLeaf = 0, rightLeaf = 0;
        if (root == nullptr)return 0;
        if (root->getLeftChild() == nullptr && root->getRightChild() == nullptr)return 1;
        leftLeaf = getLeafSize(root->getLeftChild());
        rightLeaf = getLeafSize(root->getRightChild());
        return leftLeaf + rightLeaf;
    }

    //使用递归的方式计算叶子节点个数，自开发版本未测试
    int getLeafSize2() {
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
    //p指向二叉树链表中任意的节点
    int getDepth(NodePointer p) {
        //TODO 求二叉树的深度，编写相关代码

    }

    //寻找指定节点的双亲节点，在以theRoot为根节点的二叉树中寻找节点target的父节点
    NodePointer getParent(NodePointer target) {
        NodePointer p = nullptr;
        if (root == nullptr)return nullptr;
        if (root->getLeftChild() == target || root->getRightChild() == target)
            return root;
        p = getParent(root->getLeftChild(), target);//在左子树中递归寻找
        if (p != nullptr)return p;//在左子树中找到了
        else return getParent(root->getRightChild(), target);//在左子树中没有找到，在右子树中递归查找
    }

    //打印输出二叉树
    void printTree() {
        //TODO 打印输出二叉树，编写相关代码

    }


    //对二叉树进行线索化，从根节点开始对二叉树线索化
    void cueing() {
        //第一个遍历的节点的左孩子为空，最后一个遍历的节点的右孩子为空

        NodePointer pre = nullptr;//总是指向正在遍历的节点的前驱节点
        if (root != nullptr) {
            NodePointer p = root;//指向正在遍历的节点
            inThread(p, pre);//开始整个遍历过程，这是一个递归函数，在中序遍历二叉树的过程中线索化
            //此时p指向根节点，在递归的过程中，p最后回溯到了根节点
            //pre此时指向最后一个节点，此时最后一个节点的右孩子必须置空
            pre->setRightChild(nullptr);
            pre->setRightTag(true);
            hasThread = true;
        } else {
            //根节点为空的情况，无法线索化
            hasThread = false;
        }
    }

private:

    //线索化二叉树的递归函数（属于内部实现），此处采用中序遍历线索化二叉树
    void inThread(NodePointer &p, NodePointer &pre) {
        //首次在外部调用该递归函数时，p不会是nullptr，该递归出口即p==nullptr

        //该递归函数返回的条件即是p==nullptr
        if (p != nullptr) {
            inThread(p->getLeftChild(), pre);//中序遍历中的左遍历

            //////////////中序遍历的处理流程如下///////////////////
            if (p->getLeftChild() == nullptr) {
                //如果p的左孩子为空，则给p加上左线索，将leftTag置true，让p的左孩子指针指向pre（前驱），否则将p的leftTag置为false
                p->setLeftChild(pre);
                p->setLeftTag(true);
            }
            if (pre != nullptr && pre->getRightChild() == nullptr) {
                pre->setRightChild(p);//前驱节点如果没有右孩子则其右指针域指向后继
                pre->setRightTag(true);
            }
            pre = p;//更新前驱节点
            ///////////////////////////////////////////////

            inThread(p->getRightChild(), pre);//中序遍历的右遍历，继续递归线索化右子树
        }

    }


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

    //被析构函数调用
    void erase() {
        postOrder(dispose);//采用前序遍历的方式对每个节点执行删除操作
        root = nullptr;
        treeSize = 0;
    }

    void countSize(NodePointer p, int &currentSize) {
        if (p != nullptr)return;
        currentSize++;
        countSize(p->getLeftChild(), currentSize);
        countSize(p->getRightChild(), currentSize);
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
