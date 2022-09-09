#pragma once

#include "ChainNode.h"
#include "D:\ClionProjects\Data_Structures_And_Algorithms\selfDefineExceptionSpace.h"
#include <vector>
#include <stdexcept>
#include "D:\ClionProjects\Data_Structures_And_Algorithms\linearList\BaseLinearList.h"
using namespace ExceptionSpace::LinkListExceptions;

//带头节点的链表类，使用该链表时下标一律从1开始
class ChainListWithHead : public TempLinearList {
private:
    NodePointer head;//指向头节点的指针
    int listSize;
public:
    //构造一个空链表
    ChainListWithHead() {
        head = new Node(nullptr);//构造头节点
        listSize = 0;
    }

    //用头插法构造一个节点个数为initialCapacity的链表
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
        NodePointer p = head->next;//p指向首元节点
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
        if (index < 1 || index > listSize)throw out_of_range("取得链表元素时，链表下标越界");
        NodePointer p = head->next;
        for (int i = 0; i < index; i++) {
            p = p->next;
        }
        return p->data;
    }

    void erase(const int &index) override {
        if (empty())throw LinklistEmptyException();
        if (index < 1 || index > listSize)throw out_of_range("删除链表元素时，链表下标越界");
        NodePointer p = head->next;
        for (int i = 0; i < index - 2; i++) {
            p = p->next;
        }
        NodePointer deleteNode = p->next;
        p->next = p->next->next;
        delete deleteNode;
        listSize--;
    }

    //@param index 要在链表的第几个节点之前插入节点（注意这里头节点不算入第一个节点）
    void insert(const int &index, const int &theElement) override {
        if (empty() && index != 1)
            throw out_of_range("当链表为空时，插入元素的下标越界");
        else if (index < 1 || index > listSize)throw out_of_range("当链表不为空时，插入元素的下标越界");
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

    //清空链表所有节点，注意不包括头节点
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

    //常规接口
    //在链表的尾部插入一个新元素
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

    //链表排序
    void linkListSort() {
        NodePointer curr, pre, p, q;
        p = head->next;//p指向首元节点
        head->next = nullptr;//将首元节点和头节点断开，使得head所指向的链表成为了一个空表，一个空表可视为一个有序链表

        while (p != nullptr) {
            curr = head->next;//curr指向链表中应该是首元节点的地址，此时因为head指向空表，所以此时curr为空
            pre = head;//pre指向头节点
            while (curr != nullptr && curr->data <= p->data) {
                pre = curr;
                curr = curr->next;
            }
            q = p;
            p = p->next;//p指向下一个要插入的节点
            q->next = pre->next;
            pre->next = q;
        }



    }

    //删除链表中最大的元素
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
        //将vector容器中所有元素追加到链表上
        for (int i = 0; i < array.size(); i++) {
            push_back(array.at(i));
        }
        listSize += array.size();
    }


};