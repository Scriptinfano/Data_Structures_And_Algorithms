#pragma once

//��������ڵ���
template<class T>
class ChainNode {
public:
    T element;//����ڵ��������
    ChainNode<T> *next;//����ڵ��ָ����

    //������δ֪��ָ������ȷ�Ĺ��캯��
    ChainNode() = default;

    ChainNode(ChainNode<T> *theNext) : element(*(new T)), next(theNext) {}

    //ָ���������ָ����ı�׼���캯��
    ChainNode(const T &theElement, ChainNode<T> *theNext = nullptr) : element(theElement), next(theNext) {}

};

//����˫��ѭ������ڵ�
template<class T>
class DoublyNode {
public://����
    using pointer = DoublyNode<T> *;
    using node = DoublyNode<T>;
private://˽�г�Ա
    T element;
    pointer previous;
    pointer next;
public://�����������뿽�����캯��
    DoublyNode(const pointer&thePrevious,const T&theElement,const pointer &theNext):previous(thePrevious),element(theElement),next(theNext){}
    DoublyNode()=default;
    DoublyNode(const node&theNode){
        const pointer thePrevious=theNode.getPrevious();
        const T theElement=theNode.getElement();
        const pointer theNext=theNode.getNext();
        this->set(thePrevious, theElement, theNext);
    }
public://���нӿ�
    void setPrevious(const pointer &thePrevious){ previous=thePrevious;}
    void setNext(const pointer &theNext){next=theNext;}
    void setElement(const T&theElement){element=theElement;}
    void set(const pointer &thePrevious, const T &theElement, const pointer &theNext)
    {
        next=theNext;
        element=theElement;
        previous=thePrevious;
    }
    //��ֵ�ķ�ʽ���س�Ա
    pointer getNext()const{return next;}
    pointer getPrevious()const{return previous;}
    T getElement()const{return element;}

    //�����õķ�ʽ���س�Ա
    pointer &theNext(){return next;}
    pointer &thePrevious(){return previous;}
    T& theElement(){return element;}

};

//������������ĳ������
template<class T>
class LinearList {
public:
    virtual ~LinearList() {}                                 //�յ�����������
    virtual bool empty() const = 0;                          //��������Ƿ�Ϊ��
    virtual int size() const = 0;                            //����������Ԫ�ص�����
    virtual int indexOf(const T &theElement) const = 0;      //�����������ã����ظö����������е�����ֵ
    virtual T get(const int &index)const= 0;                     //��������ֵΪindex�Ķ���
    virtual void erase(const int &index) = 0;                       //ɾ������Ϊindex�Ķ���
    virtual void insert(const int &index, const T &theElement) = 0; //������index���ĺ�һ��λ�ò���Ԫ��
    virtual void output(std::ostream &out) const = 0;        //���Ԫ��
    virtual void clear() = 0;

};

//Ϊ����extendedChain�ඨ�������࣬�˳������˽��������
template<class T>
class extendedLinearList : private LinearList<T> {
public:
    virtual ~extendedLinearList() {}

    virtual void push_back(const T &theElement) = 0;

};
