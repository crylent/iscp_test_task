#include <iostream>
#include <chrono>

#define N 10000000

template<typename T>
class LinkedQueue {
public:
    ~LinkedQueue() {
        while (mSize > 0) pop();
    }

    void push(T item) {
        auto second = mFirst;
        mFirst = new Container();
        mFirst->item = item;
        mFirst->next = second;
        if (mSize > 0) second->prev = mFirst;
        else mLast = mFirst;
        mSize++;
    }

    T pop() {
        T item = mLast->item;
        mLast = mLast->prev;
        mSize--;
        if (mSize > 0) {
            delete mLast->next;
            mLast->next = nullptr;
        }
        else {
            delete mFirst;
            mFirst = nullptr;
        }
        return item;
    }

    int size() {
        return mSize;
    }

private:
    struct Container {
        Container* next;
        Container* prev;
        T item;
    };

    Container* mFirst;
    Container* mLast;

    int mSize = 0;
};

void main() {
    auto start = std::chrono::high_resolution_clock::now();
    auto queue = LinkedQueue<int>();
    for (int i = 0; i < N; i++) {
        queue.push(i);
    }
    for (int i = 0; i < N; i++) {
        queue.pop();
    }
    auto finish = std::chrono::high_resolution_clock::now();
    std::cout << (finish - start).count();
}