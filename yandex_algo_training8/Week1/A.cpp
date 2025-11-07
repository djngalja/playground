#include <iostream>

int main() {
    int n{};
    std::cin >> n;

    int sum_v{};
    int sum_m{};
    int min_v{1000};
    int max_m{1};

    for (int i = 0; i < n; ++i) {
        int num{};
        std::cin >> num;
        if (i % 2 == 0) {
            sum_v += num;
            if (num < min_v) {
                min_v = num;
            }
        } else {
            sum_m += num;
            if (num > max_m) {
                max_m = num;
            }
        }
    }
    if (max_m > min_v) {
        std::cout << sum_v - sum_m + 2 * max_m - 2 * min_v;
    } else {
        std::cout << sum_v - sum_m;
    }
    
	return 0;
}
