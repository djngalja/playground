#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>

int main() {
    std::string str;
    std::cin >> str;
    size_t len = str.size();

    std::vector<int> left(len + 1);
    std::vector<int> right(len + 1);

    left[0] = 0;
    right[0] = INT_MAX - 2;

    for (size_t i = 1; i <= len; ++i) {
        int path1 = (str[i - 1] != 'R') ? left[i - 1] + 1 : left[i - 1];
        int path2 = (str[i - 1] != 'R') ? right[i - 1] + 2 : right[i - 1] + 1;
        left[i] = std::min(path1, path2);
        
        path1 = (str[i - 1] != 'L') ? right[i - 1] + 1 : right[i - 1];
        path2 = (str[i - 1] != 'L') ? left[i - 1] + 2 : left[i - 1] + 1;
        right[i] = std::min(path1, path2);
    }

    std::cout << std::min(left[len] + 1, right[len]);

    return 0;
}
