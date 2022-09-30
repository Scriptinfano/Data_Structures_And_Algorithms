#pragma once
#include <stdio.h>
#include <malloc.h>

typedef int DataType;//定义泛型数据

//定义链表节点
typedef struct ChainNode {
    DataType element;
    struct ChainNode *next;
} Node;
typedef Node *NodePointer;

NodePointer initializeNode(DataType element, NodePointer next) {
    NodePointer p = (NodePointer) malloc(sizeof(Node));
    p->next = next;
    p->element = element;
    return p;
}

NodePointer initializeNode_default(NodePointer next) {
    NodePointer p = (NodePointer) malloc(sizeof(Node));
    p->next = next;
    return p;
}

//定义循环链表
typedef struct CircularListWithHead {
    NodePointer nodeHeader;//指向头节点的指针
    NodePointer nodeBack;//指向尾节点的指针
    int listSize;//链表的节点个数
} circularList;
typedef circularList *CircularPointer;

//释放链表所占的所有空间
void freeList(CircularPointer p){
    NodePointer j=p->nodeHeader->next;
    NodePointer deleteNode=j;
    while(j!=p->nodeHeader){
        j=j->next;
        free(deleteNode);
        deleteNode=j;
    }
    free(j);
    free(p);
}
//初始化链表
CircularPointer initializeList() {
    CircularPointer p = (CircularPointer) malloc(sizeof(circularList));
    p->listSize = 0;
    p->nodeHeader = initializeNode_default(p->nodeHeader);
    p->nodeBack = p->nodeHeader;
}

//返回链表中的节点数目
int getSizeOfList(CircularPointer p) {
    return p->listSize;
}

//在表头插入新节点
int addNode_front(CircularPointer p, DataType element) {
    NodePointer newNode = initializeNode(element, p->nodeHeader->next);
    p->nodeHeader->next = newNode;
    if (p->listSize == 0)p->nodeBack = newNode;
    p->listSize++;
    return 1;
}

//在表尾插入新节点
void addNode_back(CircularPointer p, DataType element) {
    p->nodeBack->next = initializeNode(element, p->nodeHeader);
    p->listSize++;
    p->nodeBack = p->nodeBack->next;
}

//判断链表是否为空
int isEmpty(CircularPointer p) {
    return p->listSize == 0 && p->nodeHeader == p->nodeBack;
}

//在第index个节点之后插入新节点。若返回-1，则说明参数错误
int insertNode(CircularPointer p, int index, DataType element) {
    if (index > p->listSize)return -1;
    if (index == p->listSize) {
        addNode_back(p, element);
        return 1;
    }
    NodePointer j = p->nodeHeader;
    for (int i = 0; i < index; i++) {
        j = j->next;
    }
    NodePointer newNode = initializeNode(element, j->next);
    j->next = newNode;
    p->listSize++;
}

//删除第index个节点，若返回0则说明链表为空，无法执行删除操作;若返回-1，则说明参数index错误;返回1则说明操作成功
int deleteNode(CircularPointer p, int index) {
    if (isEmpty(p))return 0;
    if (index > p->listSize)return -1;
    NodePointer j = p->nodeHeader;
    for (int i = 0; i < index - 1; i++) {
        j = j->next;
    }
    NodePointer deleteNode = j->next;
    j->next = j->next->next;
    free(deleteNode);
    p->listSize--;
    return 1;
}

//取得第index个节点的数据。若返回-1，说明参数index错误;返回1，则说明操作成功
int getNodeElement(CircularPointer p, int index, DataType *data) {
    if (index > p->listSize) {
        return -1;
    }
    NodePointer j = p->nodeHeader;
    for (int i = 0; i < index; i++) {
        j = j->next;
    }
    *data= j->element;
    return 1;
}
//输出链表中所有的数据。若返回0，则链表为空，无法输出链表内容
int outPutList(CircularPointer p){
    if(p->listSize==0){
        return 0;
    }
    NodePointer j = p->nodeHeader->next;
    while (j!=p->nodeHeader) {
        printf("%d ",j->element);
        j = j->next;
    }
    printf("\n");
}

void processErr(int errCode){
    switch(errCode){
        case 0:
            printf("链表为空，无法执行相关操作\n");
            break;
        case -1:
            printf("index参数错误，无法执行相关操作\n");
            break;
    }
}
