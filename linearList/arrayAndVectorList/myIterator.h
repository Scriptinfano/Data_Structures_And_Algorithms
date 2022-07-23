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

        //���캯��
        iterator(T *theposition = 0) { position = theposition; }

        //�����ò�����
        T &operator*() const { return *position; }

        T *operator->() const { return &*position; }

        //�����������Ųһλ
        iterator &operator++() {
            ++position;
            return *this;
        }//ǰ�õ���
        iterator operator++(int) {
            iterator old = *this;
            ++position;
            return old;
        }//���õ�����int��ռλ�������������������������غ���

        //����������λ����ǰŲһλ
        iterator &operator--() {
            --position;
            return *this;
        }

        iterator operator--(int) {
            iterator old = *this;
            --position;
            return old;
        }

        //���⽫��������ǰ������ƶ�n��λ��
        iterator operator+(int n);

        iterator operator-(int n);

        //�����Ƿ����
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
