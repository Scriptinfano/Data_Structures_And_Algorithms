#pragma once

#include "illegalParameterValue.h"
#include"arrayList.h"

template<class T>
void changeLength1D(T *&a, int oldLength, int newLength) {
    if (newLength < 0)
        throw illegalParameterValue("������ĳ��ȱ�����ڵ���0");
    T *temp = new T[newLength];             //Ϊ���������ռ�
    int number = min(oldLength, newLength); //���ؽ�С��ֵ
    copy(a, a + number, temp);              //���������ֵ���ο�����������
    delete[] a;                             //�ͷ���������ڴ�
    a = temp;                               //ʹ��ԭָ��������������
}

//�ı��ά����Ĵ�С���ڲ�ÿһ��һά����Ĵ�СҲ���Ըı�
template<class T>
void changeLength2D(T **&a, int oldRows, int copyRows,
                    int copyColumns, int newRows,
                    int newColumns) {// Resize the two-dimensional array a that has oldRows number of rows.
    // The dimensions of the resized array are newRows x newColumns.
    // Copy the top left oldRows x newColumns sub array into the resized array.
    // make sure new dimensions are adequate
    if (copyRows > newRows || copyColumns > newColumns)
        throw illegalParameterValue("new dimensions are too small");

    T **temp = new T *[newRows];              // array for rows
    // create row arrays for temp
    for (int i = 0; i < newRows; i++)
        temp[i] = new T[newColumns];

    // copy from old space to new space, delete old space
    for (int i = 0; i < copyRows; i++) {
        copy(a[i], a[i] + copyColumns, temp[i]);
        delete[] a[i];                      // deallocate old memory
    }

    // delete remaining rows of a
    for (int i = copyRows; i < oldRows; i++)
        delete[] a[i];

    delete[] a;//�洢ÿ��һά�����׵�ַ�����黹û���ͷ��ڴ棬��ʱ�ͷ����д洢һά�����ַ���ڴ�
    a = temp;
}

