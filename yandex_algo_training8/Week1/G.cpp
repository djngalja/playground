#include <iostream>
#include <string>
#include <vector>

int main() {
    int n{};
    int m{};
    std::cin >> n >> m; 

    int res{};

    std::vector<std::string> field;
    for (int i = 0; i < n; ++i) {
        std::string temp;
        std::cin >> temp;
        if (!res && m >= 5 && (temp.find("XXXXX") != std::string::npos || temp.find("OOOOO") != std::string::npos)) {
            res = 1;
        }
        field.push_back(temp);
    }
    if (!res) {
        for (int i = 0; i <= n - 5; ++i) {
            if (res) { break; }
            for (int j = 0; j < m; ++j) {
                if (field[i][j] == '.') {
                    continue;
                }
                // vert
                if (field[i][j] == field[i + 1][j] && field[i][j] == field[i + 2][j] 
                    && field[i][j] == field[i + 3][j] && field[i][j] == field[i + 4][j]) {
                        res = 1;
                        break;
                }
                // diag 1
                if (j >= 4 && field[i][j] == field[i + 1][j - 1] 
                    && field[i][j] == field[i + 2][j - 2] && field[i][j] == field[i + 3][j - 3] 
                    && field[i][j] == field[i + 4][j - 4]) {
                        res = 1;
                        break;
                }
                // diag 2
                if (m - j >= 5 && field[i][j] == field[i + 1][j + 1] 
                    && field[i][j] == field[i + 2][j + 2] && field[i][j] == field[i + 3][j + 3] 
                    && field[i][j] == field[i + 4][j + 4]) {
                        res = 1;
                        break;
                }
            }
        }
    }

    if (res) {
        std::cout << "Yes";
    } else {
        std::cout << "No";
    }

	return 0;
}

