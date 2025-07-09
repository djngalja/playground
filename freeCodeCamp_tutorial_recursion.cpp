/*
Recursion in programming complete freeCodeCamp tutorial
https://youtu.be/IJDJ0kBx2LM?si=zaO9t1YXlnkJn6TU

The original Java code modified and rewritten in C++11 by Galina
July 2025
*/


#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>


// Reverse a string
std::string reverse_str(const std::string& input) {
    return input.empty() ? "" : reverse_str(input.substr(1)) + input.front();
}


// Check if a string is a palindrome
bool is_palindrome(const std::string& input) {
    if (input.empty() || input.size() == 1) {
        return true;
    }
    if (input.front() != input.back()) {
        return false;
    }
    return is_palindrome(input.substr(1, input.size() - 2));
}


// Decimal to binary converter (the additional function deals with edge cases)
std::string find_binary_rec(int decimal) {
    return decimal == 0 ? "" : find_binary_rec(decimal / 2) + std::to_string(decimal % 2);

}

std::string find_binary(int decimal) { // <-- Call this function
    if (decimal < 0) {
        throw std::invalid_argument("Received negative value");
    }
    if (decimal == 0) { return "0"; };
    return find_binary_rec(decimal);
}


// Calculate the sum of natural numbers
int summation(int input) {
    return input <= 1 ? input : input + summation(input - 1);
}


// DIVIDE AND CONQUER ALGORITHMS
// Binary search
int binary_search_rec(int target, const std::vector<int>& vec, int left, int right) {
    if (right < left) { return -1; }
    int mid = (left + right) / 2;
    if (target == vec[mid]) { return mid; }
    if (target > vec[mid]) {
        return binary_search_rec(target, vec, mid + 1, right);
    }
    return binary_search_rec(target, vec, left, mid - 1);
}

int binary_s(int target, const std::vector<int>& vec) { // <-- Call this function
    return binary_search_rec(target, vec, 0, vec.size() - 1);
}


// Non-optimized fibonacci
long fib(long n) {
    return n <= 1 ? n : fib(n - 1) + fib(n - 2);
}


// Merge sort
void merge_sorted(std::vector<int>& data, std::size_t first, std::size_t mid, std::size_t last) {
    std::vector<int> temp;
    std::size_t i {first};
    std::size_t j {mid + 1};
    while (i <= mid && j <= last) {
        if (data[i] <= data[j]) {
            temp.push_back(data[i++]);
        } else {
            temp.push_back(data[j++]);
        }
    }
    while (i <= mid) {
        temp.push_back(data[i++]);
    }
    while (j <= last) {
        temp.push_back(data[j++]);
    }
    std::copy(temp.begin(), temp.end(), data.begin() + first);
}

void merge_sort_rec(std::vector<int>& data, std::size_t first, std::size_t last) {
    if (first < last) {
        std::size_t mid = (first + last) / 2;
        merge_sort_rec(data, first, mid);
        merge_sort_rec(data, mid + 1, last);
        merge_sorted(data, first, mid, last);
    }
}

void merge_sort(std::vector<int>& data) { // <-- Call this function
    if (data.size() <= 1) { return; }
    merge_sort_rec(data, 0, data.size() - 1);
}




int main() {
    std::vector test_vec {7, -1, 0, 13, 3, 9, 6, 23, 23, -4, 29, 15, 0};
    merge_sort(test_vec);
    for (int num : test_vec) { std::cout << num << ' '; }
    return 0;
}
