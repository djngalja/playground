/*
Dynamic programming complete freeCodeCamp tutorial
https://www.youtube.com/watch?v=oBt53YbR9Kk

Rewritten in modern C++ by Galina
June 2025
*/

#include <iostream>
#include <map>
#include <vector>

// Brute force
int fib(int);
long long grid_traveler(int, int);
bool can_sum(int, const std::vector<int>&);
// Memoization
int fib(int, std::map<int, int>&);
long long grid_traveler(int, int, std::map<std::string, long long>&);
bool can_sum(int, const std::vector<int>&, std::map<int, bool>&);



int main() {
    std::map<int, bool> memo;
    std::vector<int> nums {7, 14};
    std::cout << can_sum(300, nums, memo);


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

bool can_sum(int target, const std::vector<int>& nums) {
    if (target == 0) { return true; }
    if (target < 0) { return false; }
    for (int num : nums) {
        if (can_sum(target - num, nums)) {
            return true;
        }
    }
    return false;
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

bool can_sum(int target, const std::vector<int>& nums, std::map<int, bool>& memo) {
    if (target == 0) { return true; }
    if (target < 0) { return false; }
    if (memo.find(target) != memo.end()) { return memo[target]; }
    for (int num : nums) {
        if (can_sum(target - num, nums, memo)) {
            memo[target] = true;
            return true;
        }
    }
    memo[target] = false;
    return false;
}
