//
// Created by Mingxiang on 2022/9/29.
//

#include "cicularList.h"
#include <stdio.h>

int main() {
    printf("��ʼ����ѭ������\n");
    CircularPointer list = initializeList();
    int listSize = getSizeOfList(list);
    printf("��ʼ�����е�Ԫ�ظ���=%d \n", listSize);
    printf("������������ĸ�Ԫ�أ�13��14��16��41\n");
    addNode_back(list, 13);
    addNode_back(list, 14);
    addNode_back(list, 16);
    addNode_back(list, 41);
    printf("��ӡ������֮��������е�ÿһ��Ԫ��\n");
    processErr(outPutList(list));
    printf("ɾ�������еڶ����ڵ㣬��һ���ڵ㣬���ĸ��ڵ�\n");
    processErr(deleteNode(list, 2));
    processErr(deleteNode(list, 1));
    processErr(deleteNode(list, 2));
    printf("��ӡɾ������Ԫ��֮��������е�ÿһ��Ԫ��\n");
    processErr(outPutList(list));
    printf("Ŀǰ����Ľڵ����=%d\n", getSizeOfList(list));
    printf("�������ͷ���������½ڵ�:89,68\n");
    processErr(addNode_front(list, 89));
    processErr(addNode_front(list, 68));
    printf("��ӡ��������ڵ�֮��������е�ÿһ��Ԫ��\n");
    processErr(outPutList(list));
    printf("ȡ�õ������ڵ������\n");
    DataType *store = (DataType *) malloc(sizeof(int));
/*
    int temp=0;
    int *store=&temp;
*/
    processErr(getNodeElement(list, 3, store));
    printf("�������ڵ�������ǣ�%d \n", *store);


    free(store);

    freeList(list);//�ͷ�����������ڴ�

    return 0;
}