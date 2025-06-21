// PALINDROME
#include <iostream>
#include <string>
#include <vector>
#include <functional>

void test(std::function<bool(const std::string&)>);

// Without recursion
bool is_palindrome(const std::string& str) {
    int left {};
    int right = str.size() - 1;
    while (left < right) {
        if (str[left] != str[right]) {
            return false;
        }
        left++;
        right--;
    }
    return true;
}

// Using recursion
bool is_palindrome_rec(const std::string& str) {
    if (str.empty() || str.size() == 1) { return true; }
    if (str.front() == str.back()) {
        return is_palindrome_rec(str.substr(1, str.size() - 2));
    }
    return false;
}




int main(){
    test(&is_palindrome);
    test(&is_palindrome_rec);
    return 0;
}




void test(std::function<bool(const std::string&)> f) {
    std::vector<std::string> vec {"racecar", "madam", "hello"};
    for (const auto& str : vec) {
        std::cout << str << " --> " << std::boolalpha << f(str) << '\n';
    }
    std::cout << '\n';
}
