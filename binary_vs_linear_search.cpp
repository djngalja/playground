/*
Binary vs. linear search
C++11 code by Galina - 29/03/2025
*/

#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <functional>

void test();
int linear(const std::vector<int>&, int);
std::pair<int, int> binary(const std::vector<int>&, int);
bool get_input(int&);
void binary_vs_linear(const std::vector<int>&);
std::vector<int> get_vec();


int main() {
    //test();
    std::vector<int> vec = get_vec();
    std::sort(vec.begin(), vec.end());
    binary_vs_linear(vec);
    return 0;
}



std::vector<int> get_vec() {
    auto rand_int = std::bind(std::uniform_int_distribution<> {0, 500}, std::default_random_engine {});
    std::vector<int> vec;
    for (int i=0; i<550; ++i) { // The vector holds 550 elements between 0 and 500
        vec.push_back(rand_int());
    }
    return vec;
}

void binary_vs_linear(const std::vector<int>& vec) {
    int target {};
    if(get_input(target)) {
        auto res_b = binary(vec, target);
        if (res_b.first != -1) {
            std::cout << "\nYour number is " << target
                << ".\nIt took " << res_b.second << " step(s) to find it using binary search.\nIt took "
                << linear(vec, target) << " step(s) to find it using linear search.\n";
                return;
        }
        std::cout << "Number not found. Try again.\n\n";
    }
    binary_vs_linear(vec);
}

bool get_input(int& target) {
    std::cout << "Enter an integer between 0 and 500\n";
    if (int num; std::cin >> num) {
        if (num >= 0 && num <= 500) {
            target = num;
            return true;
        }
    }
    if (!std::cin) { // if not an integer
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cout << "Invalid input\n\n";
    return false;
}

/*
Returns a pair consisting of the position of 'target'
and the number of steps required to find it.
If 'target' is not found, the position is set to -1.
*/
std::pair<int, int> binary(const std::vector<int>& data, int target) {
    std::size_t min_val = 0;
    std::size_t max_val = data.size() - 1;
    int cnt {};
    while (min_val <= max_val) {
        cnt++;
        std::size_t mid_val = (min_val + max_val)/ 2;
        if (data[mid_val] == target) {
            return {mid_val, cnt};
        } else if (data[mid_val] < target) {
            min_val = mid_val + 1;
        } else {
            max_val = mid_val - 1;
        }
    }
    return {-1, cnt};
}

int linear(const std::vector<int>& data, int target) { // Returns the number of steps required to find 'target'
    for (std::size_t i=0; i!=data.size()-1; ++i) {
        if (data[i] == target) {
            return i + 1;
        }
    }
    return data.size();
}

void test() {
    std::vector<int> vec = {0, 3, 5, 7, 13, 17, 25, 30, 33, 39, 45, 50};
    auto res = binary(vec, 5);
    if (!(res.first == 2 && res.second == 2)) {
        std::cout << "Test case #1 failed\n";
    }
    res = binary(vec, 2);
    if (!(res.first == -1 && res.second == 4)) {
        std::cout << "Test case #2 failed\n";
    }
}
