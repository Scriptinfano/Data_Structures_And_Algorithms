#include <iostream>

using namespace std;

class person {
public :
    virtual ~person() = default;

private:
    virtual void pureable() = 0;

public:
    virtual void func1() {}

    virtual void func2() {}

    virtual void func3() {}

    virtual void func4() {}

    virtual void func5() {}


};

class teacher : public person {
private:
    void pureable() override {}

public:
    ~teacher() override {
        cout << "执行子类的析构函数" << endl;
    }

    teacher() {
        cout << "子类构造函数" << endl;
    }

    void func1() override {
        person::func1();
    }

    void func2() override {
        person::func2();
    }

    void func3() override {
        person::func3();
    }
};


void test() {
    teacher t;
    person *p = new teacher;
}
class Father{
public:
    virtual void fun()=0;
    virtual void fun2()=0;
};
class Son: private Father{
public:
    void fun() override {
cout<<"fun"<<endl;
    }
    void fun2() override{
        cout<<"fun2"<<endl;
    }
};
int main() {
    Son *son=new Son();
    son->fun();

    return 0;
}
