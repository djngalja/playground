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

Constraints:
1 <= s.length <= 5 * 104
0 <= k <= 50
*/

#include <iostream>
#include <string>
#include <unordered_map>

int lengthOfLongestSubstringKDistinct(std::string s, int k) {
    int res{};
    int left{};
    std::unordered_map<char, int> cnt;
    for (int right = 0; right < s.size(); ++right) {
        ++cnt[s[right]];
        while (cnt.size() > k) {
            --cnt[s[left]];
            if (cnt[s[left]] == 0) { cnt.erase(s[left]); }
            ++left;
        }
        if (right - left + 1 > res) {
            res = right - left + 1;
        }
    }
    return res;
}

int main() {
    std::cout << lengthOfLongestSubstringKDistinct("eceba", 2);
    return 0;
}
