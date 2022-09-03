//
// Created by Mingxiang on 2022/9/3.
//
#pragma once

template<class T>
class StackADT {
public :
    virtual ~StackADT() {}

    virtual bool empty() const = 0;

    virtual int size() const = 0;

    virtual T getTop() const = 0;

    virtual T &top() = 0;

    virtual void pop() = 0;

    virtual void push(const T &theElement) = 0;

};

