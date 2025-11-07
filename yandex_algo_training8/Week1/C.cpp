#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

int main() {
    std::string pswd;
    std::cin >> pswd;

    std::unordered_map<char, std::vector<int>> data;
    for (size_t i = 0; i < pswd.size(); ++i) {
        data[pswd[i]].push_back(i);
    }

    long res{1};

    if (data.size() > 1) {
        for (const auto& letter : data) {
            int contribution{};
            size_t freq{letter.second.size()};
            for (int pos : letter.second) {
                contribution += pos + freq--;
            }
        res += pswd.size() * letter.second.size() - contribution;
        }
    }
    
    std::cout << res;

	return 0;
}
