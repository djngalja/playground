#include <iostream>
#include <cmath>

int main() {
    int x{};
    int y{};
    int f{};
    int g{};
    std::cin >> x >> y >> f >> g; 

    long res{}; 
    long dist_x = abs(x - f);
    long dist_y = abs(y - g);

    if (dist_x + dist_y) {
        if (dist_x == 0 || dist_y == 0) {
            res = (dist_x + dist_y - 1) * 3;
        } else {
            res = (dist_x + dist_y - 2) * 3 + 1;
        }
    }
    
    std::cout << res;

    return 0;
}
