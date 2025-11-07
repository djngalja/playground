#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

int main() {
    int n{};
    int m{};
    std::cin >> n >> m; 

    std::string word;
    std::cin >> word;

    std::unordered_map<std::string, std::vector<int>> substr;
    for (int i = 0; i < m; ++i) {
        std::string temp;
        std::cin >> temp;
        substr[temp].push_back(i + 1);
    }

    int k = n / m;

    for (int i = 0; i < m; ++i) {
        std::string sub = word.substr(i * k, k);
        std::cout << substr[sub].back() << ' ';
        substr[sub].pop_back();
    }
}
