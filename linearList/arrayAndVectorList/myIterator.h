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

        //������֮�������Ԫ��
        difference_type operator-(reference theIterator);

        //�������͵�����ͨ�õĹ�ϵ��������غ���
        bool operator!=(const iterator right) const { return position != right.position; }

        bool operator==(const iterator right) const { return position == right.position; }

        //ֻ�����������ʵ�����֧�ֵ����������������غ���
        T &operator[](int i);

        //ֻ��������ʵ�����֧�ֵĹ�ϵ��������غ���

        bool operator>(const iterator right)const{return position>right.position;}

        bool operator<(const iterator right)const{return position<right.position;}

        bool operator<=(const iterator right)const{return position<=right.position;}

        bool operator>=(const iterator right)const{return position>=right.position;}

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

template<class T>
typename mystd::iterator<T>::difference_type mystd::iterator<T>::operator-(reference theIterator) {
    difference_type distance= position-theIterator.position;
    return distance;
}


template<class T>
T &mystd::iterator<T>::operator[](int i) {
    position+=i;
    return *position;
}
