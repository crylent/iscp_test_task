#include <iostream>
#include <chrono>

#define N 10000000

template<typename T>
class LinkedRingBuffer {
public:
    LinkedRingBuffer(int capacity = 10) {
        mCapacity = capacity;
        mFirst = new Container();
        Container* curr = mFirst;
        for (int i = 0; i < mCapacity - 1; i++) {
            Container* next = new Container();
            curr->next = next;
            curr = next;
        }
        curr->next = mFirst;
        mLast = curr;
    }

    ~LinkedRingBuffer() {
        Container* next = mFirst;
        for (int i = 0; i < mCapacity - 1; i++) {
            Container* curr = next;
            next = curr->next;
            delete curr;
        }
        delete next;
    }

    void push(T item) {
        mLast = mLast->next;
        if (!mFirst->item) { // buffer is empty
            mFirst = mLast;
        }
        else if (mLast == mFirst) { // buffer is full
            mFirst = mFirst->next;
        }
        mLast->item = item;
    }

    T pop() {
        T item = mFirst->item;
        mFirst->item = {};
        mFirst = mFirst->next;
        return item;
    }

    int capacity() {
        return mCapacity;
    }

private:
    struct Container {
        Container* next;
        T item;
    };

    Container* mFirst;
    Container* mLast;

    int mCapacity = 0;
};

static int k = 0;

template<typename T>
void push_n_times(LinkedRingBuffer<T>& buffer, int n) {
    for (int i = 1; i <= n; i++) {
        buffer.push(i + k);
    }
    k += n;
}

template<typename T>
void pop_n_times(LinkedRingBuffer<T>& buffer, int n) {
    for (int i = 1; i <= n; i++) {
        buffer.pop();
    }
}

void main() {
    auto start = std::chrono::high_resolution_clock::now();
    auto buffer = LinkedRingBuffer<int>(N);
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