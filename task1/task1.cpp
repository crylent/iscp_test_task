#include <math.h>
#include <iostream>
#include <chrono>
#include <functional>

// Хорошая функция, минусов нет
bool is_even(int value) {
    return value % 2 == 0;
}

// По времени НАМНОГО хуже
bool is_even_2(int value) {
    return remainder(value, 2) == 0;
}

// По времени плюс-минус так же, по читаемости кода хуже
bool is_even_3(int value) {
    return !(value & 1);
}

// Ещё хуже по читаемости...
bool is_even_4(int value) {
    return (value >> 1 << 1) == value;
}

void test(std::function<void(int)> f) {
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 10000; i++) {
        f(std::rand());
    }
    auto finish = std::chrono::high_resolution_clock::now();
    std::cout << "\n" << (finish - start).count();
}

void main() {
    test(&is_even);
    test(&is_even_2);
    test(&is_even_3);
    test(&is_even_4);
}