//自定义异常类封装
#pragma once

#include <iostream>
#include <string_view>
#include <exception>

using namespace std;

namespace ExceptionSpace {
//TODO 给下面的每个自定义异常类分类，将他们放在不同的命名空间中（命名空间是可以嵌套的）

    class IllegalParameterValue : public exception {
    private:
        string message;

    public:
        explicit IllegalParameterValue(string_view theMessage = "非法参数传递") : message(theMessage) {}

        const char *what() const noexcept override//重写父类函数
        {
            return message.c_str();
        }
    };

    class outOfBounds : public exception {
    protected:
        string message;
    public:
        explicit outOfBounds(string_view theMessage = "访问超出界限") : message(theMessage) {}

        const char *what() const noexcept override {
            return message.c_str();
        }

    };

    class matrixIndexOutOfBounds : public outOfBounds {
    public:
        explicit matrixIndexOutOfBounds(string_view theMessage = "矩阵下标引用错误，导致访问超出界限") : outOfBounds(theMessage) {}
    };

    class iteratorOutOfBounds : public outOfBounds {
    public:
        explicit iteratorOutOfBounds(string_view theMessage = "迭代器超出可访问界限") : outOfBounds(theMessage) {}
    };

    class matrixSizeMismatch : public exception {
    protected:
        string message;
    public:
        explicit matrixSizeMismatch(string_view theMessage = "矩阵大小规格不匹配") : message(theMessage) {}

        const char *what() const noexcept override {
            return message.c_str();
        }
    };

    class matrixSizeMismatchOfPlus : public matrixSizeMismatch {
    public:
        explicit matrixSizeMismatchOfPlus(string_view theMessage = "执行矩阵加法时，两个矩阵的大小规格必须完全相同") : matrixSizeMismatch(
                theMessage) {}
    };

    class matrixSizeMismatchOfMultiply : public matrixSizeMismatch {
    public:
        explicit matrixSizeMismatchOfMultiply(string_view theMessage = "执行矩阵乘法时，第一个矩阵的列数必须和第二个矩阵的行数必须相同")
                : matrixSizeMismatch(
                theMessage) {}
    };

    class matrixSizeMismatchOfInitialize : public matrixSizeMismatch {
    public:
        explicit matrixSizeMismatchOfInitialize(string_view theMessage = "执行矩阵初始化时，传入的矩阵必须和当前的矩阵大小规格完全相同")
                : matrixSizeMismatch(
                theMessage) {}
    };

    class matrixSizeMismatchOfSubtraction : public matrixSizeMismatch {
    public:
        explicit matrixSizeMismatchOfSubtraction(string_view theMessage = "执行矩阵减法时，传入的矩阵必须和当前的矩阵大小规格完全相同")
                : matrixSizeMismatch(
                theMessage) {}

    };

    class uninitializedMatrix : public exception {
    private:
        string message;
    public:
        explicit uninitializedMatrix(string_view theMessage = "使用未初始化的矩阵执行了矩阵运算") : message(theMessage) {}

        const char *what() const noexcept override {
            return message.c_str();
        }

    };

    class reInitializedMatrix : public exception {
    private:
        string message;
    public:
        explicit reInitializedMatrix(string_view theMessage = "已经初始化过的矩阵不能再次初始化") : message(theMessage) {}

        const char *what() const noexcept override {
            return message.c_str();
        }
    };

    class invalidMatrixValueSet : public exception {
    private:
        string message;
    public:
        explicit invalidMatrixValueSet(string_view theMessage = "改变特殊矩阵中元素的值时不能将零区元素设为除了零以外的其他数") : message(theMessage) {}

        const char *what() const noexcept override {
            return message.c_str();
        }

    };

    class StackEmptyException : public exception {
    private:
        string message;
    public:
        explicit StackEmptyException(string_view theMessage = "栈为空，无法取得栈顶元素") : message(theMessage) {}

        const char *what() const noexcept override {
            return message.c_str();
        }
    };

    class InvalidStackInitializeException : public exception {
    private:
        string message;
    public:
        explicit InvalidStackInitializeException(string_view theMessage = "初始化自定义栈时，栈的初始容量小于传入的容器元素个数") : message(theMessage) {}

        const char *what() const noexcept override {
            return message.c_str();
        }
    };

    namespace LinkListExceptions {
        //链表中的异常类
        class LinklistEmptyException : public logic_error {
        public:
            explicit LinklistEmptyException(const string &theMessage = "未找到指定元素") : logic_error(theMessage) {}
        };

        class ElementNotFoundException : public logic_error {
        public:
            explicit ElementNotFoundException(const string &theMessage = "未找到指定元素") : logic_error(theMessage) {}
        };

    }


}
