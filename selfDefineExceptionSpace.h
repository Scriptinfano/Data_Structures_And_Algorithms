//�Զ����쳣���װ
#pragma once

#include <iostream>
#include <string_view>
#include <exception>

using namespace std;

namespace ExceptionSpace {
//TODO �������ÿ���Զ����쳣����࣬�����Ƿ��ڲ�ͬ�������ռ��У������ռ��ǿ���Ƕ�׵ģ�

    class IllegalParameterValue : public exception {
    private:
        string message;

    public:
        explicit IllegalParameterValue(string_view theMessage = "�Ƿ���������") : message(theMessage) {}

        const char *what() const noexcept override//��д���ຯ��
        {
            return message.c_str();
        }
    };

    class outOfBounds : public exception {
    protected:
        string message;
    public:
        explicit outOfBounds(string_view theMessage = "���ʳ�������") : message(theMessage) {}

        const char *what() const noexcept override {
            return message.c_str();
        }

    };

    class matrixIndexOutOfBounds : public outOfBounds {
    public:
        explicit matrixIndexOutOfBounds(string_view theMessage = "�����±����ô��󣬵��·��ʳ�������") : outOfBounds(theMessage) {}
    };

    class iteratorOutOfBounds : public outOfBounds {
    public:
        explicit iteratorOutOfBounds(string_view theMessage = "�����������ɷ��ʽ���") : outOfBounds(theMessage) {}
    };

    class matrixSizeMismatch : public exception {
    protected:
        string message;
    public:
        explicit matrixSizeMismatch(string_view theMessage = "�����С���ƥ��") : message(theMessage) {}

        const char *what() const noexcept override {
            return message.c_str();
        }
    };

    class matrixSizeMismatchOfPlus : public matrixSizeMismatch {
    public:
        explicit matrixSizeMismatchOfPlus(string_view theMessage = "ִ�о���ӷ�ʱ����������Ĵ�С��������ȫ��ͬ") : matrixSizeMismatch(
                theMessage) {}
    };

    class matrixSizeMismatchOfMultiply : public matrixSizeMismatch {
    public:
        explicit matrixSizeMismatchOfMultiply(string_view theMessage = "ִ�о���˷�ʱ����һ���������������͵ڶ������������������ͬ")
                : matrixSizeMismatch(
                theMessage) {}
    };

    class matrixSizeMismatchOfInitialize : public matrixSizeMismatch {
    public:
        explicit matrixSizeMismatchOfInitialize(string_view theMessage = "ִ�о����ʼ��ʱ������ľ������͵�ǰ�ľ����С�����ȫ��ͬ")
                : matrixSizeMismatch(
                theMessage) {}
    };

    class matrixSizeMismatchOfSubtraction : public matrixSizeMismatch {
    public:
        explicit matrixSizeMismatchOfSubtraction(string_view theMessage = "ִ�о������ʱ������ľ������͵�ǰ�ľ����С�����ȫ��ͬ")
                : matrixSizeMismatch(
                theMessage) {}

    };

    class uninitializedMatrix : public exception {
    private:
        string message;
    public:
        explicit uninitializedMatrix(string_view theMessage = "ʹ��δ��ʼ���ľ���ִ���˾�������") : message(theMessage) {}

        const char *what() const noexcept override {
            return message.c_str();
        }

    };

    class reInitializedMatrix : public exception {
    private:
        string message;
    public:
        explicit reInitializedMatrix(string_view theMessage = "�Ѿ���ʼ�����ľ������ٴγ�ʼ��") : message(theMessage) {}

        const char *what() const noexcept override {
            return message.c_str();
        }
    };

    class invalidMatrixValueSet : public exception {
    private:
        string message;
    public:
        explicit invalidMatrixValueSet(string_view theMessage = "�ı����������Ԫ�ص�ֵʱ���ܽ�����Ԫ����Ϊ�����������������") : message(theMessage) {}

        const char *what() const noexcept override {
            return message.c_str();
        }

    };

    class StackEmptyException : public exception {
    private:
        string message;
    public:
        explicit StackEmptyException(string_view theMessage = "ջΪ�գ��޷�ȡ��ջ��Ԫ��") : message(theMessage) {}

        const char *what() const noexcept override {
            return message.c_str();
        }
    };

    class InvalidStackInitializeException : public exception {
    private:
        string message;
    public:
        explicit InvalidStackInitializeException(string_view theMessage = "��ʼ���Զ���ջʱ��ջ�ĳ�ʼ����С�ڴ��������Ԫ�ظ���") : message(theMessage) {}

        const char *what() const noexcept override {
            return message.c_str();
        }
    };

    namespace LinkListExceptions {
        //�����е��쳣��
        class LinklistEmptyException : public logic_error {
        public:
            explicit LinklistEmptyException(const string &theMessage = "δ�ҵ�ָ��Ԫ��") : logic_error(theMessage) {}
        };

        class ElementNotFoundException : public logic_error {
        public:
            explicit ElementNotFoundException(const string &theMessage = "δ�ҵ�ָ��Ԫ��") : logic_error(theMessage) {}
        };

    }


}
