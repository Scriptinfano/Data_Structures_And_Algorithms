#pragma once

template<class T>
class BinaryTreeNode;

template<class T>
class BinaryTreeNode {
    using TreeNode = BinaryTreeNode<T>;
    using NodePointer = BinaryTreeNode<T> *;
private:
    T element;
    NodePointer leftChild;
    NodePointer rightChild;
    bool leftTag;
    bool rightTag;
public:
    BinaryTreeNode() {
        leftChild = rightChild = nullptr;
        leftTag = rightTag = false;
    }

    explicit BinaryTreeNode(const T &theElement) {
        element = theElement;
        leftChild = rightChild = nullptr;
        leftTag = rightTag = false;
    }

    BinaryTreeNode(T element, const BinaryTreeNode<T> *leftChild, const BinaryTreeNode<T> *rightChild) : element(element), leftChild(leftChild), rightChild(rightChild) {
        leftTag = rightTag = false;
    }

    T getElement() const {
        return element;
    }

    BinaryTreeNode<T> *getLeftChild() const {
        return leftChild;
    }

    BinaryTreeNode<T> *getRightChild() const {
        return rightChild;
    }

    BinaryTreeNode<T> *getLeftChild_nonConst() {
        return leftChild;
    }

    BinaryTreeNode<T> *getRightChild_nonConst() {
        return rightChild;
    }


    bool isLeftTag() const {
        return leftTag;
    }

    void setLeftTag(bool theLeftTag) {
        leftTag = theLeftTag;
    }

    bool isRightTag() const {
        return rightTag;
    }

    void setRightTag(bool theRightTag) {
        BinaryTreeNode<T>::rightTag = theRightTag;
    }

    void setLeftChild(BinaryTreeNode<T> *theLeftChild) {
        BinaryTreeNode<T>::leftChild = theLeftChild;
    }

    void setRightChild(BinaryTreeNode<T> *theRightChild) {
        BinaryTreeNode<T>::rightChild = theRightChild;
    }
};

template<class T>
class HuffmanTreeNode {
    using node = HuffmanTreeNode<T>;
    using nodePointer = HuffmanTreeNode<T> *;
private:
    T *element;
    nodePointer leftChild;
    nodePointer rightChild;
    nodePointer parent;
public:
    explicit HuffmanTreeNode(T element) {
        element = new T(element);
        leftChild = rightChild = parent = nullptr;
    }

    HuffmanTreeNode() {
        element = leftChild = rightChild = parent = nullptr;
    }

    virtual ~HuffmanTreeNode() {
        delete element;
        delete leftChild;
        delete rightChild;
        delete parent;
    }

    T getElement() const {
        return element;
    }

    const HuffmanTreeNode<T> *getLeftChild() const {
        return leftChild;
    }

    const HuffmanTreeNode<T> *getRightChild() const {
        return rightChild;
    }

    const HuffmanTreeNode<T> *getParent() const {
        return parent;
    }

    void setElement(T theElement) {
        element = theElement;
    }

    void setLeftChild(const HuffmanTreeNode<T> *theLeftChild) {
        leftChild = theLeftChild;
    }

    void setRightChild(const HuffmanTreeNode<T> *theRightChild) {
        rightChild = theRightChild;
    }

    void setParent(const HuffmanTreeNode<T> *theParent) {
        parent = theParent;
    }
};
