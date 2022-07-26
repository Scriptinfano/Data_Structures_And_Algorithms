#pragma once

#include <malloc.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
typedef int KeyType;
typedef char *InfoType;
typedef struct HashNode {
    KeyType key;//关键字域
    InfoType info;//数据域
    struct HashNode *next;//哈希表采用链地址法解决冲突，所以存放数据的节点要采用链表节点，此处为地址域
    struct HashNode *pre;
} Node;

Node *createNode(KeyType theKey, InfoType theInfo) {
    Node *theNode = (Node *) malloc(sizeof(Node));
    theNode->key = theKey;
    theNode->info = theInfo;
    theNode->next = NULL;
    theNode->pre = NULL;
    return theNode;
}

typedef struct HashTable {
    Node **table;//每个元素都是一个单链表，哈希地址相同的元素在同一个单链表中
    int tableSize;//哈希表的长度
    int elementSize;//哈希表中总共存放了多少个元素
} Table;

//创建哈希表
Table *createHashTable(int tableSize) {
    Table *theTable = (Table *) malloc(sizeof(Table));
    theTable->table = (Node **) malloc(sizeof(Node *) * tableSize);
    theTable->tableSize = tableSize;
    for (int i = 0; i < tableSize; i++) {
        theTable->table[i] = NULL;
    }
    theTable->elementSize = 0;
    return theTable;
}

//哈希映射函数，返回关键字在哈希表中的下标
int hashFunction(Table *table, KeyType theKey) {
    return theKey % (table->tableSize);
}

//向哈希表中添加元素
bool hashInsert(Table *theTable, KeyType theKey, InfoType theInfo) {
    //整个链表是双向循环链表
    int address = hashFunction(theTable, theKey);//利用哈希映射根据关键字计算存储位置
    if (address < 0 || address >= theTable->tableSize) {
        //关键字经过哈希映射之后找不到位置则返回false
        return false;
    }
    Node *newNode = createNode(theKey, theInfo);//创建链表新节点
    if (theTable->table[address] == NULL) {
        //没有产生哈希冲突，直接插入
        theTable->table[address] = newNode;
        newNode->pre = newNode;
        newNode->next = newNode;
    } else {
        //产生了哈希冲突，在该位置的单链表末尾
        Node *rear = theTable->table[address]->pre;//因为首节点的前驱指向整个链表的最后一个节点，所以要插入新节点则要获得最后一个节点的地址
        rear->next = newNode;//最后一个节点的下一个节点就是新节点
        newNode->pre = rear;//新节点的前一个节点是插入之前的最后一个节点
        newNode->next = theTable->table[address];
        theTable->table[address]->pre = newNode;//首节点的前驱要保存整个链表最后一个节点的地址
    }
    theTable->elementSize++;//节点数更新
    return true;
}

//哈希表元素的查找，若找到了则返回该元素的前一个节点的地址，没找到则返回空地址
Node *hashSearch(Table *theTable, Node *theNode) {
    KeyType theKey = theNode->key;
    InfoType theInfo = theNode->info;
    int address = hashFunction(theTable, theKey);//利用哈希映射根据关键字计算存储位置
    if (address < 0 || address >= theTable->tableSize) {
        //关键字经过哈希映射之后找不到位置
        return NULL;
    }
    Node *pointer = theTable->table[address];
    if (pointer == NULL) {
        return NULL;
    }
    Node *prePointer = pointer->pre;

    do {
//比较有问题
        if (strcmp(theInfo,pointer->info)==0) {
            return prePointer;
        }
        prePointer=pointer;
        pointer = pointer->next;
    } while (pointer != theTable->table[address]);
    return NULL;

}


//哈希表元素的删除，删除成功返回true，失败则返回false
bool hashElementDelete(Table *theTable, Node *theNode) {
    Node *rear = hashSearch(theTable, theNode);
    if (rear) {
        //找到了该元素，则删除该元素
        Node *temp = rear->next;
        rear->next = rear->next->next;
        rear->next->pre = rear;
        free(temp);
        return true;
    } else return false;
}

//哈希表的删除撤销，释放其中所有空间
void hashTableDelete(Table *theTable) {
    Node *pointer = NULL;
    Node *nextPointer = NULL;
    for (int i = 0; i < theTable->tableSize; i++) {
        pointer = theTable->table[i]->pre;//pointer指向链表的最后一个节点
        nextPointer = pointer->pre;//nextPointer指向倒数第二个节点
        theTable->table[i]->pre = NULL;
        theTable->table[i]=NULL;
        while (nextPointer != NULL) {
            free(pointer);
            pointer = nextPointer;
            nextPointer = nextPointer->pre;
        }
        free(pointer);
        pointer=NULL;
    }
    free(theTable->table);
}
