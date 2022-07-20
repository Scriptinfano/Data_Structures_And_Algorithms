#pragma once

#include "illegalParameterValue.h"
#include"arrayList.h"

template<class T>
void changeLength1D(T *&a, int oldLength, int newLength) {
    if (newLength < 0)
        throw illegalParameterValue("新数组的长度必须大于等于0");
    T *temp = new T[newLength];             //为新数组分配空间
    int number = min(oldLength, newLength); //返回较小的值
    copy(a, a + number, temp);              //将老数组的值依次拷贝到新数组
    delete[] a;                             //释放老数组的内存
    a = temp;                               //使得原指针能引用新数组
}

//改变二维数组的大小，内部每一个一维数组的大小也可以改变
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

    delete[] a;//存储每个一维数组首地址的数组还没有释放内存，此时释放所有存储一维数组地址的内存
    a = temp;
}

