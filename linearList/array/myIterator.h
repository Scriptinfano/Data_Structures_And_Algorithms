#pragma once

namespace mystd
{
    template<class T>
    class iterator {
    protected:
        T* position;
    public:
        typedef std::bidirectional_iterator_tag iterator_category;
        typedef T value_type;
        typedef ptrdiff_t difference_type;
        typedef T *pointer;
        typedef T &reference;

        //���캯��
        iterator(T *theposition=0){position=theposition;}

        //�����ò�����
        T& operator*()const{return *position;}
        T* operator->()const{return &*position;}

        //��������ֵ����
        iterator& operator++(){++position;return *this;}//ǰ�õ���
        iterator operator++(int){iterator old=*this;--position;return old;}//���õ�����int��ռλ�������������������������غ���

        //�����Ƿ����
        bool operator!=(const iterator right)const{return position!=right.position;}
        bool operator==(const iterator right)const{return position==right.position;}



    };

}
