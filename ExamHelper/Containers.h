//
// Created by 85378 on 5/7/2022.
//

#ifndef EXAMHELPER_CONTAINERS_H
#define EXAMHELPER_CONTAINERS_H


#include <stdexcept>

// note that this is a database, the queue owns the data
template<typename T, int maxSize>
class MyQueue {
protected:
    // require: T implements the copy assignment operator
    T items[maxSize];
    int head = 0; // index of first element
    int rear = 0; // rear is the index of the last element
    int count = 0; // number of elements

public:
    MyQueue() = default;

    int size() const { return count; }

    bool isEmpty() { return count == 0; }

    bool isFull() { return count == maxSize; }

    void enqueue(T const& item) {
        if (isFull()) {
            dequeue();
            enqueue(item);
            return;
        }
        ++count;
        items[rear] = item;
        rear = (rear + 1) % maxSize;
    }

    // should check if the queue is empty
    T dequeue() {
        if (isEmpty()) { throw std::runtime_error("queue is empty"); }
        T* item = &items[head];
        --count;
        head = (head + 1) % maxSize;
        return *item;
    }

    T& operator[](int index) {
        if (index < 0 || index >= maxSize) { throw std::runtime_error("index out of range"); }
        int real_index = (head + index) % maxSize;
        return items[real_index];
    }
};


template<typename T>
struct Node{
    T data;
    Node* next;
    explicit Node(T const& data) : data(data), next(nullptr) {}
    ~Node() = default;
};

// note that this is a database, the list owns the data
template<typename T, int maxSize>
class MyList {
protected:
    int count = 0;
    Node<T>* root = nullptr;

public:

    MyList() = default;

    int size() const { return count; }

    bool isEmpty() { return count == 0; }

    bool isFull() { return count == maxSize; }

    void push_back(T const& item) {
        if (isFull()) {
            remove(0);
            push_back(item);
            return;
        }
        ++count;
        Node<T>* new_node = new Node<T>(item);
        if (root == nullptr) {
            root = new_node;
        } else {
            auto cur = root;
            while (cur->next != nullptr) {
                cur = cur->next;
            }
            cur->next = new_node;
        }
    }

    void push_front(T const& item) {
        Node<T>* new_node = new Node<T>(item);
        new_node->next = root;
        root = new_node;
    }

    void remove(int index) {
        if (index < 0 || index >= size()) { throw std::runtime_error("index out of range"); }
        if (index == 0) {
            auto ptr = root;
            root = root->next;
            delete ptr;
        } else {
            int i = 1;
            auto pre = root;
            auto cur = pre->next;
            while (i < index) {
                pre = cur;
                cur = cur->next;
                ++i;
            }
            pre->next = cur->next;
            delete cur;
        }
        --count;
    }

    T& operator[](int index) {
        if (index < 0 || index >= size()) { throw std::runtime_error("index out of range"); }
        int i = 0;
        auto cur = root;
        while (i < index) {
            cur = cur->next;
            ++i;
        }
        return cur->data;
    }
};


/* This is part of my Roasty coursework and was prepared prior to the exam */
template<typename T>
class MyVector {
private:
    T* data = nullptr;
    size_t occupancy = 0;
    size_t capacity = 2;
    /* allocate a new heap area with copy of previous elements */
    void reNew(size_t newCapacity) {
        if (newCapacity < occupancy) { occupancy = newCapacity; }
        T* newData = new T[newCapacity];
        for (size_t i = 0; i < occupancy; i++) { newData[i] = std::move(data[i]); }
        delete [] data;
        data = newData;
        capacity = newCapacity;
    }

public:
    struct Iterator {
    private:
        T* tPtr;
    public:
        /* iterator constructor*/
        Iterator(T* ptr) : tPtr(ptr) {}
        /* operator overloading to make it behave like a common iterator */
        T& operator*() const { return *tPtr; }
        T* operator->() { return tPtr; }
        Iterator& operator++() { tPtr++; return *this; }
        Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }
        friend bool operator== (Iterator const& a, Iterator const& b) { return a.tPtr == b.tPtr; };
        friend bool operator!= (Iterator const& a, Iterator const& b) { return a.tPtr != b.tPtr; };
    };

    /* constructor and rule of 3 */
    MyVector() { reNew(capacity); }
    MyVector& operator=(MyVector const& otherVector) {
        this->occupancy = otherVector.occupancy;
        this->reNew(otherVector.capacity);
        for (size_t i = 0; i < occupancy; i++) {
            data[i] = otherVector.data[i];
        }
        return *this;
    }
    MyVector(MyVector const& otherVector) { *this = otherVector; }
    virtual ~MyVector() { delete [] data; }

    Iterator begin() const  { return Iterator(&data[0]); }
    Iterator end() const { return Iterator(&data[occupancy]); }

    /* copy and move, make it more efficient if possible */
    void push_back(T const& item) {
        if (occupancy >= capacity) { reNew(capacity*2); }
        data[occupancy++] = item;
    }
    void push_back(T&& item) {
        if (occupancy >= capacity) { reNew(capacity*2); }
        data[occupancy++] = std::move(item);
    }

    size_t size() const { return occupancy; }

    void remove(size_t index) {
        for (size_t i = index; i < occupancy-1; i++) { data[i] = data[i+1]; }
        occupancy--;
    }

    T const& operator[](size_t i) const {return data[i];}

    T& operator[](size_t i) {
        if (i >= occupancy) { throw std::out_of_range("Index out of range"); }
        return data[i];
    }
};





#endif //EXAMHELPER_CONTAINERS_H
