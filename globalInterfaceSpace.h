#pragma once

//TODO 该接口可以为每一个自定义结构实现初始化录入数据操作
class Initializable {
public:
    virtual ~Initializable() {}
    virtual void initializeByArray(const int *&array);

};