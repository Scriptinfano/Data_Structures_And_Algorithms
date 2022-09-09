#include <iostream>

using namespace std;

class Father {
private:
    virtual void virtual_base_private() {
        cout << "�������˽�к���" << endl;
    }

    void base_private() {
        cout << "����˽�к���" << endl;
    }

    virtual void pure_virtual_base_private() = 0;//���ඨ���˽�д��麯�����ܱ�������д�����������ڶ��壬����˽�еĴ��麯��ֻ�������ⶨ�壬�ҵ���ֻ��������ĺ����е���

protected:
    void base_protected() {
        cout << "���ౣ������" << endl;
    }

    virtual void virtual_base_protected() {
        cout << "������ౣ������" << endl;
    }

    virtual void pure_virtual_base_protected() = 0;

    virtual void virtual_base_protected2();

public:

    virtual void virtual_base_public() {
        cout << "������๫�к���" << endl;
    }

    virtual void pure_virtual_base_public() = 0;


    void base_public() {
        cout << "���๫�к���" << endl;
    }
};

void Father::pure_virtual_base_private() {
    cout << "����˽�еĴ��麯����Ĭ��ʵ�ִ���" << endl;
}

class Son : public Father {
private:
    void sub_private() {
        cout << "����˽�к���" << endl;

    }

    virtual void virtual_sub_private() {
        cout << "��������˽�к���" << endl;
    }


protected:
    void sub_protected() {
        cout << "���ౣ������" << endl;
    }

    virtual void virtual_sub_protected() {
        cout << "�������ౣ������" << endl;
    }


public :

    virtual void pure_virtual_base_private()override {
        cout<<"�ڻ��๫��Ȩ������д����˽�д��麯��"<<endl;
    }

    void sub_public() {
        cout << "���๫�к���" << endl;
    }

    virtual void virtual_sub_public() {
        cout << "�������๫�к���" << endl;
    }

    void virtual_base_protected() override {
        cout << "������Ĺ���Ȩ������д�������Ᵽ������" << endl;
        pure_virtual_base_protected();
    }


    void pure_virtual_base_protected() override {
        cout << "������Ĺ���Ȩ������д����ı������麯��" << endl;
    }

    void pure_virtual_base_public() override {
        cout << "������Ĺ���Ȩ������д����Ĺ��д��麯��" << endl;
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