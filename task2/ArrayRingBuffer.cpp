#include <vector>
#include <iostream>
#include <chrono>

#define N 10000000

template<typename T>
class ArrayRingBuffer
{
public:
    ArrayRingBuffer(int capacity = 10) {
        mCapacity = capacity;
        mItems = new T[capacity]{};
    }

    ~ArrayRingBuffer() {
        delete[] mItems;
    }

    void push(T item) {
        increment(mLast);
        if (!mItems[mFirst]) { // buffer is empty ???
            mFirst = mLast;
        }
        else if (mLast == mFirst) { // buffer is full
            increment(mFirst);
        }
        mItems[mLast] = item;
    }

    T pop() {
        T item = mItems[mFirst];
        mItems[mFirst] = {};
        increment(mFirst);
        return item;
    }

    int capacity() {
        return mCapacity;
    }

private:
    T* mItems;
    
    int mCapacity;
    int mFirst = 0;
    int mLast = -1;

    void increment(int& n) {
        n++;
        if (n >= mCapacity) n = 0;
    }
};

static int k = 0;

template<typename T>
void push_n_times(ArrayRingBuffer<T>& buffer, int n) {
    for (int i = 1; i <= n; i++) {
        buffer.push(i + k);
    }
    k += n;
}

template<typename T>
void pop_n_times(ArrayRingBuffer<T>& buffer, int n) {
    for (int i = 1; i <= n; i++) {
        buffer.pop();
    }
}

void main() {
    auto start = std::chrono::high_resolution_clock::now();
    auto buffer = ArrayRingBuffer<int>(N);
    auto after_construct = std::chrono::high_resolution_clock::now();
    push_n_times(buffer, N);
    auto after_push = std::chrono::high_resolution_clock::now();
    pop_n_times(buffer, N);
    auto finish = std::chrono::high_resolution_clock::now();
    std::printf("Constructor: %lld\nPush: %lld\nPop: %lld",
        (int64_t) (after_construct - start).count(),
        (int64_t) (after_push - after_construct).count(),
        (int64_t) (finish - after_push).count()
    );
}