//全局函数封装
#pragma once

#include "selfDefineExceptionSpace.h"

using namespace ExceptionSpace;
namespace GlobalSpace {
    template<class T>
    void changeLength1D(T *&a, int oldLength, int newLength) {
        if (newLength < 0)
            throw IllegalParameterException("新数组的长度必须大于等于0");
        T *temp = new T[newLength];             //为新数组分配空间
        int number = min(oldLength, newLength); //返回较小的值
        copy(a, a + number, temp);              //将老数组的值依次拷贝到新数组
        delete[] a;                             //释放老数组的内存
        a = temp;                               //使得原指针能引用新数组
    }

//改变二维数组的大小，内部每一个一维数组的大小也可以改变
    template<class T>
    void changeLength2D(T **&a, int oldRows, int copyRows, int copyColumns, int newRows, int newColumns) {
        if (copyRows > newRows || copyColumns > newColumns)
            throw IllegalParameterException("new dimensions are too small");

        T **temp = new T *[newRows];//创建保存新二维数组地址的指针
        for (int i = 0; i < newRows; i++)
            temp[i] = new T[newColumns];//为每一行分配空间

        //将老数组的元素按照copyRows x copyColumns的规格复制到新数组
        for (int i = 0; i < copyRows; i++) {
            copy(a[i], a[i] + copyColumns, temp[i]);
            delete[] a[i];//删除旧空间
        }

        //删除旧数组剩下的空间
        for (int i = copyRows; i < oldRows; i++)
            delete[] a[i];

        delete[] a;//存储每个一维数组首地址的数组还没有释放内存，此时释放所有存储一维数组地址的内存
        a = temp;//让老数组的指针指向新数组的地址
    }

    int getMatrixSize(vector<vector<int>> theMatrix) {
        int sum=0;
        for(int i=0;i<theMatrix.size();i++)
        {
            for(int j=0;j<theMatrix.at(i).size();j++)
                sum++;
        }
        return sum;
    }

}
