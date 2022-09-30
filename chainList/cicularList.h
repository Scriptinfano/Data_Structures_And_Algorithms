#pragma once
#include <stdio.h>
#include <malloc.h>

typedef int DataType;//���巺������

//��������ڵ�
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

//����ѭ������
typedef struct CircularListWithHead {
    NodePointer nodeHeader;//ָ��ͷ�ڵ��ָ��
    NodePointer nodeBack;//ָ��β�ڵ��ָ��
    int listSize;//����Ľڵ����
} circularList;
typedef circularList *CircularPointer;

//�ͷ�������ռ�����пռ�
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
//��ʼ������
CircularPointer initializeList() {
    CircularPointer p = (CircularPointer) malloc(sizeof(circularList));
    p->listSize = 0;
    p->nodeHeader = initializeNode_default(p->nodeHeader);
    p->nodeBack = p->nodeHeader;
}

//���������еĽڵ���Ŀ
int getSizeOfList(CircularPointer p) {
    return p->listSize;
}

//�ڱ�ͷ�����½ڵ�
int addNode_front(CircularPointer p, DataType element) {
    NodePointer newNode = initializeNode(element, p->nodeHeader->next);
    p->nodeHeader->next = newNode;
    if (p->listSize == 0)p->nodeBack = newNode;
    p->listSize++;
    return 1;
}

//�ڱ�β�����½ڵ�
void addNode_back(CircularPointer p, DataType element) {
    p->nodeBack->next = initializeNode(element, p->nodeHeader);
    p->listSize++;
    p->nodeBack = p->nodeBack->next;
}

//�ж������Ƿ�Ϊ��
int isEmpty(CircularPointer p) {
    return p->listSize == 0 && p->nodeHeader == p->nodeBack;
}

//�ڵ�index���ڵ�֮������½ڵ㡣������-1����˵����������
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

//ɾ����index���ڵ㣬������0��˵������Ϊ�գ��޷�ִ��ɾ������;������-1����˵������index����;����1��˵�������ɹ�
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

//ȡ�õ�index���ڵ�����ݡ�������-1��˵������index����;����1����˵�������ɹ�
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
//������������е����ݡ�������0��������Ϊ�գ��޷������������
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
            printf("����Ϊ�գ��޷�ִ����ز���\n");
            break;
        case -1:
            printf("index���������޷�ִ����ز���\n");
            break;
    }
}
