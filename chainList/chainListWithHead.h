#pragma once

#include "ChainNode.h"
#include "D:\ClionProjects\Data_Structures_And_Algorithms\selfDefineExceptionSpace.h"
#include <vector>
#include <stdexcept>
#include "D:\ClionProjects\Data_Structures_And_Algorithms\linearList\BaseLinearList.h"
using namespace ExceptionSpace::LinkListExceptions;

//��ͷ�ڵ�������࣬ʹ�ø�����ʱ�±�һ�ɴ�1��ʼ
class ChainListWithHead : public TempLinearList {
private:
    NodePointer head;//ָ��ͷ�ڵ��ָ��
    int listSize;
public:
    //����һ��������
    ChainListWithHead() {
        head = new Node(nullptr);//����ͷ�ڵ�
        listSize = 0;
    }

    //��ͷ�巨����һ���ڵ����ΪinitialCapacity������
    explicit ChainListWithHead(const int &initialCapacity) {
        head = new Node(nullptr);
        NodePointer p = head;
        for (int i = 0; i < initialCapacity; i++) {
            p->next = new Node(0, nullptr);
            p = p->next;
        }
        listSize = initialCapacity;
    }

    ~ChainListWithHead() {
        while (head != nullptr) {
            NodePointer nextNode = head->next;
            delete head;
            head = nextNode;
        }
    }

    [[nodiscard]] bool empty() const override {
        return head->next == nullptr || listSize == 0;
    }

    [[nodiscard]] int indexOf(const int &theElement) const override {
        if (empty())throw LinklistEmptyException();
        NodePointer p = head->next;//pָ����Ԫ�ڵ�
        int index = 0;
        while (p != nullptr && p->data != theElement) {
            p = p->next;
            index++;
        }
        if (p == nullptr)throw ElementNotFoundException();
        return index + 1;
    }

    [[nodiscard]] int getElement(const int &index) const override {
        if (empty())throw LinklistEmptyException();
        if (index < 1 || index > listSize)throw out_of_range("ȡ������Ԫ��ʱ�������±�Խ��");
        NodePointer p = head->next;
        for (int i = 0; i < index; i++) {
            p = p->next;
        }
        return p->data;
    }

    void erase(const int &index) override {
        if (empty())throw LinklistEmptyException();
        if (index < 1 || index > listSize)throw out_of_range("ɾ������Ԫ��ʱ�������±�Խ��");
        NodePointer p = head->next;
        for (int i = 0; i < index - 2; i++) {
            p = p->next;
        }
        NodePointer deleteNode = p->next;
        p->next = p->next->next;
        delete deleteNode;
        listSize--;
    }

    //@param index Ҫ������ĵڼ����ڵ�֮ǰ����ڵ㣨ע������ͷ�ڵ㲻�����һ���ڵ㣩
    void insert(const int &index, const int &theElement) override {
        if (empty() && index != 1)
            throw out_of_range("������Ϊ��ʱ������Ԫ�ص��±�Խ��");
        else if (index < 1 || index > listSize)throw out_of_range("������Ϊ��ʱ������Ԫ�ص��±�Խ��");
        else {
            NodePointer p = head->next;
            for (int i = 0; i < index - 2; i++) {
                p = p->next;
            }
            auto newNode = new Node(theElement, p->next);
            p->next = newNode;
            listSize++;
        }
    }

    void output() const override {
        if (empty())throw LinklistEmptyException();
        for (auto currentNode = head->next; currentNode != nullptr; currentNode = currentNode->next) {
            cout << currentNode->data << " ";
        }
    }

    //����������нڵ㣬ע�ⲻ����ͷ�ڵ�
    void clear() override {
        if (empty())return;
        NodePointer p = head->next;
        while (p != nullptr) {
            NodePointer nextNode = p->next;
            delete p;
            p = nextNode;
        }
        listSize = 0;
    }

    //����ӿ�
    //�������β������һ����Ԫ��
    void push_back(const int &theElement) {
        if (empty()) {
            head->next = new Node(theElement, nullptr);
            listSize++;
            return;
        }
        NodePointer p = head->next;
        while (p->next != nullptr)
            p = p->next;
        p->next = new Node(theElement, nullptr);
        listSize++;
    }

    //��������
    void linkListSort() {
        NodePointer curr, pre, p, q;
        p = head->next;//pָ����Ԫ�ڵ�
        head->next = nullptr;//����Ԫ�ڵ��ͷ�ڵ�Ͽ���ʹ��head��ָ��������Ϊ��һ���ձ�һ���ձ����Ϊһ����������

        while (p != nullptr) {
            curr = head->next;//currָ��������Ӧ������Ԫ�ڵ�ĵ�ַ����ʱ��Ϊheadָ��ձ����Դ�ʱcurrΪ��
            pre = head;//preָ��ͷ�ڵ�
            while (curr != nullptr && curr->data <= p->data) {
                pre = curr;
                curr = curr->next;
            }
            q = p;
            p = p->next;//pָ����һ��Ҫ����Ľڵ�
            q->next = pre->next;
            pre->next = q;
        }



    }

    //ɾ������������Ԫ��
    void eraseMaxElement() {
        if (empty())throw LinklistEmptyException();
        NodePointer maxPointer=head;
        NodePointer p=head->next;
        NodePointer pre=head;
        while(p!= nullptr)
        {
            if(p->data>maxPointer->next->data){
                maxPointer=pre;
            }
            pre=p;
            p=p->next;
        }
        p=maxPointer->next;
        maxPointer->next=maxPointer->next->next;
        delete p;
        listSize--;
    }

    void import(const vector<int> &array) {
        //��vector����������Ԫ��׷�ӵ�������
        for (int i = 0; i < array.size(); i++) {
            push_back(array.at(i));
        }
        listSize += array.size();
    }


};