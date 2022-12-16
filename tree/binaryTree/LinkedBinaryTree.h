#pragma once

#include "BinaryTreeNode.h"
#include "processFuncSpace.h"
#include <iostream>
#include <queue>
#include <stack>
#include <vector>

using namespace std;
using namespace ProcessTreeNodeFuncSpace;

//用链表实现的二叉树，可线索化
template<class T>
class LinkedBinaryTree {
    using TreeNode = BinaryTreeNode<T>;
    using NodePointer = BinaryTreeNode<T> *;

private://私有成员变量
    NodePointer root;//树的根节点
    int treeSize;//树的节点个数
    bool hasThread;//指示是否经过线索化
    vector<char> orderVec;
public:

    //返回根节点地址
    NodePointer getRoot() const {
        return root;
    }


public:

    //传入一个代表前序序列的遍历结果的数组，根据数组来构造二叉树
    explicit LinkedBinaryTree(const vector<char> &theOrderVec) {
        hasThread = false;
        treeSize = 0;
        orderVec = theOrderVec;
        root = initiate_preOrder(root);
    }

private:

    //TODO 测试创建二叉树的代码，判断是否需要对遍历序号i作出限制

    //根据前序遍历序列创建二叉树的递归函数
    NodePointer initiate_preOrder(NodePointer p) {
        static int i = -1;
        i++;
        p = new TreeNode();//先默认初始化节点
        if (orderVec[i] == '#') {
            p->setElement('#');
            p->setLeftChild(nullptr);
            p->setRightChild(nullptr);
        } else {
            treeSize++;
            p->setElement(orderVec[i]);
            p->setLeftChild(initiate_preOrder(p->getLeftChild_nonConst()));
            p->setRightChild(initiate_preOrder(p->getRightChild_nonConst()));
        }
        return p;
    }

    T transformToT(const char &theChar) {
        return (T) theChar;
    }

public:
    //析构函数，释放二叉树中所有节点
    ~LinkedBinaryTree() {
        deleteTreeNode(root);
        cout << "已经释放了二叉树中所有的节点" << endl;
    }

private:

    //被析构函数调用
    void deleteTreeNode(NodePointer pointer) {
        if (pointer->getLeftChild())
            deleteTreeNode(pointer->getLeftChild());
        if (pointer->getRightChild())
            deleteTreeNode(pointer->getRightChild());
        delete pointer;
    }


public:

    //判断二叉树是否为空
    bool empty() const {
        return treeSize == 0 && root == nullptr;
    }

    //直接返回内部统计树节点变量
    int size() const {
        return treeSize;
    }

    //二叉树遍历的非递归实现，每个函数返回遍历的结果

    //前序遍历的非递归实现，将遍历的节点的权值存储在一个vector容器中并返回该容器
    vector<int> preOrder_noRecursion() {
        stack<NodePointer> nodeStack;
        vector<T> result;//存放遍历的结果
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

private:

    void levelOrder(NodePointer theNode) {
        std::queue<NodePointer> pointerQueue;
        while (theNode != nullptr) {
            cout << theNode->getElement() << " ";
            if (theNode->getLeftChild() != nullptr)
                pointerQueue.push(theNode->getLeftChild());
            if (theNode->getRightChild() != nullptr)
                pointerQueue.push(theNode->getRightChild());
            if (pointerQueue.empty()) return;
            else theNode = pointerQueue.front();
            pointerQueue.pop();
        }
    }

public:
    //调用层次遍历输出二叉树中的每一个节点
    void output_levelOrder() {
        if (empty())
            return;
        else {
            levelOrder(root);
            cout << endl;
        }
    }



    //////////////////////////二叉树功能性代码，例如输出二叉树的遍历序列，在叶子节点之后插入节点，求高度，深度，双亲，节点总数，叶子节点数等/////////////////////

public:
    //在叶子节点之后插入节点
    void insertTReeNode(T theElement, T theInsertElement, bool leftOrRight) {
        NodePointer theNode = getTreeNode(theElement);
        if (theNode != nullptr) {
            if (theNode->getRightChild()->getElement() == '#' && theNode->getLeftChild()->getElement() == '#') {
                if (leftOrRight)
                    theNode->setLeftChild(new BinaryTreeNode('#'));
                else
                    theNode->setRightChild(new BinaryTreeNode('#'));
                cout << "插入成功" << endl;
            } else
                cout << "该节点不是叶子节点，无法插入指定的节点" << endl;
        } else
            cout << "找不到指定的节点" << endl;
    }

private:
    void outputNode_preOrder(NodePointer pointer) {
        if (pointer == nullptr)
            return;
        cout << pointer->getElement();
        outputNode_preOrder(pointer->getLeftChild_nonConst());
        outputNode_preOrder(pointer->getRightChild_nonConst());
    }


public:

    void output_preOrder() {
        outputNode_preOrder(root);
        cout << endl;
    }

public:
    //使用递归的方式计算叶子节点的个数
    int getLeafSize() {
        int leftLeaf = 0, rightLeaf = 0;
        if (root == nullptr)return 0;
        if (root->getLeftChild() == nullptr && root->getRightChild() == nullptr)return 1;
        leftLeaf = getLeafSize(root->getLeftChild());
        rightLeaf = getLeafSize(root->getRightChild());
        return leftLeaf + rightLeaf;
    }

private:
    //求二叉树高度，二叉树的高度是树中任意一个节点到叶子节点的距离，求二叉树高度需要使用后序遍历
    int treeHeight(NodePointer p) {
        if (p->getElement() == '#')
            return 0;//返回的其实是p所指向的子节点的高度，只不过此时p是null且指向了叶子节点，因为叶子节点没有子节点所以应该返回0
        else {
            //求二叉树的高度采用后序遍历
            int leftHigh = treeHeight(p->getLeftChild());//遍历左
            int rightHigh = treeHeight(p->getRightChild());//遍历右
            int high = (leftHigh > rightHigh ? leftHigh : rightHigh) + 1;//树高度应为其左右子树高度的较大值加1
            return high;
            //上面四行代码可以合并成一行：return 1+max(getHeight(p->getLeftChild()),treeHeight(p->getRightChild()));
        }
    }

public:
    int getTreeHeight() {
        if (empty())
            return 0;
        else return treeHeight(root);
    }

private:
    void treeDepth(const NodePointer pointer, NodePointer targetNode, int &theDepth) {
        static int level = -1;
        level++;
        if (pointer != nullptr) {
            if (pointer == targetNode) {
                theDepth = level;
                return;
            } else {
                treeDepth(pointer->getLeftChild(), targetNode, theDepth);
                treeDepth(pointer->getRightChild(), targetNode, theDepth);
                level--;
            }
        } else level--;
    }

    int treeDepth2(NodePointer pointer, NodePointer targetNode) {
        static int depth = -1;
        static bool hasFound = false;
        depth++;
        if (pointer == nullptr) {
            depth--;
            return depth;
        } else {
            if (pointer == targetNode) {
                hasFound = true;
                return depth;
            }
            if (!hasFound)
                depth = treeDepth2(pointer->getLeftChild_nonConst(), targetNode);
            if (!hasFound)
                depth = treeDepth2(pointer->getRightChild_nonConst(), targetNode);
            if (!hasFound)
                depth--;
            return depth;
        }
    }

public:
    int getTreeDepth(NodePointer targetNode) {
        int deep = 0;
        treeDepth(root, targetNode, deep);
        return deep;
    }

    int getTreeDepth2(NodePointer targetNode) {
        return treeDepth2(root, targetNode);
    }

private:
    NodePointer treeNodeParent(NodePointer pointer, NodePointer targetNode) {
        if (pointer == nullptr)
            return nullptr;
        else if (pointer->getLeftChild() == targetNode || pointer->getRightChild() == targetNode)
            return pointer;
        else {
            NodePointer p = treeNodeParent(pointer->getLeftChild_nonConst(), targetNode);
            if (p != nullptr)
                return p;
            else return treeNodeParent(pointer->getRightChild_nonConst(), targetNode);
        }
    }

    NodePointer treeNodeParentByValue(NodePointer currentNode, T theElement) {
        NodePointer p = nullptr;
        if (currentNode == nullptr)
            return nullptr;
        if (currentNode->getLeftChild() != nullptr) {
            if (currentNode->getLeftChild_nonConst()->getElement() == theElement)
                return currentNode;
        }
        if (currentNode->getRightChild() != nullptr) {
            if (currentNode->getRightChild()->getElement() == theElement)
                return currentNode;
        }
        p = treeNodeParentByValue(currentNode->getLeftChild_nonConst(), theElement);
        if (p != nullptr)
            return p;
        else
            p = treeNodeParentByValue(currentNode->getRightChild_nonConst(), theElement);
        if (p != nullptr)
            return p;
        else return nullptr;
    }

public:
    NodePointer getTreeParent(NodePointer targetNode) {
        if (empty())return nullptr;
        return treeNodeParent(root, targetNode);
    }

    NodePointer getTreeParentByValue(T theElement) {
        if (empty())return nullptr;
        return treeNodeParentByValue(root, theElement);
    }

private:
    int countLeafSize(NodePointer pointer) {
        int leftLeafSize = 0, rightLeafSize = 0;
        if (pointer->getLeftChild()->getElement() == '#' && pointer->getRightChild()->getElement() == '#')
            return 1;
        leftLeafSize = countLeafSize(pointer->getLeftChild_nonConst());
        rightLeafSize = countLeafSize(pointer->getRightChild_nonConst());
        return leftLeafSize + rightLeafSize;
    }

public:
    int getTreeLeafSize() {
        if (empty())return 0;
        else return countLeafSize(root);
    }

private:

    void countTreeSize(NodePointer pointer, int &currentSize) {

        if (pointer == nullptr)
            return;
        if (pointer->getElement() != '#')
            currentSize++;
        countTreeSize(pointer->getLeftChild_nonConst(), currentSize);
        countTreeSize(pointer->getRightChild_nonConst(), currentSize);
    }

public:
    //用算法统计二叉树中的节点个数
    int getTreeSize() {
        int size = 0;
        countTreeSize(root, size);
        return size;
    }

private:
    NodePointer findTreeNode(NodePointer pointer, T theElement) {
        if (pointer == nullptr)
            return nullptr;
        else {
            if (pointer->getElement() == theElement)
                return pointer;
            else {
                NodePointer temp = findTreeNode(pointer->getLeftChild_nonConst(), theElement);
                if (temp != nullptr)
                    return findTreeNode(pointer->getRightChild_nonConst(), theElement);
                return temp;
            }
        }
    }

public:
    NodePointer getTreeNode(T theElement) {
        if (empty())
            return nullptr;
        return findTreeNode(root, theElement);
    }

    //TODO 求左右孩子


    //////////////////////线索化与哈夫曼树的构建///////////////////////
//TODO 测试哈夫曼树的实现与线索化

private:
    //线索化二叉树的递归函数（属于内部实现），此处采用中序遍历线索化二叉树
    void inThread(NodePointer p, NodePointer pre) {
        //首次在外部调用该递归函数时，p不会是nullptr，该递归出口即p==nullptr

        //该递归函数返回的条件即是p==nullptr
        if (p != nullptr) {
            inThread(p->getLeftChild_nonConst(), pre);//中序遍历中的左遍历

            //////////////中序遍历的处理流程如下//////////////////
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
            /////////////////////////////////////////////////

            inThread(p->getRightChild(), pre);//中序遍历的右遍历，继续递归线索化右子树
        }

    }

public:
    //对二叉树进行线索化，从根节点开始对二叉树线索化
    void cueing() {
        //第一个遍历的节点的左孩子为空，最后一个遍历的节点的右孩子为空

        NodePointer pre = nullptr;//总是指向正在遍历的节点的前驱节点
        if (!empty()) {
            //二叉树不为空
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
            cout << "二叉树为空，无法线索化" << endl;
        }
    }

private:
    //服务于线索化输出的两个私有函数

    //在中序线索二叉树上求中序遍历的第一个节点
    NodePointer firstNode(NodePointer pointer) {
        //找到最左下的节点
        while (!pointer->isLeftTag()) {
            pointer = pointer->getLeftChild_nonConst();
        }
        return pointer;
    }

    //在中序线索二叉树上求节点p在中序序列中的后继节点
    NodePointer nextNode(NodePointer pointer) {
        if (!pointer->isRightTag())
            return firstNode(pointer->getRightChild_nonConst());
        else return pointer->getRightChild_nonConst();
    }

public:

    //线索化之后，线索二叉树的遍历输出
    void outputThreadTree() {
        for (NodePointer p = firstNode(root); p != nullptr; p = nextNode(p))
            cout << p->getElement() << " ";
        cout << endl;
    }

private:
    //找到parent为nullptr的最小和次小的两个节点，由createHuffmanTree调用
    void findMin(HuffmanTreeNode<T> *theArray[], const int &p, int &minChild, int &secondMinChild) {
        int temp;
        minChild = theArray[0]->getElement();
        secondMinChild = theArray[0]->getElement();
        for (int i = 0; i < p; i++) {
            if (theArray[i]->getParent() == nullptr) {
                temp = theArray[i]->getElement();
                if (temp < secondMinChild) {
                    if (temp > minChild) {
                        secondMinChild = temp;
                    } else {
                        minChild = secondMinChild;
                        secondMinChild = temp;
                    }
                }
            }
        }

    }

    //通过前序遍历，将每个叶子节点放入vector容器
    void getLeafVec_preOrder(NodePointer p, vector<T> &leafVec) {
        if (p != nullptr) {
            if (p->getRightChild() == nullptr && p->getLeftChild() == nullptr)
                leafVec.push_back(p->getElement());
            getLeafVec_preOrder(p->getLeftChild());
            getLeafVec_preOrder(p->getRightChild());
        }
    }

public:
    //返回用该二叉树叶子节点所创建的哈夫曼树
    HuffmanTreeNode<T> **createHuffmanTree() {
        vector<T> theLeafVec;//存储叶子节点的容器
        getLeafVec_preOrder(root, theLeafVec);//将所有叶子节点的权值放入vec容器
        int leafSize = getLeafSize();
        int huffmanArraySize = 2 * leafSize - 1;//最终构建的哈夫曼树的叶子节点数组，一共有2*n-1个
        HuffmanTreeNode<T> **huffmanArray = new HuffmanTreeNode<T> *[huffmanArraySize];
        //初始化前n个节点的权值
        for (int i = 0; i < leafSize; i++) {
            huffmanArray[i] = new HuffmanTreeNode(theLeafVec.at(i));
        }
        for (int i = leafSize; i < huffmanArraySize; i++) {
            huffmanArray[i] = new HuffmanTreeNode<T>;
            //找到parent为nullptr的最小和次小的两个节点
            int minChild, secondMinChild;//存储最小和次小的节点在数组中的编号
            findMin(huffmanArray, i, minChild, secondMinChild);
            huffmanArray[i]->setElement(huffmanArray[minChild]->getElement() + huffmanArray[secondMinChild]->getElement());
            huffmanArray[minChild]->setParent(huffmanArray[i]);
            huffmanArray[secondMinChild]->setParent(huffmanArray[i]);
            huffmanArray[i]->setLeftChild(huffmanArray[minChild]);
            huffmanArray[i]->setRightChild(huffmanArray[secondMinChild]);
        }
        return huffmanArray;
    }

};

