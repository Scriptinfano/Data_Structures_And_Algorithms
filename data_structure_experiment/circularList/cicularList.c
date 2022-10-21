//
// Created by Mingxiang on 2022/9/29.
// ��GB2312����򿪴��ļ�

#include "cicularList.h"
#include <stdio.h>

int main() {
    printf("��ʼ����ѭ������\n");
    CircularPointer list = initializeList();
    int listSize = getSizeOfList(list);
    printf("��ʼ�����е�Ԫ�ظ���=%d \n", listSize);

    //�ڱ�β��ӹ��ܲ���
    printf("������������ĸ�Ԫ�أ�13��14��16��41\n");
    addNode_back(list, 13);
    addNode_back(list, 14);
    addNode_back(list, 16);
    addNode_back(list, 41);
    printf("��ӡ������֮��������е�ÿһ��Ԫ��\n");
    processErr(outPutList(list));

    //ɾ�����ܲ���
    printf("ɾ�������еڶ����ڵ㣬��һ���ڵ㣬���ĸ��ڵ�\n");
    processErr(deleteNode(list, 2));
    processErr(deleteNode(list, 1));
    processErr(deleteNode(list, 2));
    printf("��ӡɾ������Ԫ��֮��������е�ÿһ��Ԫ��\n");
    processErr(outPutList(list));

    //ɾ��ʧ�ܵ���ʾ����
    printf("ɾ��ʧ�ܵ���ʾ���ԣ���ͼɾ�������еڰ˸�Ԫ�أ���ʱ�ڰ˸�Ԫ�ز����ڣ����ᱨ��\n");
    processErr(deleteNode(list, 8));

    //�ڱ�ͷ��ӹ��ܲ���
    printf("Ŀǰ����Ľڵ����=%d\n", getSizeOfList(list));
    printf("�������ͷ���������½ڵ�:89,68\n");
    processErr(addNode_front(list, 89));
    processErr(addNode_front(list, 68));
    printf("��ӡ��������ڵ�֮��������е�ÿһ��Ԫ��\n");
    processErr(outPutList(list));

    //ȡ������λ��Ԫ�ع��ܲ���
    printf("ȡ�õ������ڵ������\n");
    DataType *store = (DataType *) malloc(sizeof(int));
    processErr(getNodeElement(list, 3, store));
    printf("�������ڵ�������ǣ�%d \n", *store);

    //ȡ��ĳλ��Ԫ��ʧ�ܵ���ʾ����
    printf("ȡ�õھŸ��ڵ������\n");
    DataType *store2 = (DataType *) malloc(sizeof(int));
    processErr(getNodeElement(list, 9, store2));
    printf("�������ڵ�������ǣ�%d \n", *store2);

    //�ͷŴ洢��ʱ���ݵĿռ�
    free(store);
    free(store2);

    freeList(list);//�ͷ�����������ڴ�

    return 0;
}