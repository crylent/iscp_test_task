#include <iostream>
#include <chrono>

#define N 10000000

template<typename T>
class ArrayQueue {
public:
    ArrayQueue(int capacity = 10) {
        mCapacity = capacity;
        mItems = new T[capacity];
    }

    ~ArrayQueue() {
        delete[] mItems;
    }

    void push(T item) {
        if (mSize >= mCapacity) ensure_capacity(mCapacity * 2);
        mSize++;
        mLast++;
        if (mLast >= mCapacity) mLast = 0;
        mItems[mLast] = item;
    }

    T pop() {
        mSize--;
        mFirst++;
        if (mFirst >= mCapacity) {
            mFirst = 0;
            return mItems[mCapacity - 1];
        }
        return mItems[mFirst - 1];
    }

    int size() {
        return mSize;
    }

    void ensure_capacity(int capacity) {
        if (capacity < mSize) {
            throw std::invalid_argument("Insufficient capacity specified");
        }

        T* old = mItems;
        mItems = new T[capacity];
        if (mLast >= mFirst) {
            std::copy(old + mFirst, old + mLast + 1, mItems);
        } else {
            std::copy(old + mFirst, old + mCapacity, mItems);
            std::copy(old, old + mLast + 1, mItems + mCapacity - mFirst);
        }
        delete[] old;
        mCapacity = capacity;
        mFirst = 0;
        mLast = mSize - 1;
    }

private:
    T* mItems;
    
    int mCapacity;
    int mFirst = 0;
    int mLast = -1;
    int mSize = 0;
};

void main() {
    auto start = std::chrono::high_resolution_clock::now();
    auto queue = ArrayQueue<int>();
    for (int i = 0; i < N; i++) {
        queue.push(i);
    }
    for (int i = 0; i < N; i++) {
        int a = queue.pop();
        if (a != i) std::cout << i << " " << a << "\n";
    }
    auto finish = std::chrono::high_resolution_clock::now();
    std::cout << (finish - start).count();
}