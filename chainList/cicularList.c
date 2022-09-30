//
// Created by Mingxiang on 2022/9/29.
//

#include "cicularList.h"
#include <stdio.h>

int main() {
    printf("初始化单循环链表\n");
    CircularPointer list = initializeList();
    int listSize = getSizeOfList(list);
    printf("初始链表中的元素个数=%d \n", listSize);
    printf("向链表中添加四个元素：13，14，16，41\n");
    addNode_back(list, 13);
    addNode_back(list, 14);
    addNode_back(list, 16);
    addNode_back(list, 41);
    printf("打印输出添加之后的链表中的每一个元素\n");
    processErr(outPutList(list));
    printf("删除链表中第二个节点，第一个节点，第四个节点\n");
    processErr(deleteNode(list, 2));
    processErr(deleteNode(list, 1));
    processErr(deleteNode(list, 2));
    printf("打印删除三个元素之后的链表中的每一个元素\n");
    processErr(outPutList(list));
    printf("目前链表的节点个数=%d\n", getSizeOfList(list));
    printf("在链表表头插入两个新节点:89,68\n");
    processErr(addNode_front(list, 89));
    processErr(addNode_front(list, 68));
    printf("打印添加两个节点之后的链表中的每一个元素\n");
    processErr(outPutList(list));
    printf("取得第三个节点的数据\n");
    DataType *store = (DataType *) malloc(sizeof(int));
/*
    int temp=0;
    int *store=&temp;
*/
    processErr(getNodeElement(list, 3, store));
    printf("第三个节点的数据是：%d \n", *store);


    free(store);

    freeList(list);//释放整个链表的内存

    return 0;
}