#pragma once

#include "StackADT.h"
#include "D:\ClionProjects\Data_Structures_And_Algorithms\linearList\arrayAndVectorList\arrayList.hpp"
#include "D:\ClionProjects\Data_Structures_And_Algorithms\selfDefineExceptionSpace.h"

using namespace StackExceptionSpace;

template<class T>
class StackWithArrayList : public StackADT<T> {
private:
    arrayList<T> list;
public :
    StackWithArrayList(const arrayList<T> &list) : list(list) {}

    StackWithArrayList() = default;

    ~StackWithArrayList() = default;

    [[nodiscard]] bool empty() const override {
        return list.empty();
    }

    [[nodiscard]] int size() const override {
        return list.size();
    }

    T getTop() const override {
        return list.get(list.size() - 1);
    }

    T &top() override = delete;//不实现也不使用抽象基类中定义的功能

    void pop() override {
        list.erase(list.size() - 1);
    }

    void push(const T &theElement) override {
        list.push_back(theElement);
    }

    void initializeStack(const vector<T> &array) {
        if (!this->empty())throw ReinitializeStackException();
        if (array.empty())throw VectorEmptyException();
        for (int i = 0; i < array.size(); i++) {
            list.push_back(array.at(i));
        }
    }

    void output() override {
        try {
            list.output(cout);

        } catch (const ArrayListEmptyException &e) {
            throw StackEmptyException();
        }
    }

};
