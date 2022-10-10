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
public:
    BinaryTreeNode(){
        leftChild=rightChild= nullptr;
    }
    BinaryTreeNode(const T&theElement){
        element=theElement;
        leftChild=rightChild= nullptr;
    }
    BinaryTreeNode(T element, const BinaryTreeNode<T> *leftChild, const BinaryTreeNode<T> *rightChild) : element(element), leftChild(leftChild), rightChild(rightChild) {}

    T getElement() const {
        return element;
    }

    const BinaryTreeNode<T> *getLeftChild() const {
        return leftChild;
    }

    const BinaryTreeNode<T> *getRightChild() const {
        return rightChild;
    }
};
