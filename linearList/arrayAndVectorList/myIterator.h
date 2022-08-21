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

        //��������
        iterator(const iterator<T> &theIterator) {
            position = theIterator.get();
        }


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
        iterator operator+(const int &n);

        iterator operator-(const int &n);

        iterator &operator+=(const int &n);

        iterator &operator-=(const int &n);


        //������֮�������Ԫ��
        difference_type operator-(const iterator& theIterator)const;

        //�������͵�����ͨ�õĹ�ϵ��������غ���
        bool operator!=(const iterator &right) const { return position != right.get(); }

        bool operator==(const iterator &right) const { return position == right.get(); }

        //ֻ��������ʵ�����֧�ֵĹ�ϵ��������غ���

        bool operator>(const iterator &right) const { return position > right.get(); }

        bool operator<(const iterator &right) const { return position < right.get(); }

        bool operator<=(const iterator &right) const { return position <= right.get(); }

        bool operator>=(const iterator &right) const { return position >= right.get(); }

        //��ֵ���������
        iterator &operator=(const iterator &right) { position = right.get(); }

        //�����ڲ�˽�����ݽӿ�
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
