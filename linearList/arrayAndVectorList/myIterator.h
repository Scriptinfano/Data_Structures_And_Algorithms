#pragma once
using namespace std;
namespace mystd {
    template<class T>
    class iterator {
    protected:
        T *position;
    public:
        typedef typename std::random_access_iterator_tag iterator_category;
        typedef T value_type;
        typedef typename std::ptrdiff_t difference_type;
        typedef T *pointer;
        typedef T &reference;

        //构造函数
        iterator(T *theposition = 0) { position = theposition; }

        //拷贝构造
        iterator(const iterator<T> &theIterator) {
            position = theIterator.get();
        }


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
        iterator operator+(const int &n);

        iterator operator-(const int &n);

        iterator &operator+=(const int &n);

        iterator &operator-=(const int &n);


        //迭代器之间的算术元素
        difference_type operator-(const iterator& theIterator)const;

        //所有类型迭代器通用的关系运算符重载函数
        bool operator!=(const iterator &right) const { return position != right.get(); }

        bool operator==(const iterator &right) const { return position == right.get(); }

        //只有随机访问迭代器支持的关系运算符重载函数

        bool operator>(const iterator &right) const { return position > right.get(); }

        bool operator<(const iterator &right) const { return position < right.get(); }

        bool operator<=(const iterator &right) const { return position <= right.get(); }

        bool operator>=(const iterator &right) const { return position >= right.get(); }

        //赋值运算符重载
        iterator &operator=(const iterator &right) { position = right.get(); }

        //访问内部私有数据接口
        T *get() const { return position; }
    };
}


template<class T>
mystd::iterator<T> mystd::iterator<T>::operator+(const int &n) {
    T *target;
    target = position + n;
    return mystd::iterator<T>(target);
}

template<class T>
mystd::iterator<T> mystd::iterator<T>::operator-(const int &n) {
    T *target;
    target = position - n;
    return mystd::iterator<T>(target);
}

template<class T>
typename mystd::iterator<T>::difference_type mystd::iterator<T>::operator-(const iterator<T>& theIterator)const {
    difference_type distance = position - theIterator.position;
    return distance;
}

template<class T>
mystd::iterator<T> &mystd::iterator<T>::operator+=(const int &n) {
    position += n;
    return *this;
}

template<class T>
mystd::iterator<T> &mystd::iterator<T>::operator-=(const int &n) {
    position -= n;
    return *this;
}
