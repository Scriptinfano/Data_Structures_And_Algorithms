#pragma once

#include <iostream>
#include <string_view>
#include <exception>
using namespace std;

namespace ExceptionSpace {
    class IllegalParameterValue:public exception {
    private:
        string message;

    public:
        explicit IllegalParameterValue(string_view theMessage = "非法参数传递") : message(theMessage) {}
        const char * what() const noexcept override//重写父类函数
        {
            return message.c_str();
        }
    };

    class outOfBounds: public exception{
    protected:
        string message;
    public:
        explicit outOfBounds(string_view theMessage = "访问超出界限") : message(theMessage) {}
        const char * what() const noexcept override
        {
            return message.c_str();
        }

    };

    class matrixIndexOutOfBounds : public outOfBounds {
    public:
        explicit matrixIndexOutOfBounds(string_view theMessage = "矩阵下标引用错误，导致访问超出界限") : outOfBounds(theMessage) {}
    };

    class iteratorOutOfBounds:public outOfBounds{
    public:
        explicit iteratorOutOfBounds(string_view theMessage="迭代器超出可访问界限"): outOfBounds(theMessage){}
    };

    class matrixSizeMismatch:public exception {
    protected:
        string message;
    public:
        explicit matrixSizeMismatch(string_view theMessage = "矩阵大小规格不匹配") : message(theMessage) {}

        const char * what() const noexcept override
        {
            return message.c_str();
        }
    };

    class matrixSizeMismatchOfPlus : public matrixSizeMismatch {
    public:
        explicit matrixSizeMismatchOfPlus(string_view theMessage = "执行矩阵加法时，两个矩阵的大小规格必须完全相同") : matrixSizeMismatch(
                theMessage) {}
    };

    class matrixSizeMismatchOfMultiply : public matrixSizeMismatch {
    public:
        explicit matrixSizeMismatchOfMultiply(string_view theMessage = "执行矩阵乘法时，第一个矩阵的列数必须和第二个矩阵的行数必须相同")
                : matrixSizeMismatch(
                theMessage) {}
    };

    class matrixSizeMismatchOfInitialize : public matrixSizeMismatch {
    public:
        explicit matrixSizeMismatchOfInitialize(string_view theMessage = "执行矩阵初始化时，传入的矩阵必须和当前的矩阵大小规格完全相同")
                : matrixSizeMismatch(
                theMessage) {}
    };

    class matrixSizeMismatchOfSubtraction : public matrixSizeMismatch {
    public:
        explicit matrixSizeMismatchOfSubtraction(string_view theMessage = "执行矩阵减法时，传入的矩阵必须和当前的矩阵大小规格完全相同")
                : matrixSizeMismatch(
                theMessage) {}

    };

    class uninitializedMatrix:public exception {
    private:
        string message;
    public:
        explicit uninitializedMatrix(string_view theMessage = "使用未初始化的矩阵执行了矩阵运算") : message(theMessage) {}
        const char * what() const noexcept override
        {
            return message.c_str();
        }

    };

    class reInitializedMatrix:public exception{
    private:
        string message;
    public:
        explicit reInitializedMatrix(string_view theMessage = "已经初始化过的矩阵不能再次初始化") : message(theMessage) {}
        const char * what() const noexcept override
        {
            return message.c_str();
        }
    };

    class invalidMatrixValueSet :public exception{
    private:
        string message;
    public:
        explicit invalidMatrixValueSet(string_view theMessage = "改变特殊矩阵中元素的值时不能将零区元素设为除了零以外的其他数") : message(theMessage) {}
        const char * what() const noexcept override
        {
            return message.c_str();
        }

    };

}
namespace GlobalSpace {
    template<class T>
    void changeLength1D(T *&a, int oldLength, int newLength) {
        if (newLength < 0)
            throw ExceptionSpace::IllegalParameterValue("新数组的长度必须大于等于0");
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
                        int newColumns) {// Resize the two-dimensional arrayList a that has oldRows number of rows.
        // The dimensions of the resized arrayList are newRows x newColumns.
        // Copy the top left oldRows x newColumns sub arrayList into the resized arrayList.
        // make sure new dimensions are adequate
        if (copyRows > newRows || copyColumns > newColumns)
            throw ExceptionSpace::IllegalParameterValue("new dimensions are too small");

        T **temp = new T *[newRows];              // arrayList for rows
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


}
