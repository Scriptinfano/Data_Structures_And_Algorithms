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

        //构造函数
        iterator(T *theposition=0){position=theposition;}

        //解引用操作符
        T& operator*()const{return *position;}
        T* operator->()const{return &*position;}

        //迭代器的值增加
        iterator& operator++(){++position;return *this;}//前置递增
        iterator operator++(int){iterator old=*this;--position;return old;}//后置递增，int起到占位的作用用以区分两个递增重载函数

        //测试是否相等
        bool operator!=(const iterator right)const{return position!=right.position;}
        bool operator==(const iterator right)const{return position==right.position;}



    };

}
