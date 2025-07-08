/*
Recursion in programming complete freeCodeCamp tutorial
https://youtu.be/IJDJ0kBx2LM?si=zaO9t1YXlnkJn6TU

The original Java code modified and rewritten in C++11 by Galina
July 2025
*/


#include <iostream>
#include <string>
#include <vector>
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
    if (n == 0) { return 0; }
    if (n == 1) { return 1; }
    return fib(n - 1) + fib(n - 2);
}




int main() {
    std::vector test_vec {-4, -1, 0, 0, 3, 6, 12, 23, 23, 26, 29, 30};
    std::cout << binary_s(29, test_vec) << '\n';
    std::cout << find_binary(50) << '\n';
    std::cout << reverse_str("hello world") << '\n';
    return 0;
}
