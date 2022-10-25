#pragma once

#include <malloc.h>
#include <stdbool.h>

typedef char T;

//二叉树节点定义
typedef struct BinaryTreeNode {
    T element;//权重值
    struct BinaryTreeNode *leftChild;//左孩子指针
    struct BinaryTreeNode *rightChild;//右孩子指针
} TreeNode, *NodePointer;

//默认初始化初始化二叉树节点
NodePointer newTreeNode() {
    NodePointer newNode = (NodePointer) malloc(sizeof(TreeNode));
    newNode->rightChild = newNode->leftChild = NULL;//将左右孩子默认置空
    newNode->element = '#';//数据域默认置为#
    return newNode;
}

//初始化一个叶子节点，叶子节点的两个左右孩子都是权值为#的空节点
NodePointer newLeafNode(const T theElement) {
    NodePointer newNode = (NodePointer) malloc(sizeof(TreeNode));
    newNode->element = theElement;
    newNode->rightChild = newTreeNode();
    newNode->leftChild = newTreeNode();
    return newNode;
}

//建立二叉链表存储的二叉树
typedef struct BinaryTree {
    NodePointer root;//树的根节点
} BinaryTree, *TreePointer;

//初始化一颗空树
TreePointer newEmptyTree() {
    TreePointer newTree = (TreePointer) malloc(sizeof(BinaryTree));
    newTree->root = NULL;
    return newTree;
}

//判断树是否为空
bool emptyTree(TreePointer p) {
    return p->root == NULL;
}

T *preOrderGlobalArray;//全局的表示先序序列的数组，作用是保存main函数中用户输入的先序序列，初始化二叉树的函数需要根据该数组来构建二叉树
//初始化全局的先序序列的数组
void initializeTreeArray(const T thePreOrderArray[], int arraySize) {
    preOrderGlobalArray = (T *) malloc(arraySize * sizeof(T));
    for (int i = 0; i < arraySize; i++) {
        preOrderGlobalArray[i] = thePreOrderArray[i];
    }
}

//创建一颗树的递归函数
NodePointer create_preOrder(NodePointer p) {
    static int i = -1;
    i++;
    p = newTreeNode();
    if (preOrderGlobalArray[i] == '#') {
        p->element = '#';
        p->leftChild = NULL;
        p->rightChild = NULL;
    } else {
        p->element = preOrderGlobalArray[i];
        p->leftChild = create_preOrder(p->leftChild);
        p->rightChild = create_preOrder(p->rightChild);
    }
    return p;
}

/*初始化一颗非空的二叉树，此函数需要根据全局的一段扩展的先序遍历的序列preOrderGlobalArray
 * （用数组表示，空子树由'#'表示），在调用此函数之前先调用initializeTreeArray初始化全局的
 * 数组preOrderArray*/
TreePointer newTree() {
    TreePointer theNewTree = (TreePointer) malloc(sizeof(BinaryTree));
    theNewTree->root = create_preOrder(theNewTree->root);
    return theNewTree;
}

//以下是遍历过程中可以执行的代表具体操作的函数，可以将其下的函数地址传递给函数指针

void outputNode(NodePointer p) {
    printf("%c", p->element);
}

//定义一个全局的函数指针，在遍历二叉树的过程中，可执行的具体操作随具体情况而定，这个函数指针指向具体要执行操作的函数
void (*processFunction)(NodePointer theNode);//全局函数指针

//以下是直接使用函数指针来调用相应的函数完成相关操作的三种递归函数

void preOrder(NodePointer p) {
    if (p == NULL)return;
    processFunction(p);
    preOrder(p->leftChild);
    preOrder(p->rightChild);
}

void inOrder(NodePointer p) {
    if (p == NULL)return;
    inOrder(p->leftChild);
    processFunction(p);
    inOrder(p->rightChild);
}

void postOrder(NodePointer p) {
    if (p == NULL)return;
    postOrder(p->leftChild);
    postOrder(p->rightChild);
    processFunction(p);
}

//以下三个函数即可传入相关函数的函数地址，并传入树的根节点，然后调用相关遍历函数完成相关操作
void preOrder_func(void (*funcPointer)(NodePointer), NodePointer p) {
    processFunction = funcPointer;
    preOrder(p);
}

void postOrder_func(void (*funcPointer)(NodePointer), NodePointer p) {
    processFunction = funcPointer;
    postOrder(p);
}

void inOrder_func(void (*funcPointer)(NodePointer), NodePointer p) {
    processFunction = funcPointer;
    inOrder(p);
}

//销毁一颗二叉树的递归函数，由void deleteTree(TreePointer theTree)调用
void deleteNode(NodePointer pointer) {
    if (pointer->leftChild)
        deleteNode(pointer->leftChild);
    if (pointer->rightChild)
        deleteNode(pointer->rightChild);
    free(pointer);
}

//实现销毁一颗二叉树，释放其中所有节点，在main函数中调用
void deleteTree(TreePointer theTree) {
    deleteNode(theTree->root);
    free(preOrderGlobalArray);//释放全局数组
    printf("\n已释放所有节点以及全局数组\n");
}


//实现求二叉树的高度的递归函数，仅由getTreeHeight调用
int treeHeight(NodePointer p) {
    int leftHeight, rightHeight;
    if (p->element == '#')
        return 0;
    else {
        leftHeight = treeHeight(p->leftChild);
        rightHeight = treeHeight(p->rightChild);
        return ((leftHeight > rightHeight) ? leftHeight : rightHeight) + 1;
    }
}

//求二叉树高度的函数，在main函数中调用
int getTreeHeight(TreePointer p) {
    if (p == NULL)return 0;
    else return treeHeight(p->root);
}

//求二叉树深度的递归函数，仅由int getDepth(TreePointer p, NodePointer targetNode)调用
void depthCount(NodePointer p, NodePointer targetNode, int *theDepth) {
    static int level = -1;
    level++;
    if (p != NULL) {
        if (p == targetNode) {
            *theDepth = level;
            return;
        } else {
            depthCount(p->leftChild, targetNode, theDepth);
            depthCount(p->rightChild, targetNode, theDepth);
            level--;
        }
    } else {
        level--;
    }
}

//实现求二叉树中任意节点的深度，在main函数中调用
int getDepth(TreePointer p, NodePointer targetNode) {
    int *deep = (int *) malloc(sizeof(int));
    depthCount(p->root, targetNode, deep);
    int result = *deep;
    free(deep);
    return result;
}

//不使用非输出型参数计算任意节点的深度的递归函数
int countDepth2(NodePointer currentNode, NodePointer targetNode) {
    static int depth = -1;
    static bool hasFound = false;
    depth++;
    if (currentNode == NULL) {
        depth--;
        return depth;
    } else {
        if (currentNode== targetNode) {
            hasFound = true;
            return depth;
        }
        if (!hasFound)
            depth = countDepth2(currentNode->leftChild, targetNode);
        if (!hasFound)
            depth = countDepth2(currentNode->rightChild, targetNode);
        if(!hasFound)
          depth--;
        return depth;
    }
}

//不使用非输出型参数计算任意节点的深度的函数，在main函数中调用
int getDepth2(TreePointer pointer, NodePointer theNode) {
    int theResult = countDepth2(pointer->root, theNode);
    return theResult;
}

//求节点双亲的递归函数，仅由NodePointer getParent(TreePointer treePointer, NodePointer target)调用
NodePointer findParent(NodePointer currentNode, NodePointer target) {
    NodePointer p;
    if (currentNode == NULL)return NULL;
    else if (currentNode->leftChild == target || currentNode->rightChild == target)
        return currentNode;//找到了target的双亲
    else {
        //未找到target的双亲
        p = findParent(currentNode->leftChild, target);//在左子树中寻找
        if (p != NULL)
            return p;//在左子树中找到了，直接返回
        else return findParent(currentNode->rightChild, target);//在右子树中递归查找
    }
}

//实现求指定节点的双亲，在main函数中调用
NodePointer getParent(TreePointer treePointer, NodePointer target) {
    if (treePointer->root == NULL || target == NULL)return NULL;
    return findParent(treePointer->root, target);
}

//根据指定节点的权值求其双亲节点的地址，仅由NodePointer getParentByValue(TreePointer pointer, T theElement)调用
NodePointer findParentByValue(NodePointer currentNode, T theElement) {
    NodePointer p = NULL;
    if (currentNode == NULL)
        return NULL;
    if (currentNode->leftChild != NULL) {
        if (currentNode->leftChild->element == theElement) {
            return currentNode;
        }
    }
    if (currentNode->rightChild != NULL) {
        if (currentNode->rightChild->element == theElement) {
            return currentNode;
        }
    }
    p = findParentByValue(currentNode->leftChild, theElement);
    if (p != NULL)
        return p;
    else
       p= findParentByValue(currentNode->rightChild, theElement);
    if(p!=NULL)
        return p;
    else return NULL;
}

//通过指定节点的地址查找节点的双亲，在main函数中调用
NodePointer getParentByValue(TreePointer pointer, T theElement) {
    if (pointer->root == NULL)return NULL;
    return findParentByValue(pointer->root, theElement);
}

//统计叶子数目的递归函数，仅由int getLeafSize(TreePointer treePointer)调用
int countLeafSize(NodePointer pointer) {
    int leftLeaf = 0, rightLeaf = 0;
    if (pointer->leftChild->element == '#' && pointer->rightChild->element == '#')
        return 1;
    leftLeaf = countLeafSize(pointer->leftChild);
    rightLeaf = countLeafSize(pointer->rightChild);
    return leftLeaf + rightLeaf;
}

//实现求叶子节点的数目，在main函数中调用
int getLeafSize(TreePointer treePointer) {
    if (treePointer == NULL) {
        return 0;
    } else {
        return countLeafSize(treePointer->root);
    }
}

/*实现求所有节点的数目的递归函数，仅由int getTreeSize(TreePointer pointer)调用
 * NodePointer pointer：树的节点的指针
 * int *currentSize：输出型参数，统计节点的数量，每到一个节点就+1*/
void countTreeSize(NodePointer pointer, int *currentSize) {
    if (pointer == NULL)return;
    if (pointer->element != '#')
        (*currentSize)++;
    countTreeSize(pointer->leftChild, currentSize);
    countTreeSize(pointer->rightChild, currentSize);
}

/*实现求二叉树的所有节点的数量
 * TreePointer pointer：树的指针*/
int getTreeSize(TreePointer pointer) {
    int *size = (int *) malloc(sizeof(int));
    *size = 0;
    countTreeSize(pointer->root, size);
    int result = *size;
    free(size);
    return result;
}

/*根据传入的值找到二叉树中指定的节点，返回节点的地址，仅由NodePointer getTreeNode(TreePointer pointer, T theElement)调用
 * NodePointer p: 树的节点的地址
 * T theElement: 要查找节点的权值*/
NodePointer findTreeNode(NodePointer p, T theElement) {
    if (p == NULL)
        return NULL;
    else {
        if (p->element == theElement)
            return p;
        else {
            NodePointer temp;
            temp = findTreeNode(p->leftChild, theElement);
            if (temp == NULL)
                return findTreeNode(p->rightChild, theElement);
            return temp;
        }
    }
}

/*实现查找指定节点，传入该节点的权值，如果该权值不存在则返回NULL，存在则返回该节点的地址，在main函数中调用此函数
 TreePointer pointer: 树的指针
 T theElement: 要查找节点的权值*/
NodePointer getTreeNode(TreePointer pointer, T theElement) {
    if (pointer == NULL)return NULL;
    return findTreeNode(pointer->root, theElement);
}

/*在某叶子节点之后插入一个新节点,bool rightOrLeft指定要将该节点插入到左孩子还是右孩子，如果无法插入会输出错误信息
 TreePointer pointer:树的指针
 const T theElement:节点插入到树之后，该节点的双亲的权值
 const T theInsertElement:要插入的节点的权值
 bool rightOrLeft:要插入到左孩子还是有孩子，为true时为左孩子，为false时为右孩子
 */
void insertTreeNode(TreePointer pointer, const T theElement, const T theInsertElement, bool rightOrLeft) {
    //先以值的方式查找想要查找的节点存不存在
    NodePointer theNode = getTreeNode(pointer, theElement);
    if (theNode != NULL) {
        //判断该节点是不是叶子节点，如果是则可以插入，如果不是则不能插入
        if (theNode->rightChild->element == '#' && theNode->leftChild->element == '#') {
            //该节点是叶子节点
            if (rightOrLeft) {
                //将新节点插在左孩子上
                theNode->leftChild = newLeafNode(theInsertElement);
            } else {
                //将新节点插在右孩子上
                theNode->rightChild = newLeafNode(theInsertElement);
            }
            printf("\n插入成功\n");
        } else {
            printf("\n该节点不是叶子节点，无法插入指定的节点\n");
        }
    } else {
        printf("\n找不到指定的叶子节点\n");
    }
}