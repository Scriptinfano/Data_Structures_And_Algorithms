#pragma once

template<class T>
class linearList {
public:
    virtual ~linearList() {}                                  //�յ�����������
    virtual bool empty() const = 0;                          //��������Ƿ�Ϊ��
    virtual int size() const = 0;                            //����������Ԫ�ص�����
    virtual T &get(int index) const = 0;                     //��������ֵΪindex�Ķ���
    virtual int indexOf(const T &theElement) const = 0;      //�����������ã����ظö����������е�����ֵ
    virtual void erase(int index) = 0;                       //ɾ������Ϊindex�Ķ���
    virtual void insert(int index, const T &theElement) = 0; //������index���ĺ�һ��λ�ò���Ԫ��
    virtual void output(std::ostream &out) const = 0;        //���Ԫ��
};

//Ϊ����extendedChain�ඨ�������࣬�˳������˽��������
template<class T>
class extendedLinearList : private linearList<T> {
public:
    virtual ~extendedLinearList() {}

    virtual void clear() = 0;

    virtual void push_back(const T &theElement) = 0;

};
