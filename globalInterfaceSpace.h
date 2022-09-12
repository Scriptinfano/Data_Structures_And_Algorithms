#pragma once

#include <vector>

//TODO 该接口可以为每一个自定义结构实现初始化录入数据操作
template<class T>
class Initializable {
public:
    virtual ~Initializable() {}

    virtual void initialize(int array[], int size);

    virtual void initialize(const std::vector<T> &array) {}

};