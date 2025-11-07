#include <iostream>
#include <deque>
#include <unordered_set>

int main() {
    int n{};
    int k{};
    std::cin >> n >> k;

    if (n == k) {
        for (int i = 0, num = 0; i < n; ++i) {
            std::cin >> num;
            std::cout << num << ' ';
        }
    } else {
        std::deque<int> d;
        std::unordered_set<int> s;

        for (int i = 0, num = 0; i < n; ++i) {
            std::cin >> num;
            auto res = s.insert(num);
            if (res.second) {
                d.push_front(num);
            } else {
                d.push_back(num);
            }
        }
        for (int i = 0; i < k; ++i) {
            std::cout << d[i] << ' ';
        }
    }

	return 0;
}

