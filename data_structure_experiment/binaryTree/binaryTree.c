#include <stdio.h>
#include "binaryTree.h"

int main() {
    setbuf(stdout, NULL);//在调试时使得输出语句可以将数据打印在控制台上

    //测试建立二叉树，并按三种遍历顺序遍历输出二叉树中所有节点的值
    char treeArray[] = {'A','B','D','#','#','E','#','#','C','G','#','#','H','#','#'};
    initializeTreeArray(treeArray, sizeof(treeArray) / sizeof(treeArray[0]));
    TreePointer theTree = newTree();
    printf("按前序遍历输出二叉树：");
    preOrder_func(theTree,outputNode);//按前序输出
    printf("\n按中序遍历输出二叉树：");
    inOrder_func(theTree,outputNode);//按中序输出
    printf("\n按后序遍历输出二叉树：");
    postOrder_func(theTree,outputNode);//按后序输出
    //输出树中所有节点的数量
    int treeSize = getTreeSize(theTree);
    printf("\n输出二叉树中的所有节点的数目：%d", treeSize);
    //输出树中所有叶子节点的数量
    int leafSize = getLeafSize(theTree);
    printf("\n输出二叉树中所有叶子节点的个数：%d", leafSize);
    //输出树的高度
    int theTreeHeight = getTreeHeight(theTree);
    printf("\n输出二叉树的总高度：%d\n", theTreeHeight);


    //测试查找指定节点
    printf("\n测试查找指定的节点，输入要查找的节点的值：");
    char findNode;
    scanf("%c", &findNode);
    getchar();
    NodePointer theNode = getTreeNode(theTree, findNode);
    if (theNode != NULL&&theNode->element==findNode) {
        printf("找到了指定节点\n");
    } else printf("未找到指定节点\n\n");


    //求指定节点的双亲
    printf("测试查找指定节点的双亲，输入要查找双亲的节点的值：");
    char targetChar;
    scanf("%c", &targetChar);
    getchar();
    NodePointer theParent = getParentByValue(theTree, targetChar);
    if (theParent != NULL&&(theParent->leftChild->element == targetChar || theParent->rightChild->element == targetChar))
        printf("找到了该节点的双亲，该节点的双亲的权值是：%c\n", theParent->element);
    else printf("未找到该节点，所以没有找到该节点的双亲\n\n");

    //测试二叉树求任意节点深度
    printf("使用带有输出型参数求二叉树求任意节点的深度，输入要求节点深度的节点权值：");
    char depthNode;
    scanf("%c", &depthNode);
    getchar();
    NodePointer theDepthNode = getTreeNode(theTree, depthNode);
    if (theDepthNode != NULL&&theDepthNode->element==depthNode) {
        int theDepth = getDepth(theTree, theDepthNode);
        printf("该节点的深度是：%d\n", theDepth);
    } else printf("你输入的节点未找到，无法求得深度\n\n");

    //测试二叉树求任意节点高度，求出树的总高度，再求出该节点的深度，用树的高度减去该节点的深度即为该节点的高度
    printf("测试二叉树求任意节点的高度，输入要求节点高度的节点权值：");
    char heightNode;
    scanf("%c", &heightNode);
    getchar();
    NodePointer theHeightNode = getTreeNode(theTree, heightNode);
    if (theHeightNode != NULL&&theHeightNode->element == heightNode) {
        int height = getTreeHeight(theTree) - getDepth(theTree, theHeightNode);//树的总高度-该节点的深度=该节点的高度
        printf("该节点的高度=%d\n", height);
    } else printf("你输入的节点未找到，无法求得高度\n\n");

    //测试在叶子节点之后插入新节点
    printf("测试在二叉树的叶子节点上插入新节点，节点要成为到哪个节点的左孩子或右孩子，请输入该叶子节点的权值：");
    char theInsertedNode;
    scanf("%c", &theInsertedNode);
    getchar();
    NodePointer theLeafNode= getTreeNode(theTree,theInsertedNode);
    if(theLeafNode==NULL||theLeafNode->element!=theInsertedNode)
        printf("你输入的叶子节点不存在，无法执行插入操作");
    else{
        printf("\n请输入你要插入节点的权值：");
        char theInsertNode;
        scanf("%c", &theInsertNode);
        getchar();
        printf("\n你要将节点插入到左孩子还是右孩子上（左孩子输入y，右孩子输入n）：");
        char rightOrLeftChar;
        bool rightOrLeft;
        scanf("%c", &rightOrLeftChar);
        getchar();
        if (rightOrLeftChar == 'y')
            rightOrLeft = true;
        else rightOrLeft = false;
        insertTreeNode(theTree,theInsertedNode,theInsertNode,rightOrLeft);
        printf("输出插入节点之后的二叉树前序遍历序列：");
        preOrder_func(outputNode,theTree->root);
    }

    //用不带输出型参数的函数求得指定节点的深度
    printf("\n使用不带输出型参数的函数求任意节点的深度，输入要求节点的权值：");
    char theDepthNode2;
    scanf("%c", &theDepthNode2);
    getchar();
    NodePointer depthNode2 = getTreeNode(theTree, theDepthNode2);
    if (depthNode2 != NULL&&depthNode2->element == theDepthNode2) {
        int result = getDepth2(theTree, depthNode2);
        printf("\n你要查找的节点的深度=%d", result);
    } else{
        printf("\n没有找到你要查找的节点，无法求得深度");
    }

    //测试销毁二叉树，释放其中所有节点
    deleteTree(theTree);
    return 0;
}