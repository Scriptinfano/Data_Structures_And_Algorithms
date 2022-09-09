#include <iostream>

using namespace std;

class Father {
private:
    virtual void virtual_base_private() {
        cout << "虚拟基类私有函数" << endl;
    }

    void base_private() {
        cout << "基类私有函数" << endl;
    }

    virtual void pure_virtual_base_private() = 0;//基类定义的私有纯虚函数不能被子类重写，不能有类内定义，基类私有的纯虚函数只能在类外定义，且调用只能在子类的函数中调用

protected:
    void base_protected() {
        cout << "基类保护函数" << endl;
    }

    virtual void virtual_base_protected() {
        cout << "虚拟基类保护函数" << endl;
    }

    virtual void pure_virtual_base_protected() = 0;

    virtual void virtual_base_protected2();

public:

    virtual void virtual_base_public() {
        cout << "虚拟基类公有函数" << endl;
    }

    virtual void pure_virtual_base_public() = 0;


    void base_public() {
        cout << "基类公有函数" << endl;
    }
};

void Father::pure_virtual_base_private() {
    cout << "基类私有的纯虚函数的默认实现代码" << endl;
}

class Son : public Father {
private:
    void sub_private() {
        cout << "子类私有函数" << endl;

    }

    virtual void virtual_sub_private() {
        cout << "虚拟子类私有函数" << endl;
    }


protected:
    void sub_protected() {
        cout << "子类保护函数" << endl;
    }

    virtual void virtual_sub_protected() {
        cout << "虚拟子类保护函数" << endl;
    }


public :

    virtual void pure_virtual_base_private()override {
        cout<<"在基类公有权限中重写基类私有纯虚函数"<<endl;
    }

    void sub_public() {
        cout << "子类公有函数" << endl;
    }

    virtual void virtual_sub_public() {
        cout << "虚拟子类公有函数" << endl;
    }

    void virtual_base_protected() override {
        cout << "在子类的公有权限下重写基类虚拟保护函数" << endl;
        pure_virtual_base_protected();
    }


    void pure_virtual_base_protected() override {
        cout << "在子类的公有权限中重写基类的保护纯虚函数" << endl;
    }

    void pure_virtual_base_public() override {
        cout << "在子类的公有权限下重写基类的公有纯虚函数" << endl;
        pure_virtual_base_protected();
        pure_virtual_base_private();
    }

};

int main() {
    Father *person = new Son();
    person

/*
    Son son;
    son.pure_virtual_base_public();
*/


    return 0;
}