#pragma once
using namespace std;
namespace mystd {
    template<class T>
    class iterator {
    protected:
        T *position;
    public:
        typedef bidirectional_iterator_tag iterator_category;
        typedef T value_type;
        typedef ptrdiff_t difference_type;
        typedef T *pointer;
        typedef T &reference;

        //构造函数
        iterator(T *theposition = 0) { position = theposition; }

        //解引用操作符
        T &operator*() const { return *position; }

        T *operator->() const { return &*position; }

        //将迭代器向后挪一位
        iterator &operator++() {
            ++position;
            return *this;
        }//前置递增
        iterator operator++(int) {
            iterator old = *this;
            ++position;
            return old;
        }//后置递增，int起到占位的作用用以区分两个递增重载函数

        //将迭代器的位置向前挪一位
        iterator &operator--() {
            --position;
            return *this;
        }

        iterator operator--(int) {
            iterator old = *this;
            --position;
            return old;
        }

        //任意将迭代器向前或向后移动n个位置
        iterator operator+(int n);

        iterator operator-(int n);

        //测试是否相等
        bool operator!=(const iterator right) const { return position != right.position; }

        bool operator==(const iterator right) const { return position == right.position; }


    };
}


template<class T>
mystd::iterator<T> mystd::iterator<T>::operator+(int n) {
    T *target;
    target = position + n;
    return mystd::iterator<T>(target);
}

template<class T>
mystd::iterator<T> mystd::iterator<T>::operator-(int n) {
    T *target;
    target = position - n;
    return mystd::iterator<T>(target);
}
