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
    //哈希表采用链地址法解决冲突，所以存放数据的节点要采用链表节点
    struct HashNode *next;//节点后驱
    struct HashNode *pre;//节点前驱
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
    int tableLength;//哈希表的长度
    int elementSize;//哈希表中总共存放了多少个元素
} Table;

//创建哈希表
Table *createHashTable(int tableSize) {
    Table *theTable = (Table *) malloc(sizeof(Table));
    theTable->table = (Node **) malloc(sizeof(Node *) * tableSize);
    theTable->tableLength = tableSize;
    for (int i = 0; i < tableSize; i++) {
        theTable->table[i] = NULL;
    }
    theTable->elementSize = 0;
    return theTable;
}

//哈希映射函数，返回关键字在哈希表中的下标
int hashFunction(Table *table, KeyType theKey) {
    return theKey % (table->tableLength);
}

//向哈希表中添加元素
void hashInsert(Table *theTable, KeyType theKey, InfoType theInfo) {
    //整个链表是双向循环链表
    int address = hashFunction(theTable, theKey);//利用哈希映射根据关键字计算存储位置
    Node *newNode = createNode(theKey, theInfo);//创建链表新节点
    if (theTable->table[address] == NULL) {
        //没有产生哈希冲突，直接插入
        theTable->table[address] = newNode;
        newNode->pre = newNode;
        newNode->next = newNode;
    } else {
        //产生了哈希冲突，在该位置的单链表末尾插入该元素
        Node *rear = theTable->table[address]->pre;//因为首节点的前驱指向整个链表的最后一个节点，所以要插入新节点则要获得最后一个节点的地址
        rear->next = newNode;//最后一个节点的下一个节点就是新节点
        newNode->pre = rear;//新节点的前一个节点是插入之前的最后一个节点
        newNode->next = theTable->table[address];//新节点指向该单链表首地址，实现双向循环链表
        theTable->table[address]->pre = newNode;//首节点的前驱要保存整个链表最后一个节点的地址
    }
    theTable->elementSize++;//节点数更新
}

//输入节点的key值，返回该节点所在链表的头部节点指针
Node *headPointer(Table *theTable, KeyType theKey) {
    int address = hashFunction(theTable, theKey);
    if (address < 0)return NULL;
    return theTable->table[address];
}

///输入节点的key值，返回该节点所在返回尾部节点指针
Node *tailPointer(Table *theTable, KeyType theKey) {
    int address = hashFunction(theTable, theKey);
    if (address < 0)return NULL;
    return theTable->table[address]->pre;
}

//哈希查找指定的节点，返回找到的节点的指针，如果没有找到则返回NULL，
Node *hashSearch(Table *theTable, KeyType theKey) {
    int address = hashFunction(theTable, theKey);//利用哈希映射根据关键字计算存储位置
    if (address < 0)return NULL;//除留余数法当除数是负数的时候，不能保证结果会落在指定区间内，所以如果用户输入了负数应该直接返回NULL
    Node *pointer = theTable->table[address];
    if (pointer == NULL) {
        return NULL;
    } else {
        //遍历该双向循环链表，比对键值，找到了就返回节点指针
        while (pointer != NULL) {
            if (theKey == pointer->key)
                return pointer;
            else {
                pointer = pointer->next;
            }
            if (pointer == theTable->table[address])
                break;
        }
        return NULL;
    }
}

//哈希表元素的删除，删除成功返回true，失败则返回false
bool hashElementDelete(Table *theTable, KeyType theKey) {
    Node *deleteNode = hashSearch(theTable, theKey);
    Node *head = headPointer(theTable, theKey);
    Node *tail = tailPointer(theTable, theKey);
    if (deleteNode) {
        //如果待删除的节点所在的链表只有待删除节点一个节点，则仅删除该节点，然后将哈希表中该节点所在的槽位置空
        if (deleteNode->next == deleteNode) {
            //此时链表中只有一个节点
            free(deleteNode);
            theTable->table[hashFunction(theTable, theKey)] = NULL;
            return true;
        }
        //找到了该元素，则删除该元素，以下均讨论链表中有多个节点的情况
        if (deleteNode == head) {
            //链表中有多个节点，删除第一个节点
            Node *temp = deleteNode;
            Node *newHead = deleteNode->next;
            newHead->pre = tail;
            tail->next = newHead;
            theTable->table[hashFunction(theTable, theKey)] = newHead;
            free(temp);
        } else if (deleteNode == tail) {
            //如果待删除的节点是链表的最后一个节点
            deleteNode->pre->next = head;
            head->pre = deleteNode->pre;
            free(deleteNode);
        } else {
            //如果待删除的节点是链表中间的某个节点
            deleteNode->pre->next = deleteNode->next;
            deleteNode->next->pre = deleteNode->pre;
            free(deleteNode);
        }
        theTable->elementSize--;
        return true;
    } else return false;
}

//哈希表的删除撤销，释放其中所有空间
void freeHashTable(Table *theTable) {
    Node *pointer = NULL;
    Node *nextPointer = NULL;
    for (int i = 0; i < theTable->tableLength; i++) {
        pointer = theTable->table[i]->pre;//pointer指向链表的最后一个节点
        nextPointer = pointer->pre;//nextPointer指向倒数第二个节点
        theTable->table[i]->pre = NULL;
        theTable->table[i] = NULL;
        while (nextPointer != NULL) {
            free(pointer);
            pointer = nextPointer;
            nextPointer = nextPointer->pre;
        }
        free(pointer);
        pointer = NULL;
    }
    free(theTable->table);
}
