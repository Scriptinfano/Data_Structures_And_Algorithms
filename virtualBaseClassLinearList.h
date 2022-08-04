#pragma once

//��������ڵ���
template<class T>
class ChainNode {
public:
    T element;//����ڵ��������
    ChainNode<T> *next;//����ڵ��ָ����

    //������δ֪��ָ������ȷ�Ĺ��캯��
    ChainNode()=default;

    ChainNode(const ChainNode<T> *theNext) : element(new T),next(theNext) {}

    //ָ���������ָ����ı�׼���캯��
    ChainNode(const T &theElement,ChainNode<T> *theNext = nullptr) : element(theElement),next(theNext) {}

};

template<class T>
class LinearList {
public:
    virtual ~LinearList() {}                                 //�յ�����������
    virtual bool empty() const = 0;                          //��������Ƿ�Ϊ��
    virtual int size() const = 0;                            //����������Ԫ�ص�����
    virtual int indexOf(const T &theElement) const = 0;      //�����������ã����ظö����������е�����ֵ
    virtual T &get(const int &index) const = 0;                     //��������ֵΪindex�Ķ���
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
