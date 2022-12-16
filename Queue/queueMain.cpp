#include "arrayQueue.h"
#include "LinkedQueue.h"
#include <iostream>
#include <ctime>

using namespace std;

template<class T>
void outputQueue(queue<T> &theQueue) {
    T *arr = new T[theQueue.size()];
    for (int i = 0; i < theQueue.size(); i++) {
        arr[i] = theQueue.pop_catch();
        theQueue.push(arr[i]);
    }
    for (int i = 0; i < theQueue.size(); i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void testLinkQueue() {
    LinkedQueue<int> link;
    link.push(12);
    link.push(31);
    link.push(41);
    link.push(87);
    outputQueue(link);
}

void testArrayQueue() {
    ArrayQueue<int> arrayQueue(5);

    try {
        arrayQueue.push_infinite(12);
        arrayQueue.push_infinite(13);
        arrayQueue.push_infinite(154);
        arrayQueue.push_infinite(1534);
        arrayQueue.push_infinite(1532);
        arrayQueue.push_infinite(5213);
        arrayQueue.push_infinite(11513);
        arrayQueue.push_infinite(513);
        arrayQueue.push_infinite(14);
        arrayQueue.push_infinite(151332);
        arrayQueue.push_infinite(52123);
        arrayQueue.push_infinite(11513);
        arrayQueue.push_infinite(513);
        arrayQueue.push(16);
        arrayQueue.push(16);
        arrayQueue.push(16);
        arrayQueue.push(16);
        arrayQueue.push(16);
        arrayQueue.push(16);
        arrayQueue.push(16);
        arrayQueue.push(16);
        arrayQueue.push(16);
        arrayQueue.push(16);
        arrayQueue.push(16);
        arrayQueue.push(16);

    } catch (QueueFullException &e) {
        cout << e.what() << endl;
        cout << "当前队列容量=" << arrayQueue.capacity() << endl;
        cout << "输出队列中的所有元素：" << endl;
        outputQueue(arrayQueue);

    }
}


//如果link比array慢，则返回true
bool compareArrayQueueAndLinkedQueue() {
    LinkedQueue<int> linkQueue;
    ArrayQueue<int> arrayQueue(10);

    clock_t start = clock();
    for (int i = 0; i < 1000000; i++) {
        linkQueue.push(i);
    }
    for (int i = 0; i < 1000000; i++) {
        linkQueue.pop();
    }

    clock_t end = clock();
    clock_t result = end - start;
    cout << "linkQueue花费时间：" << result << endl;

    clock_t start2 = clock();
    for (int i = 0; i < 1000000; i++) {
        arrayQueue.push_infinite(i);
    }
    for (int i = 0; i < 1000000; i++) {
        arrayQueue.pop_catch();
    }
    clock_t end2 = clock();
    clock_t result2 = end2 - start2;
    cout << "arrayQueue共花费时间：" << result2 << endl;

    return result > result2;

//经过实验之后，数组实现的队列的效率更高
}

int main() {
    bool result = compareArrayQueueAndLinkedQueue();
    cout << boolalpha << result;

    return 0;
}