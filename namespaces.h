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
        explicit IllegalParameterValue(string_view theMessage = "�Ƿ���������") : message(theMessage) {}
        const char * what() const noexcept override//��д���ຯ��
        {
            return message.c_str();
        }
    };

    class outOfBounds: public exception{
    protected:
        string message;
    public:
        explicit outOfBounds(string_view theMessage = "���ʳ�������") : message(theMessage) {}
        const char * what() const noexcept override
        {
            return message.c_str();
        }

    };

    class matrixIndexOutOfBounds : public outOfBounds {
    public:
        explicit matrixIndexOutOfBounds(string_view theMessage = "�����±����ô��󣬵��·��ʳ�������") : outOfBounds(theMessage) {}
    };

    class iteratorOutOfBounds:public outOfBounds{
    public:
        explicit iteratorOutOfBounds(string_view theMessage="�����������ɷ��ʽ���"): outOfBounds(theMessage){}
    };

    class matrixSizeMismatch:public exception {
    protected:
        string message;
    public:
        explicit matrixSizeMismatch(string_view theMessage = "�����С���ƥ��") : message(theMessage) {}

        const char * what() const noexcept override
        {
            return message.c_str();
        }
    };

    class matrixSizeMismatchOfPlus : public matrixSizeMismatch {
    public:
        explicit matrixSizeMismatchOfPlus(string_view theMessage = "ִ�о���ӷ�ʱ����������Ĵ�С��������ȫ��ͬ") : matrixSizeMismatch(
                theMessage) {}
    };

    class matrixSizeMismatchOfMultiply : public matrixSizeMismatch {
    public:
        explicit matrixSizeMismatchOfMultiply(string_view theMessage = "ִ�о���˷�ʱ����һ���������������͵ڶ������������������ͬ")
                : matrixSizeMismatch(
                theMessage) {}
    };

    class matrixSizeMismatchOfInitialize : public matrixSizeMismatch {
    public:
        explicit matrixSizeMismatchOfInitialize(string_view theMessage = "ִ�о����ʼ��ʱ������ľ������͵�ǰ�ľ����С�����ȫ��ͬ")
                : matrixSizeMismatch(
                theMessage) {}
    };

    class matrixSizeMismatchOfSubtraction : public matrixSizeMismatch {
    public:
        explicit matrixSizeMismatchOfSubtraction(string_view theMessage = "ִ�о������ʱ������ľ������͵�ǰ�ľ����С�����ȫ��ͬ")
                : matrixSizeMismatch(
                theMessage) {}

    };

    class uninitializedMatrix:public exception {
    private:
        string message;
    public:
        explicit uninitializedMatrix(string_view theMessage = "ʹ��δ��ʼ���ľ���ִ���˾�������") : message(theMessage) {}
        const char * what() const noexcept override
        {
            return message.c_str();
        }

    };

    class reInitializedMatrix:public exception{
    private:
        string message;
    public:
        explicit reInitializedMatrix(string_view theMessage = "�Ѿ���ʼ�����ľ������ٴγ�ʼ��") : message(theMessage) {}
        const char * what() const noexcept override
        {
            return message.c_str();
        }
    };

    class invalidMatrixValueSet :public exception{
    private:
        string message;
    public:
        explicit invalidMatrixValueSet(string_view theMessage = "�ı����������Ԫ�ص�ֵʱ���ܽ�����Ԫ����Ϊ�����������������") : message(theMessage) {}
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
            throw ExceptionSpace::IllegalParameterValue("������ĳ��ȱ�����ڵ���0");
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

        delete[] a;//�洢ÿ��һά�����׵�ַ�����黹û���ͷ��ڴ棬��ʱ�ͷ����д洢һά�����ַ���ڴ�
        a = temp;
    }


}
