/*
Dynamic programming complete freeCodeCamp tutorial
https://www.youtube.com/watch?v=oBt53YbR9Kk

Rewritten in modern C++ by Galina
June 2025
*/

#include <iostream>
#include <map>

// Brute force
int fib(int);
long long grid_traveler(int, int);
// Memoization
int fib(int, std::map<int, int>&);
long long grid_traveler(int, int, std::map<std::string, long long>&);




int main() {
    std::map<std::string, long long> memo;
    std::cout << grid_traveler(18, 18, memo);


    return 0;
}


// Brute force
int fib(int n) {
    if (n == 0) { return 0; }
    if (n == 1) { return 1; }
    return fib(n - 1) + fib(n - 2);
}

long long grid_traveler(int r, int c) {
    if (r == 1 && c == 1) { return 1; }
    if (r == 0 || c == 0) { return 0; }
    return grid_traveler(r - 1, c) + grid_traveler(r, c - 1);
}

// Memoization
int fib(int n, std::map<int, int>& memo) {
    if (n == 0) { return 0; }
    if (n == 1) { return 1; }
    if (memo.find(n) != memo.end()) {
        return memo[n];
    }
    memo[n] = fib(n - 1, memo) + fib(n - 2, memo);
    return memo[n];
}

long long grid_traveler(int r, int c, std::map<std::string, long long>& memo) {
    std::string key = std::to_string(r) + ',' + std::to_string(c);
    if (memo.find(key) != memo.end()) { return memo[key]; }
    if (r == 1 && c == 1) { return 1; }
    if (r == 0 || c == 0) { return 0; }
    memo[key] = grid_traveler(r - 1, c, memo) + grid_traveler(r, c - 1, memo);
    return memo[key];
}
