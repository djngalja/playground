/*
Dynamic programming complete freeCodeCamp tutorial
https://www.youtube.com/watch?v=oBt53YbR9Kk

Rewritten in modern C++ by Galina
June 2025
*/

#include <iostream>
#include <map>
#include <vector>
#include <string>

// Brute force
int fib(int);
long long grid_traveler(int, int);
bool can_sum(int, const std::vector<int>&);
bool how_sum(int, const std::vector<int>&, std::vector<int>&);
std::pair<bool, std::vector<int>> best_sum(int, const std::vector<int>&);
bool can_construct(const std::string&, const std::vector<std::string>&);
int count_construct(const std::string&, const std::vector<std::string>&);
// Memoization
int fib(int, std::map<int, int>&);
long long grid_traveler(int, int, std::map<std::string, long long>&);
bool can_sum(int, const std::vector<int>&, std::map<int, bool>&);
bool how_sum(int, const std::vector<int>&, std::vector<int>&, std::map<int, bool>&);
std::pair<bool, std::vector<int>> best_sum(int, const std::vector<int>&,
    std::map<int, std::pair<bool, std::vector<int>>>&);
bool can_construct(const std::string&, const std::vector<std::string>&,
    std::map<std::string, bool>&);
int count_construct(const std::string&, const std::vector<std::string>&,
    std::map<std::string, int>&);





int main() {
    std::map<std::string, int> memo;
    std::vector<std::string> words {"e", "ee", "eee", "eeee", "eeeee", "eeeeee"};
    auto res = count_construct("eeeeeeeeeeeeeeeeeeeeeeeeeeeeeef", words, memo);
    std::cout << res << '\n';

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

bool how_sum(int target, const std::vector<int>& nums, std::vector<int>& result) {
    if (target == 0) { return true; }
    if (target < 0) { return false; }
    for (int num : nums) {
        if (how_sum(target - num, nums, result)) {
            result.push_back(num);
            return true;
        }
    }
    return false;
}

std::pair<bool, std::vector<int>> best_sum(int target, const std::vector<int>& nums) {
    if (target == 0) {
        return std::make_pair(true, std::vector<int>());
    }
    if (target < 0) {
        return std::make_pair(false, std::vector<int>());
    }
    auto shortest = std::make_pair(false, std::vector<int>());
    for (int num : nums) {
        auto remainder = best_sum(target - num, nums);
        if (!remainder.first) { continue; }
        auto combination = remainder;
        combination.second.push_back(num);
        if (shortest.second.empty() || combination.second.size() < shortest.second.size()) {
            shortest = combination;
        }
    }
    return shortest;
}

bool can_construct(const std::string& target, const std::vector<std::string>& words) {
    if (target.empty()) { return true; }
    for (const auto& word : words) {
        if (target.find(word) != 0) { continue; }
        if (can_construct(target.substr(word.size()), words)) {
            return true;
        }
    }
    return false;
}

int count_construct(const std::string& target, const std::vector<std::string>& words) {
    if (target.empty()) { return 1; }
    int result {};
    for (const auto& word : words) {
        if (target.find(word) != 0) { continue; }
        result += count_construct(target.substr(word.size()), words);
    }
    return result;
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

bool how_sum(int target, const std::vector<int>& nums, std::vector<int>& result,
    std::map<int, bool>& memo) {
    if (target == 0) { return true; }
    if (target < 0) { return false; }
    if (memo.find(target) != memo.end()) {
        return memo[target];
    }
    for (int num : nums) {
        if (how_sum(target - num, nums, result, memo)) {
            result.push_back(num);
            memo[target] = true;
            return true;
        }
    }
    memo[target] = false;
    return false;
}

std::pair<bool, std::vector<int>> best_sum(int target, const std::vector<int>& nums,
    std::map<int, std::pair<bool, std::vector<int>>>& memo) {
    if (memo.find(target) != memo.end()) { return memo[target]; }
    if (target == 0) {
        return std::make_pair(true, std::vector<int>());
    }
    if (target < 0) {
        return std::make_pair(false, std::vector<int>());
    }
    auto shortest = std::make_pair(false, std::vector<int>());
    for (int num : nums) {
        auto remainder = best_sum(target - num, nums, memo);
        if (!remainder.first) { continue; }
        auto combination = remainder;
        combination.second.push_back(num);
        if (shortest.second.empty() || combination.second.size() < shortest.second.size()) {
            shortest = combination;
        }
    }
    memo[target] = shortest;
    return shortest;
}

bool can_construct(const std::string& target, const std::vector<std::string>& words,
    std::map<std::string, bool>& memo) {
    if (target.empty()) { return true; }
    if (memo.find(target) != memo.end()) { return memo[target]; }
    for (const auto& word : words) {
        if (target.find(word) != 0) { continue; }
        if (can_construct(target.substr(word.size()), words, memo)) {
            memo[target] = true;
            return true;
        }
    }
    memo[target] = false;
    return false;
}

int count_construct(const std::string& target, const std::vector<std::string>& words,
    std::map<std::string, int>& memo) {
    if (target.empty()) { return 1; }
    if (memo.find(target) != memo.end()) { return memo[target]; }
    int result {};
    for (const auto& word : words) {
        if (target.find(word) != 0) { continue; }
        result += count_construct(target.substr(word.size()), words, memo);
    }
    memo[target] = result;
    return result;
}
