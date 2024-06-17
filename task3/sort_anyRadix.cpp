#include <vector>
#include <cmath>
#include <iostream>
#include <chrono>

#define RADIX 10

using intarray = std::vector<int>;

int get_digit(int number, int i) {
    return (number / (int) std::round(std::pow(RADIX, i))) % RADIX;
}

void partial_sort(intarray& arr, int i, int elem_from, int elem_to) {
    intarray by_digit[RADIX];
    for (int j = elem_from; j <= elem_to; j++) {
        int n = arr[j];
        int digit = get_digit(n, i);
        by_digit[digit].push_back(n);
    }

    int k = 0;
    for (int digit = 0; digit < RADIX; digit++) {
        auto digit_k = by_digit[digit];
        int len = digit_k.size();
        if (len > 0) std::copy(digit_k.begin(), digit_k.end(), arr.begin() + elem_from + k);
        k += len;
    }

    if (i == 0) return;

    k = 0;
    for (int digit = 0; digit < RADIX; digit++) {
        int len = by_digit[digit].size();
        if (len > 1) partial_sort(arr, i - 1, elem_from + k, elem_from + k + len - 1);
        k += len;
    }
}

void sort(intarray& arr) {
    int max = INT32_MIN;
    for (int n: arr) {
        if (n > max) max = n;
    }
    int most_significant = std::floor(std::log2(max) / std::log2(RADIX)) + 1;
    partial_sort(arr, most_significant, 0, arr.size() - 1);
}

void main() {
    auto start = std::chrono::high_resolution_clock::now();
    intarray arr { 15, 745, 53, 88765, 56, 86, 8768, 513, 876, 51, 3, 86 };
    sort(arr);
    auto finish = std::chrono::high_resolution_clock::now();
    std::cout << (finish - start).count() << "\n";

    for (int i = 0; i < arr.size(); i++) {
        std::cout << arr[i] << " ";
    }
}