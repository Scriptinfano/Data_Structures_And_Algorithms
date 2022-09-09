/*
 * ͨ��ʵ�ֽӿڵķ�ʽ��ʵ��ջ�ṹ*/
#pragma once

#include "StackADT.h"
#include "D:\ClionProjects\Data_Structures_And_Algorithms\globalFunctionSpace.h"

using namespace GlobalSpace;

template<class T>
class ArrayStack : public StackADT<T> {
private:
    int stackTop;//����ջ��Ԫ��������ջ�е�������ע����������Ǵ�0��ʼ��
    int arrayLength;//ջ����
    T *stack;//Ԫ������

public:
    //���캯������������
    ArrayStack(const int &initialCapacity) {
        if (initialCapacity < 1) {
            ostringstream message;
            message << "��ʼ�����������0";
            throw IllegalParameterValue(message.str());//str()���ַ������е����ݸ��Ƶ�string�����в�����
        }
        arrayLength = initialCapacity;
        stack = new T[arrayLength];
        stackTop = -1;
    }

    ~ArrayStack() {
        delete[]stack;
    }

    //ʵ�ֽӿ�
    void initializeStack(const vector<T> &array) override {
        //if (array.size() > arrayLength)throw InvalidStackInitializeException();
        if(array.empty())return;
        for(T element:array){
            this->push(element);
        }
    }

    bool empty() const override {
        return stackTop == -1;
    }

    int size() const override {
        return stackTop + 1;
    }

    T getTop() const override {
        if (stackTop == -1)
            throw StackEmptyException();
        return stack[stackTop];
    }

    T &top() override {
        if (stackTop == -1)
            throw StackEmptyException();
        return stack[stackTop];
    }

    void pop() override {
        if (stackTop == -1)throw StackEmptyException();
        stack[stackTop--].~T();

    }

    void push(const T &theElement) override {

        if (stackTop == arrayLength - 1) {
            changeLength1D(stack, arrayLength, 2 * arrayLength);
            arrayLength *= 2;
        }
        //��ջ������Ԫ��
        stack[++stackTop] = theElement;//stackTop����ջ��Ԫ�ص�����������Ӧ���ȼ�1�õ�ջ��Ԫ������һ��λ�õ�����
    }
};