#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

int main() {
    int n{};
    int m{};
    std::cin >> n >> m; 

    std::vector<std::string> table;
    std::unordered_map<int, std::vector<int>> max_rows;
    int max_sum{-m};

    for (int i = 0; i < n; ++i) {
        std::string temp;
        std::cin >> temp;
        table.push_back(temp);
        int sum{};
        for (char ch : temp) {
            if (ch == '-') {
                sum -= 1;
            } else {
                sum += 1;
            }
        }
        if (sum > max_sum) {
            max_sum  = sum;
        }
        max_rows[sum].push_back(i); 
    }

    std::unordered_map<int, std::vector<int>> min_columns;
    int min_sum{n};

    for (int i = 0; i < m; ++i) {
        int sum{};
        for (int j = 0; j < n; ++j) {
            if (table[j][i] == '+') {
                sum += 1;
            } else {
                sum -= 1;
            }
        }
        if (sum < min_sum) {
            min_sum = sum;
        }
        min_columns[sum].push_back(i);
    }

    bool no_q{};
    for (int id_x : max_rows[max_sum]) {
        for (int id_y : min_columns[min_sum]) {
            if (table[id_x][id_y] != '?') {
                no_q = true;
                break;
            } 
        }
    }

    int res = no_q ? max_sum - min_sum : max_sum - min_sum - 2;

    std::cout << res;

	return 0;
}
