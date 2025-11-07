#include <iostream>
#include <vector>

int main() {
    int N{};
    std::cin >> N;
    std::vector<int> vec(N + 1);
    vec[0] = 1;
    vec[1] = 1;
    vec[2] = 2;
    if (N > 2) {
        for (int i = 3; i <= N; ++i) {
            vec[i] = vec[i - 1] + vec[i - 2] + vec[i - 3];
        }
    }
    std::cout << vec[N];

    return 0;
}
