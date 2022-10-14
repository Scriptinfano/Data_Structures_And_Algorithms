#pragma once
template<class T>
class BinaryTreeNode;
template<class T>
class BinaryTreeNode{
    using TreeNode = BinaryTreeNode<T>;
    using NodePointer = BinaryTreeNode<T>*;
private:
    T element;
    NodePointer leftChild;
    NodePointer rightChild;
    bool leftTag;
    bool rightTag;
public:
    BinaryTreeNode(){
        leftChild=rightChild= nullptr;
        leftTag=rightTag= false;
    }
    BinaryTreeNode(const T&theElement){
        element=theElement;
        leftChild=rightChild= nullptr;
        leftTag=rightTag= false;
    }
    BinaryTreeNode(T element, const BinaryTreeNode<T> *leftChild, const BinaryTreeNode<T> *rightChild) : element(element), leftChild(leftChild), rightChild(rightChild) {
        leftTag=rightTag= false;
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

    bool isLeftTag() const {
        return leftTag;
    }

    void setLeftTag(bool leftTag) {
        BinaryTreeNode::leftTag = leftTag;
    }

    bool isRightTag() const {
        return rightTag;
    }

    void setRightTag(bool theRightTag) {
        BinaryTreeNode::rightTag = theRightTag;
    }

    void setLeftChild(const BinaryTreeNode<T> *theLeftChild) {
        BinaryTreeNode::leftChild = theLeftChild;
    }

    void setRightChild(const BinaryTreeNode<T> *theRightChild) {
        BinaryTreeNode::rightChild = theRightChild;
    }
};
