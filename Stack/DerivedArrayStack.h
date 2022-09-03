//
// Created by Mingxiang on 2022/9/3.
//

/*
 * 通过派生前面已经定义的数组类来实现栈，缺点是性能低下，优点是可以直接使用基类的方法实现功能*/
#pragma once

#include "D:\ClionProjects\Data_Structures_And_Algorithms\linearList\arrayAndVectorList\arrayList.hpp"
#include "StackADT.h"

template<class T>
class DerivedArrayStack : private arrayList<T>, public StackADT<T> {
public:
    DerivedArrayStack(int initialCapacity = 10) : arrayList<T>(initialCapacity) {}

    virtual bool empty() const {
        return arrayList<T>::empty();
    }

    virtual int size() const {
        return arrayList<T>::size();
    }


    virtual T getTop() const {
        try {
            return arrayList<T>::get(arrayList<T>::size() - 1);
        } catch (IllegalParameterValue exception) {
            throw StackEmptyException();
        }
    }

    virtual T &top() {
        try {
            return arrayList<T>::getSelf(arrayList<T>::size() - 1);
        } catch (IllegalParameterValue exception) {
            throw StackEmptyException();
        }

    }

    virtual void pop() {
        try {
            arrayList<T>::erase(arrayList<T>::size() - 1);
        } catch (IllegalParameterValue exception) {
            throw StackEmptyException();
        }
    }

    virtual void push(const T &theElement) {
        try {
            arrayList<T>::insert(arrayList<T>::size(), theElement);
        } catch (IllegalParameterValue exception) {
            throw StackEmptyException();
        }

    }
};
