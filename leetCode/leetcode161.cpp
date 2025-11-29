/* 161. One Edit Distance
Given two strings s and t, return true if they are both one edit distance apart, otherwise return false.

A string s is said to be one distance apart from a string t if you can:
    - Insert exactly one character into s to get t.
    - Delete exactly one character from s to get t.
    - Replace exactly one character of s with a different character to get t.

Example 1:

Input: s = "ab", t = "acb"
Output: true
Explanation: We can insert 'c' into s to get t.

Example 2:

Input: s = "", t = ""
Output: false
Explanation: We cannot get t from s by only one step.

Constraints:

    0 <= s.length, t.length <= 104
    s and t consist of lowercase letters, uppercase letters, and digits. */

#include <iostream>
#include <string>

bool one_edit_dist(const std::string& s, const std::string& t) {
    if (abs(s.size() - t.size()) > 1) { return false; }
    if (s.size() > t.size()) {
        for (size_t i = 0; i < t.size(); ++i) {
            if (s[i] != t[i]) {
                return t.substr(i) == s.substr(i + 1);
            }
        }
        return true;
    } else if (s.size() < t.size()) {
        for (size_t i = 0; i < s.size(); ++i) {
            if (s[i] != t[i]) {
                return s.substr(i) == t.substr(i + 1);
            }
        }
        return true;
    } else {
        for (size_t i = 0; i < t.size(); ++i) {
            if (s[i] != t[i]) {
                return s.substr(i + 1) == t.substr(i + 1);
            }
        }
    }
    return false;
}

int main() {
    std::cout << std::boolalpha << one_edit_dist("abc", "ab") << '\n'; // --> true
    std::cout << one_edit_dist("ab", "ab") << '\n'; // --> false
    std::cout << one_edit_dist("", "") << '\n'; // --> false
    std::cout << one_edit_dist("ab", "acb") << '\n'; // --> true
    return 0;
}
