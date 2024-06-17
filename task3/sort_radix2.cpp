#include <vector>
#include <cmath>
#include <iostream>
#include <chrono>

using intarray = std::vector<int>;

int get_digit(int number, int i) {
    return number & (1 << i);
}

void partial_sort(intarray& arr, int i, int elem_from, int elem_to) {
    int capacity = elem_to - elem_from + 1;
    auto digit0 = intarray();
    auto digit1 = intarray();
    digit0.reserve(capacity);
    digit1.reserve(capacity);
    for (int j = elem_from; j <= elem_to; j++) {
        int n = arr[j];
        if (get_digit(n, i)) digit1.push_back(n);
        else digit0.push_back(n);
    }
    int count0 = digit0.size();
    int count1 = digit1.size();

    if (count0 > 0) std::copy(digit0.begin(), digit0.end(), arr.begin() + elem_from);
    if (count1 > 0) std::copy(digit1.begin(), digit1.end(), arr.begin() + elem_from + count0);

    if (i == 0) return;

    if (count0 > 1) partial_sort(arr, i - 1, elem_from, elem_from + count0 - 1);
    if (count1 > 1) partial_sort(arr, i - 1, elem_from + count0, elem_to);
}

void sort(intarray& arr) {
    int max = INT32_MIN;
    for (int n: arr) {
        if (n > max) max = n;
    }
    int most_significant = std::floor(std::log2(max)) + 1;
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