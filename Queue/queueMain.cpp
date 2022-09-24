#include "arrayQueue.h"
#include "LinkedQueue.h"
#include <iostream>

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
        cout << e.what()<<endl;
        cout << "当前队列容量=" << arrayQueue.capacity() << endl;
        cout << "输出队列中的所有元素：" << endl;
        outputQueue(arrayQueue);

    }
}

int main() {
    testArrayQueue();
    return 0;
}