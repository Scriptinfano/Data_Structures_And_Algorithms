/*
 * ͨ��ʵ�ֽӿڵķ�ʽ��ʵ��ջ�ṹ*/
#pragma once

#include "StackADT.h"
#include "D:\ClionProjects\Data_Structures_And_Algorithms\globalFunctionSpace.h"

using namespace GlobalSpace;
using namespace ::StackExceptionSpace;

//TODO ��ɿɳ�ʼ���ӿڵ����֮��ʵ�ָýӿڣ�ʵ�ֳ�ʼ��¼�����ݲ���
template<class T>
class ArrayStack : public StackADT<T>, public StackExtendFunctionInterface<T> {
    friend void GlobalSpace::changeLength1D(T *&a, int oldLength, int newLength);

private:
    int stackTop;//����ջ��Ԫ��������ջ�е�������ע����������Ǵ�0��ʼ��
    int stackLength;//ջ����
    T *stack;//Ԫ������

    //�ú���ȷ��������д����Ĵ��麯����ʹ�ø��಻Ϊ������࣬����ĺ�������Ҫд�κ�ʵ�ֲ���Ҫ���κεط�����
    virtual void pureVirtual() override {}

public:
    //���캯������������
    ArrayStack(const int &initialCapacity) {
        if (initialCapacity < 1) {
            ostringstream message;
            message << "��ʼ�����������0";
            throw IllegalParameterValue(message.str());//str()���ַ������е����ݸ��Ƶ�string�����в�����
        }
        stackLength = initialCapacity;
        stack = new T[stackLength];
        stackTop = -1;
    }

    ~ArrayStack() {
        delete[]stack;
    }

    //ʵ�ֽӿ�
    void initializeStack(const vector<T> &array) override {
        //if (array.size() > stackLength)throw InvalidStackInitializeException();
        if (array.empty())return;
        for (T element: array) {
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
        if (stackTop < (stackLength / 4)) {
            //��ջ��Ԫ�ؼ��ٵ�ԭ�����ķ�֮һ���µ�ʱ��ջ������Ӧ�ü��ٵ���ǰ������һ��
            changeLength1D(stack, stackLength, stackLength / 2);
        }
        stack[stackTop--].~T();
    }

    void push(const T &theElement) override {

        if (stackTop == stackLength - 1) {
            changeLength1D(stack, stackLength, 2 * stackLength);
            stackLength *= 2;
        }
        //��ջ������Ԫ��
        stack[++stackTop] = theElement;//stackTop����ջ��Ԫ�ص�����������Ӧ���ȼ�1�õ�ջ��Ԫ������һ��λ�õ�����
    }

    ArrayStack<T> *split() override {
        if (empty())throw StackEmptyException();
        int half = size() / 2;
        T *temp = new T[half];
        for (int i = 0; i < half; i++) {
            temp[i] = this->getTop();
            this->pop();
        }
        auto newStack = new ArrayStack(half);
        for (int i = half - 1; i > -1; i--) {
            newStack->push(temp[i]);
        }
        delete[]temp;
        return newStack;
    }

    void merge(StackExtendFunctionInterface<T> &theStack) override {
        //������ջ�ϲ������ı�ڶ���ջ��Ԫ�ص����˳��
        ArrayStack<T> &secondStack = dynamic_cast<ArrayStack<T> &>(theStack);
        changeLength1D(stack, stackLength, secondStack.size());
        auto temp = new ArrayStack(secondStack.size());
        int i = 0;
        while (!secondStack.empty()) {
            temp->push(secondStack.getTop());
            secondStack.pop();
        }
        while (!temp->empty()) {
            this->push(temp->getTop());
            temp->pop();
        }
        delete temp;
    }

};