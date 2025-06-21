// REVERSE STRING

#include <iostream>
#include <string>

// Without creating a new string
void reverse_str(std::string& str) {
    int left {};
    int right = str.size() - 1;
    while (left < right) {
        std::swap(str[left], str[right]);
        left++;
        right--;
    }
}

// Using recursion
std::string reverse_str_rec(const std::string& str) {
    if (str.empty()) { return {}; }
    return reverse_str_rec(str.substr(1)) + str[0];
}

// Reverse iterators
std::string reverse_str_it(const std::string& str) {
    return std::string(str.rbegin(), str.rend());
}


int main(){
    std::string str {"Hello"};
    reverse_str(str);
    std::cout << str << '\n';
    std::cout << reverse_str_rec(str) << '\n';
    std::cout << reverse_str_it(str) << '\n';
    return 0;
}
