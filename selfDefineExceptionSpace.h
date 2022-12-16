//�Զ����쳣���װ
#pragma once

#include <iostream>
#include <string_view>
#include <exception>

using namespace std;

namespace ExceptionSpace {
    class IllegalParameterException : public exception {
    private:
        string message;

    public:
        explicit IllegalParameterException(string_view theMessage = "�Ƿ���������") : message(theMessage) {}

        [[nodiscard]] const char *what() const noexcept override//��д���ຯ��
        {
            return message.c_str();
        }
    };

    class ReinitializeException : public exception {
    private:
        string message;

    public:
        explicit ReinitializeException(string_view theMessage = "�Ƿ���������") : message(theMessage) {}

        [[nodiscard]] const char *what() const noexcept override//��д���ຯ��
        {
            return message.c_str();
        }

    };

    class OutOfBoundsException : public exception {
    protected:
        string message;
    public:
        explicit OutOfBoundsException(string_view theMessage = "���ʳ�������") : message(theMessage) {}

        const char *what() const noexcept override {
            return message.c_str();
        }

    };

    class IteratorOutOfBounds : public logic_error {
    public:
        explicit IteratorOutOfBounds(const string &theMessage = "������Խ���쳣") : logic_error(theMessage) {}
    };

    class FullContainerException : public logic_error {
    public:
        explicit FullContainerException(const string &theMessage = "���������쳣") : logic_error(theMessage) {}

    };

    class EmptyContainerException:public logic_error{
    public:
        explicit EmptyContainerException(const string &theMessage="����Ϊ�ա��޷�ִ����ز���"):logic_error(theMessage){}
    };


    namespace MatrixExceptionSpace {

        class matrixIndexOutOfBounds : public OutOfBoundsException {
        public:
            explicit matrixIndexOutOfBounds(string_view theMessage = "�����±����ô��󣬵��·��ʳ�������") : OutOfBoundsException(theMessage) {}
        };

        class iteratorOutOfBounds : public OutOfBoundsException {
        public:
            explicit iteratorOutOfBounds(string_view theMessage = "�����������ɷ��ʽ���") : OutOfBoundsException(theMessage) {}
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

        class MatrixUnInitializeException : public exception {
        private:
            string message;
        public:
            explicit MatrixUnInitializeException(string_view theMessage = "ʹ��δ��ʼ���ľ���ִ���˾�������") : message(theMessage) {}

            const char *what() const noexcept override {
                return message.c_str();
            }

        };

        class MatrixReinitializeException : public exception {
        private:
            string message;
        public:
            explicit MatrixReinitializeException(string_view theMessage = "�Ѿ���ʼ�����ľ������ٴγ�ʼ��") : message(theMessage) {}

            const char *what() const noexcept override {
                return message.c_str();
            }
        };

        class MatrixInvalidValueSetException : public exception {
        private:
            string message;
        public:
            explicit MatrixInvalidValueSetException(string_view theMessage = "�ı����������Ԫ�ص�ֵʱ���ܽ�����Ԫ����Ϊ�����������������") : message(theMessage) {}

            const char *what() const noexcept override {
                return message.c_str();
            }

        };

        class MatrixDynamicCastException : public exception {
        private:
            string message;
        public:
            explicit MatrixDynamicCastException(string_view theMessgae = "ִ�о�������ʱ���Ҳ�������ָ��δָ�������������ת��ʧ��") : message(theMessgae) {}

            const char *what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override {
                return message.c_str();
            }
        };

    }
    namespace QueueExceptionSpace {
        class QueueFullException:public FullContainerException{
        public:
            explicit QueueFullException(const string &theMessage="�����������޷�������κ�Ԫ��"):FullContainerException(theMessage){}
        };
        class QueueEmptyException:public EmptyContainerException{
        public :
            explicit QueueEmptyException(const string &theMessage="����Ϊ�գ��޷�ȡ����ͷԪ��"): EmptyContainerException(theMessage){}
        };
    }
    namespace DequeExceptionSpace {
        class DequeFullException:public FullContainerException{
        public:
            explicit DequeFullException(const string &theMessage="˫�˶����������޷�������κ�Ԫ��"):FullContainerException(theMessage){}
        };
        class DequeEmptyException:public EmptyContainerException{
        public :
            explicit DequeEmptyException(const string &theMessage="˫�˶���Ϊ�գ��޷�ȡ���κ�Ԫ��"): EmptyContainerException(theMessage){}
        };
    }

    namespace StackExceptionSpace {
        class StackFullException : public FullContainerException {
        public:
            explicit StackFullException(const string &theMessage = "ջ�Ѿ����ˣ��޷�������κ�Ԫ��") : FullContainerException(theMessage) {}
        };

        class StackEmptyException : public EmptyContainerException {
        public:
            explicit StackEmptyException(const string& theMessage = "ջΪ�գ��޷�ȡ��ջ��Ԫ��") : EmptyContainerException(theMessage) {}
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

        class ReinitializeStackException : public logic_error {
        public:
            explicit ReinitializeStackException(const string &theMessage = "ջ�ظ���ʼ�����뽫ջ���֮�����³�ʼ��") : logic_error(theMessage) {}
        };

        class VectorEmptyException : public logic_error {
        public:
            explicit VectorEmptyException(const string &theMessage = "������ʼ��ջ��vector����Ϊ�գ����ȳ�ʼ��vector����") : logic_error(theMessage) {}
        };


    }

    namespace LinkListExceptionSpace {
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

    namespace ArrayListExceptionSpace {
        class ArrayListEmptyException : public EmptyContainerException {
        public:
            explicit ArrayListEmptyException(const string &theMessage = "ArrayListΪ�գ��޷����") : EmptyContainerException(theMessage) {}

        };
    }
}
