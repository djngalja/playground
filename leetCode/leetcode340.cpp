/*340. Longest Substring with At Most K Distinct Characters

Given a string, find the length of the longest substring T that contains at most k distinct characters.

Example 1:

Input: s = "eceba", k = 2
Output: 3
Explanation: T is "ece" which its length is 3.

Example 2:

Input: s = "aa", k = 1
Output: 2
Explanation: T is "aa" which its length is 2.
*/

#include <iostream>
#include <string>
#include <unordered_map>

int main() {
    std::string s = "eceba";
    size_t k = 2; 

    int sz = s.size();
    int n_max{}; // Result
    int pos_max{};

    int left{};
    int right{};
    std::unordered_map<char, int> cnt;
    for (int i = 0; i < sz; ++i) {
        ++cnt[s[i]];
        ++right;
        while (cnt.size() > k) {
            --cnt[s[left]];
            if (cnt[s[left]] == 0) { cnt.erase(s[left]); }
            ++left;
        }
        if (right - left > n_max) {
            n_max = right - left;
            pos_max = left;
        }
    }

    std::cout << s.substr(pos_max, n_max);

    return 0;
}
