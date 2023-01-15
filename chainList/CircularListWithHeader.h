//定义带头节点的环形链表
#pragma once

#include<vector>
#include<sstream>
#include "D:\ClionProjects\Data_Structures_And_Algorithms\selfDefineExceptionSpace.h"
#include "D:\ClionProjects\Data_Structures_And_Algorithms\linearList\BaseLinearList.h"
#include "D:\ClionProjects\Data_Structures_And_Algorithms\chainList\ChainNode.h"
using namespace std;
using ExceptionSpace::IllegalParameterException;

//带头结点的环形链表
template<class T>
class CircularListWithHeader : public LinearList<T> {
public:
    typedef ChainNode<T> *NodePointer;
    typedef ChainNode<T> Node;

    typedef CircularListWithHeader<T> CircularList;
    typedef CircularListWithHeader<T> *CircularPointer;

private:
    NodePointer nodeHeader;//头节点指针
    int listSize;//节点个数

public:
    //不构造首节点只构造头节点的构造函数
    explicit CircularListWithHeader() : listSize(0) {
        nodeHeader = new Node(nodeHeader);
    }

    //构造首节点的构造函数，可指定首节点的元素值和头节点的地址
    explicit CircularListWithHeader(const T &theElement, NodePointer p = new Node) : nodeHeader(p), listSize(1) {
        nodeHeader->next = new Node(theElement, nodeHeader);
    }

    //指定头节点和首节点地址的构造函数，在需要首节点元素值时使用
    explicit CircularListWithHeader(const T &theElement, NodePointer header, NodePointer headNode = new Node) : nodeHeader(header), listSize(1) {
        nodeHeader->next = headNode;
        headNode->element = theElement;
        headNode->next = nodeHeader;
    }

    //指定头节点和首节点地址的构造函数，在不需要提供首届点元素值时使用
    explicit CircularListWithHeader(NodePointer header, NodePointer headNode) : nodeHeader(header), listSize(1) {
        nodeHeader->next = headNode;
        headNode->next = nodeHeader;
    }

    //只需要指定首节点的构造函数
    explicit CircularListWithHeader(NodePointer headNode) {
        nodeHeader = new Node(headNode);
        headNode->next = nodeHeader;
        listSize = 1;
    }

    //构造具有newSize个节点的链表，然后将链表的所有元素都设为theElement
    CircularListWithHeader(const T theElement, const int &newSize) {
        nodeHeader = new Node;
        NodePointer p = nodeHeader;
        for (int i = 0; i < newSize; i++) {
            p->next = new Node(theElement, nodeHeader);
            p = p->next;
        }
        listSize = newSize;
    }

    //拷贝构造函数
    CircularListWithHeader(const CircularListWithHeader<T> &theChainList) {
        if (theChainList.size() == 0) {
            //链表theChainList为空，不需要复制构造
            nodeHeader = new Node;
            nodeHeader->next = nodeHeader;
            listSize = 0;
        } else {
            listSize = theChainList.size();
            nodeHeader = new Node;
            NodePointer sourceNode = &(theChainList.getNode(0));//sourceNode指向被拷贝链表的首节点
            nodeHeader->next = new Node(sourceNode->element, nodeHeader);
            sourceNode = sourceNode->next;
            NodePointer targetNode = nodeHeader->next;
            while (sourceNode != theChainList.nodeHeader) {
                targetNode->next = new Node(sourceNode->element, nodeHeader);
                targetNode = targetNode->next;
                sourceNode = sourceNode->next;
            }
        }
    }

    //析构函数
    ~CircularListWithHeader() {
        NodePointer p = nodeHeader->next;
        NodePointer deleteNode = nullptr;
        while (p != nodeHeader) {
            deleteNode = p;
            p = p->next;
            delete deleteNode;
        }
        delete nodeHeader;
    }


    //ADT方法

    //得到指定索引值的节点中的元素值
    virtual T get(const int &theIndex) const {
        checkIndex(theIndex, "get");
        NodePointer currentNode = nodeHeader->next;
        for (int i = 0; i < theIndex; i++) {
            currentNode = currentNode->next;
        }
        return currentNode->element;
    }

    //得到第一个节点元素值等于theElement的节点的索引值
    virtual int indexOf(const T &theElement) const {
        NodePointer currentNode = nodeHeader->next;
        int index = 0;
        while (currentNode->element != theElement) {
            currentNode = currentNode->next;
            index++;
        }
        if (currentNode == nodeHeader) {
            return -1;
        } else return index;
    }

    //判断容器是否为空
    [[nodiscard]] virtual bool empty() const {
        return this->listSize == 0;
    }

    //返回容器中元素的个数
    [[nodiscard]] virtual int size() const {
        return listSize;
    }

    //清空容器中所有的节点
    virtual void clear() {
        NodePointer p = nodeHeader->next;
        nodeHeader->next = nodeHeader;
        NodePointer deleteNode;
        while (p != nodeHeader) {
            deleteNode = p;
            p = p->next;
            delete deleteNode;
        }
        listSize = 0;
    }

    //删除指定索引的节点
    virtual void erase(const int &theIndex) {
        checkIndex(theIndex, "deleteTreeNode");
        NodePointer deleteNode;
        if (theIndex == 0 && listSize == 1) {
            deleteNode = nodeHeader->next;
            nodeHeader->next = nodeHeader;
        } else if (theIndex == 0 && listSize > 1) {
            deleteNode = nodeHeader->next;
            nodeHeader->next = nodeHeader->next->next;
        } else {
            NodePointer p = nodeHeader->next;
            for (int i = 0; i < theIndex - 1; i++)
                p = p->next;
            deleteNode = p->next;
            p->next = p->next->next;
        }
        listSize--;
        delete deleteNode;

    }

    //在指定索引的节点之前插入节点
    virtual void insert(const int &theIndex, const T &theElement) {
        checkIndex(theIndex, "insert");
        if (theIndex == 0) {
            if (listSize == 0)
                nodeHeader->next = new Node(theElement, nodeHeader);
            else nodeHeader->next = new Node(theElement, nodeHeader->next);
        } else {
            NodePointer p = nodeHeader->next;
            for (int i = 0; i < theIndex - 1; i++)
                p = p->next;
            p->next = new Node(theElement, p->next);
        }
        listSize++;

    }

    //输出所有节点元素值
    virtual void output(ostream &out) const {
        if (listSize == 0) {
            cout << "当前链表为空，无法输出" << endl;
            return;
        }
        for (NodePointer currentNode = nodeHeader->next; currentNode != nodeHeader; currentNode = currentNode->next) {
            out << currentNode->element << " ";
        }

    }

    //常规接口

    NodePointer getHeader() { return nodeHeader; }

    void push_back(const T &theElement) {
        NodePointer newNode = new Node(theElement, nodeHeader);
        if (listSize == 0)nodeHeader->next = newNode;
        else {
            NodePointer p = nodeHeader->next;
            for (int i = 0; i < listSize - 1; i++) {
                p = p->next;
            }
            p->next = newNode;
        }
        listSize++;


    }

    //将指定索引的节点的元素值设为theElement
    void setElement(const int &theIndex, const T &theElement) {
        checkIndex(theIndex, "replace");
        this->setElement(theIndex,theElement);
    }

    //移除两个指定索引之间的所有元素
    void removeRange(const int &beginIndex, const int &endIndex) {
        if (beginIndex >= 0 && beginIndex < endIndex && endIndex <= listSize - 1) {
            NodePointer pBegin = nodeHeader->next, pEnd = nodeHeader->next;
            for (int i = 0; i < beginIndex - 1; i++)
                pBegin = pBegin->next;
            for (int i = 0; i < endIndex - 1; i++)
                pEnd = pEnd->next;
            NodePointer p = pBegin->next, j = pEnd->next, deleteNode = nullptr;
            int count = endIndex - beginIndex + 1;
            pBegin->next = j->next;
            j->next = nullptr;
            while (p != nullptr) {
                deleteNode = p;
                p = p->next;
                delete deleteNode;
            }

            listSize -= count;
        } else {
            throw ExceptionSpace::IllegalParameterException("removeRange(const int &beginIndex, const int &endIndex)参数传递错误");
        }

    }

    //交换两个容器中节点
    void swapContainer(CircularListWithHeader<T> &theChain) {
        int tempSize = listSize;
        listSize = theChain.listSize;
        theChain.listSize = tempSize;

        NodePointer tempHeader;
        tempHeader = nodeHeader;
        nodeHeader = theChain.nodeHeader;
        theChain.nodeHeader = tempHeader;
    }

    //交换指定索引的两个节点的元素值
    void swapElement(const int &indexA, const int &indexB) {
        checkIndex(indexA, "replace");
        checkIndex(indexB, "replace");
        T temp = this->get(indexA);
        this->setElement(indexA,this->get(indexB));
        this->setElement(indexB,temp);

    }

    //将元素整体向左移动
    void leftShift(const int &offset) {
        NodePointer p = nodeHeader->next;
        NodePointer j = nodeHeader->next;
        for (int i = 0; i < offset - 1; i++) {
            p = p->next;
        }
        nodeHeader->next = p->next;
        p->next = nullptr;
        NodePointer deleteNode;
        while (j != nullptr) {
            deleteNode = j;
            j = j->next;
            delete deleteNode;
        }
        listSize -= offset;

    }

    //反转容器元素
    void reverse() {
        NodePointer p = nodeHeader->next;
        NodePointer first = p;
        NodePointer j = p->next;
        NodePointer temp = nullptr;
        while (j != nodeHeader) {
            temp = j->next;
            j->next = p;
            p = j;
            j = temp;
        }
        nodeHeader->next = p;
        first->next = nodeHeader;

    }

    //将传入的两个链表的元素交叉存入调用该函数的链表中，且不开辟新的空间，最后逻辑删除传入的两个链表
    void meld(CircularListWithHeader<T> &chainA, CircularListWithHeader<T> &chainB) {
        if (chainA.size() == 0 && chainB.size() == 0)return;

        NodePointer p = &chainA.getNode(0);
        NodePointer j = &chainB.getNode(0);
        NodePointer aBegin = chainA.getHeader();
        NodePointer bBegin = chainB.getHeader();

        while (p->next != aBegin) {
            p = p->next;
        }
        p->next = nullptr;
        while (j->next != bBegin) {
            j = j->next;
        }
        j->next = nullptr;

        p = aBegin->next;
        j = bBegin->next;
        NodePointer t, c, temp, temp2;
        t = c = temp = temp2 = nullptr;

        do {
            temp = p->next;
            t = p;
            p = p->next;
            temp2 = j->next;
            c = j;
            j = j->next;
            t->next = c;
            c->next = temp;
        } while (temp != nullptr && temp2 != nullptr);
        if (temp == nullptr && temp2 != nullptr)
            c->next = temp2;

        nodeHeader = aBegin;
        NodePointer begin = nodeHeader;
        while (begin->next != nullptr) {
            begin = begin->next;
        }
        begin->next = nodeHeader;

        listSize = chainA.size() + chainB.size();
        chainA.logicalClear();
        chainB.logicalClear();

    }

    //生成两个扩展链表a和b，a中包含c中索引为奇数的元素，b中包含c中其余的元素，这个方法不能改变c中的内存结构
    vector<CircularListWithHeader<T>> *split() {
        auto p = new vector<CircularListWithHeader<T>>;

        //首先处理两种特殊情况
        if (this->size() < 2)return nullptr;//当链表元素小于2时直接返回空指针
        if (this->size() == 2) {
            auto p1 = this->indexToAddress(0);
            auto p2 = this->indexToAddress(1);
            CircularListWithHeader c1(p1), c2(p2);
            p->push_back(c1);
            p->push_back(c2);
            this->logicalClear();
            return p;
        }

        //下面的这个算法将会把所有索引为偶数的元素向前提，使其紧挨在一起，而索引为奇数的元素将会以倒序排列在之后
        //举例：下面的算法会将这样的数组{2, 7, 8, 9, 3, 5, 4, 6, 1}变为{2, 8, 3, 4, 1, 6, 5, 9, 7}
        for (int x = 1; x + 1 <= listSize - 1; x++) {
            int i = x;
            while (i + 1 <= listSize - 1) {
                this->swapElement(i, i + 1);
                i += 2;
            }
        }

        int sizeA, sizeB;//sizeA是索引为偶数的元素的个数，sizeB是索引为奇数的元素的个数
        if (listSize % 2 == 0) { sizeA = listSize / 2; }
        else { sizeA = (listSize / 2) + 1; }
        sizeB = listSize - sizeA;

        //现在所有索引为偶数的元素都在前面，所有索引为奇数的元素都在后面（注意此时奇数序列是倒序，之后需要反转）
        //用指针分别划定索引值为偶数和奇数的区域段的开始和末尾
        NodePointer beginA = nodeHeader->next;//指向索引为偶数的序列的第一个元素
        NodePointer endA = this->indexToAddress(sizeA - 1);
        NodePointer beginB = this->indexToAddress(sizeA);//指向索引为奇数的序列的最后一个元素
        NodePointer endB = this->indexToAddress(listSize - 1);//指向索引为奇数的序列的第一个元素

        //将偶数区的元素拼接在新创建的链表中
        CircularListWithHeader listA;//保存偶数序列的链表
        NodePointer beginListA = listA.getHeader();
        beginListA->next = beginA;
        endA->next = beginListA;

        //将奇数区的元素拼接在新创建的链表中
        CircularListWithHeader listB;
        NodePointer beginListB = listB.getHeader();
        beginListB->next = beginB;
        endB->next = beginListB;

        //反转listB
        listB.reverse();

        p->push_back(listA);
        p->push_back(listB);
        return p;

    }

    void test() {
        cout << "暂无测试代码" << endl;
    }

    //按照插入排序法排列容器中的元素
    void insertSort() {

        for (int i = 1; i < this->size(); i++) {
            T t = this->get(i);
            int j = i - 1;
            while (j >= 0 && t < this->get(j)) {
                this->setElement(j + 1, this->get(j));
                j--;
            }
            this->setElement(j + 1, t);
        }

    }

    //按照选择排序法对容器中的元素进行排序
    void selectionSort() {
        for (int i = 0; i < this->size() - 1; i++) {
            int tempMin = i;
            for (int j = i + 1; j < this->size(); j++) {
                if (this->get(j) < this->get(tempMin))
                    tempMin = j;
            }
            this->swapElement(tempMin, i);
        }
    }

    //按照冒泡排序法对容器中的元素进行排序
    void bubbleSort() {
        for (int i = this->size(); i > 1 && this->bubble(i); i--);

    }

    //用覆盖的方式删除容器中的某一个链表节点
    void overwriteErase(const int &theIndex) {
        /*
         * 要删除链表中第一个节点，先把第二个节点的元素值覆盖到第一个节点，然后把第二个节点删除达到了
         * 删除第一个节点的目的
         * */
        checkIndex(theIndex, "deleteTreeNode");
        NodePointer theNode = this->indexToAddress(theIndex);
        theNode->element = theNode->next->element;
        NodePointer deleteNode = theNode->next;
        theNode->next = theNode->next->next;
        delete deleteNode;
    }

private:

    //返回指定索引的节点引用
    ChainNode<T> &getNode(const int &theIndex)const {
        NodePointer p = nodeHeader->next;
        for (int i = 0; i < theIndex; i++) {
            p = p->next;
        }
        return *p;
    }

    //将指定索引的元素值改为theElement，并将其指针域设为给定的地址
    void setNode(const int &theIndex, const T &theElement, NodePointer &theNext) {
        this->getNode(theIndex).element = theElement;
        this->getNode(theIndex).next = theNext;

    }

    //逻辑上清空链表元素，实际空间并未释放
    void logicalClear() {
        nodeHeader->next = nodeHeader;
        listSize = 0;
    }

    //强制设定链表元素个数，如果新链表元素个数大于原先链表元素个数则不需要删除任何元素
    //若新链表元素个数小于当前链表元素个数，则删除多余的链表节点
    void setSize(int newSize) {
        if (newSize < this->size() && newSize > 0) {
            NodePointer p = nodeHeader->next;
            NodePointer j = p->next;
            for (int i = 0; i < newSize - 1; i++) {
                j = j->next;
                p = p->next;
            }
            p->next = nodeHeader;
            //此时j指向的节点及其之后的所有节点都是要删除的节点
            ChainNode<T> *deleteNode = j;
            ChainNode<T> *currentNode = deleteNode;
            int count = 0;//记录删除节点的数量
            while (currentNode != nodeHeader) {
                currentNode = currentNode->next;
                delete deleteNode;
                deleteNode = currentNode;
                count++;
            }
            listSize -= count;
        } else {
            //向链表的后面补充新节点，所有新节点的值都设为0
            int newListSize = newSize - listSize;
            CircularListWithHeader circularList = new CircularListWithHeader<T>(0, newListSize);
            this->getNode(listSize - 1).next = circularList.indexToAddress(0);
            circularList.getNode(newListSize - 1).next = nodeHeader;
            listSize += newListSize;
            delete circularList.getHeader();
        }

    }

    void checkIndex(int theIndex, std::string actionType) const {
        //确保索引在窒执行特殊操作时，索引在正确的范围内
        if (actionType == "insert") {
            if (theIndex < 0 || theIndex > this->size()) {
                ostringstream s;
                s << "插入元素时，";
                if (theIndex < 0)s << "索引值不得<0" << endl;
                if (theIndex > this->size())s << "索引值不得>数组元素个数" << endl;
                throw ExceptionSpace::IllegalParameterException(s.str());
            }
        } else if (actionType == "deleteTreeNode" || actionType == "get" || actionType == "replace") {
            if (theIndex >= this->size()) {
                ostringstream s;
                if (actionType == "deleteTreeNode")
                    s << "删除元素时，索引值不得>=listSize" << endl;
                else if (actionType == "replace")s << "替换元素时，索引值不得>=listSize" << endl;
                else if (actionType == "get")s << "获取元素时，索引值不得>=listSize" << endl;
                throw ExceptionSpace::IllegalParameterException(s.str());
            }
        } else {
            ostringstream s;
            s << "checkIndex第二个参数传入不正确，未指定正确的操作类型" << endl;
            throw ExceptionSpace::IllegalParameterException(s.str());
        }
    }

    ChainNode<T> *indexToAddress(const int &theIndex) const {
        NodePointer p = nodeHeader->next;
        for (int i = 0; i < theIndex; i++)
            p = p->next;
        return p;

    }

    bool bubble(const int &n) {
        bool sorted = false;
        for (int i = 0; i < n; i++) {
            if (this->get(i) > this->get(i + 1)) {
                this->swapElement(i, i + 1);
                sorted = true;
            }
        }
        return sorted;

    }

    void addNode(const NodePointer &p) {
        p->next = nodeHeader;
        this->getNode(listSize - 1).next = p;
        listSize++;
    }

};

template<class T>
ostream &operator<<(ostream &out, const CircularListWithHeader<T> &chain) {
    chain.output(out);
    return out;
}
