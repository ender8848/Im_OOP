#include <iostream>
#include "Containers.h"

void MyVectorTest();

using namespace std;

void MyQueueTest();

void MyListTest();;

int main() {
    cout << "******** MyQueueTest ********" << endl;
    MyQueueTest();
    cout << endl;
    cout << "******** MyVectorTest ********" << endl;
    MyVectorTest();
    cout << endl;
    cout << "******** MyListTest ********" << endl;
    MyListTest();
    cout << endl;
    return 0;
}


void MyQueueTest() {
    MyQueue<int, 2> queue;
    cout << "Queue is empty? --  " << queue.isEmpty() << endl;
    cout << "Queue is full ? --  " << queue.isFull() << endl;
    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);
    queue.enqueue(4);
    cout << "After enqueueing 4 elements..." << endl;
    cout << "Queue is empty? --  " << queue.isEmpty() << endl;
    cout << "Queue is full ? --  " << queue.isFull() << endl;
    cout << "Queue now has   --  " << queue.size() << " items" << endl;
    std::cout << "Dequeue: " << queue.dequeue() << std::endl;
    std::cout << "Dequeue: " << queue.dequeue() << std::endl;
    try {
        std::cout << "Dequeue now has exception: " << queue.dequeue() << std::endl;
    }  catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}

void MyVectorTest() {
    MyVector<int> vec;
    cout << "Vector now has size --  " << vec.size() << endl;
    vec.push_back(0);
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(4);
    cout << "After pushing 5 elements(0,1,2,3,4)..." << endl;
    cout << "Vector now has size --  " << vec.size() << endl;
    vec.remove(2);
    cout << "After removing element with index 2" << endl;
    cout << "vec[2] = " << vec[2] << endl;
    cout << "Vector now has size --  " << vec.size() << endl;
    try {
        cout << "vec[5] = " << vec[5] << endl;
    } catch (const std::exception &e) {
        cout << e.what() << endl;
    }
    cout << "try looping through my vector..." << endl;
    for (auto it = vec.begin(); it != vec.end(); it++) {
        cout << *it << " ";
    }
}

void MyListTest() {
    MyList<int, 3> list;
    cout << "List now has size --  " << list.size() << endl;
    list.push_back(0);
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    cout << "After pushing 4 elements(0,1,2,3)..." << endl;
    cout << "List now has size --  " << list.size() << endl;
    cout << "with elements..." << list[0] << " " << list[1] << " " << list[2] << endl;
    try {
        cout << "list[3] = " << list[3] << endl;
    } catch (const std::exception &e) {
        cout << e.what() << endl;
    }
    cout << "after removing the last 2 elements..." << endl;
    list.remove(1); // remove middle
    list.remove(1); // now remove last
    cout << "list[0] = " << list[0] << endl;
    try {
        cout << "list[1] = " << list[1] << endl;
    } catch (const std::exception &e) {
        cout << e.what() << endl;
    }
}