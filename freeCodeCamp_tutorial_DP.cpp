/*
Dynamic programming complete freeCodeCamp tutorial
https://www.youtube.com/watch?v=oBt53YbR9Kk

The original JavaScript code rewritten in C++11 by Galina
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
std::vector<std::vector<std::string>> all_construct(const std::string&,
    const std::vector<std::string>&);
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
std::vector<std::vector<std::string>> all_construct(const std::string&,
    const std::vector<std::string>&,
    std::map<std::string, std::vector<std::vector<std::string>>>&);
// Tabulation
long fib_tab(int);
long grid_traveler_tab(int r, int c);
bool can_sum_tab(int, const std::vector<int>&);
std::vector<int> how_sum_tab(int, const std::vector<int>&);
std::vector<int> best_sum_tab(int, const std::vector<int>&);
bool can_construct_tab(const std::string&, const std::vector<std::string>&);
int count_construct_tab(const std::string&, const std::vector<std::string>&);
std::vector<std::vector<std::string>> all_construct_tab(const std::string&, const std::vector<std::string>&);

// Utility function
void print_res(const std::vector<std::vector<std::string>>& result) {
    if (result.empty()) {
        std::cout << "null";
    }
    for (const auto& vec : result) {
        for (const auto& str : vec) {
            std::cout << str << ' ';
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}




int main() {
    print_res(all_construct_tab("abcdef", {"ab", "abc", "cd", "def", "abcd", "ef", "c"}));
    print_res(all_construct_tab("purple", {"purp", "p", "ur", "le", "purpl"}));
    print_res(all_construct_tab("skateboard", {"bo", "rd", "ate", "t", "ska", "sk", "boar"}));
    print_res(all_construct_tab("aaaaaaaaaaaz", {"a", "aa", "aaa", "aaaa", "aaaaa"}));
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
        auto res = best_sum(target - num, nums);
        if (!res.first) { continue; }
        res.second.push_back(num);
        if (shortest.second.empty() || res.second.size() < shortest.second.size()) {
            shortest = res;
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

std::vector<std::vector<std::string>> all_construct(const std::string& target,
    const std::vector<std::string>& words) {
    if (target.empty()) { return {{}}; }
    std::vector<std::vector<std::string>> result;
    for (const auto& word : words) {
        if (target.find(word) != 0) { continue; }
        auto res = all_construct(target.substr(word.size()), words);
        for (auto& vec : res) {
            vec.insert(vec.begin(), word);
            result.push_back(vec);
        }
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
        auto res = best_sum(target - num, nums, memo);
        if (!res.first) { continue; }
        res.second.push_back(num);
        if (shortest.second.empty() || res.second.size() < shortest.second.size()) {
            shortest = res;
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

std::vector<std::vector<std::string>> all_construct(const std::string& target,
    const std::vector<std::string>& words,
    std::map<std::string, std::vector<std::vector<std::string>>>& memo) {
    if (memo.find(target) != memo.end()) { return memo[target]; }
    if (target.empty()) { return {{}}; }
    std::vector<std::vector<std::string>> result;
    for (const auto& word : words) {
        if (target.find(word) != 0) { continue; }
        auto res = all_construct(target.substr(word.size()), words, memo);
        for (auto& vec : res) {
            vec.insert(vec.begin(), word);
            result.push_back(vec);
        }
    }
    memo[target] = result;
    return result;
}


// Tabulation
long fib_tab(int n) {
    std::vector<long> table(n + 2, 0);
    table.at(1) = 1;
    for (int i = 0; i != n; ++i) {
        table.at(i + 1) += table.at(i);
        table.at(i + 2) += table.at(i);
    }
    return table.at(n);
}

long grid_traveler_tab(int r, int c) {
    std::vector<std::vector<long>> table(r + 1, std::vector<long>(c + 1));
    table[1][1] = 1;
    for (int i = 0; i <= r; ++i) {
        for (int j = 0; j <= c; ++j) {
            if (i + 1 <= r) {
                table[i + 1][j] += table[i][j];
            }
            if (j + 1 <= c) {
                table[i][j + 1] += table[i][j];
            }
        }
    }
    return table[r][c];
}

bool can_sum_tab(int target, const std::vector<int>& nums) {
    std::vector<bool> table(target + 1);
    table[0] = true;
    for (int i = 0; i <= target; ++i) {
        if (!table[i]) { continue; }
        for (int num : nums) {
            if (i + num > target) { continue; }
            table[i + num] = true;
        }
    }
    return table[target];
}

std::vector<int> how_sum_tab(int target, const std::vector<int>& nums) {
    std::vector<std::vector<int>> table(target + 1);
    for (int i = 0; i <= target; ++i) {
        // Skip i = 0
        if (i && table[i].empty()) { continue; }
        for (int num : nums) {
            if (i + num > target) { continue; }
            table[i + num] = table[i];
            table[i + num].push_back(num);
        }
    }
    return table[target];
}

std::vector<int> best_sum_tab(int target, const std::vector<int>& nums) {
    std::vector<std::vector<int>> table(target + 1);
    for (int i = 0; i <= target; ++i) {
        // Skip all empty elements except the 1st one
        if (i && table[i].empty()) { continue; }
        for (int num : nums) {
            if (num + i > target) { continue; }
            auto new_val = table[i];
            new_val.push_back(num);
            if (table[num + i].empty() || new_val.size() < table[num + i].size()) {
                table[num + i] = new_val;
            }
        }
    }
    return table[target];
}

bool can_construct_tab(const std::string& target, const std::vector<std::string>& words) {
    std::vector<bool> table(target.size() + 1);
    table[0] = true;
    for (std::size_t i = 0; i <= target.size(); ++i) {
        if (!table[i]) { continue; }
        for (const auto& word : words) {
            if (i + word.size() <= target.size() && target.substr(i, word.size()) == word) {
                table[i + word.size()] = true;
            }
        }
    }
    return table[target.size()];
}

int count_construct_tab(const std::string& target, const std::vector<std::string>& words) {
    std::vector<int> table(target.size() + 1);
    table[0] = 1;
    for (std::size_t i = 0; i <= target.size(); ++i) {
        if (!table[i]) { continue; }
        for (const auto& word : words) {
            if (i + word.size() <= target.size() && target.substr(i, word.size()) == word) {
                table[i + word.size()] += table[i];
            }
        }
    }
    return table[target.size()];
}

std::vector<std::vector<std::string>> all_construct_tab(const std::string& target, const std::vector<std::string>& words) {
    std::vector<std::vector<std::vector<std::string>>> table(target.size() + 1);
    table[0] = {{}};
    for (std::size_t i = 0; i <= target.size(); ++i) {
        if (table[i].empty()) { continue; }
        for (const auto& word : words) {
            if (i + word.size() <= target.size() && target.substr(i, word.size()) == word) {
                std::vector<std::vector<std::string>> new_vals(table[i]);
                for (auto& vec : new_vals) {
                    vec.push_back(word);
                }
                table[i + word.size()].insert(table[i + word.size()].end(), new_vals.begin(), new_vals.end());
            }
        }
    }
    return table[target.size()];
}
