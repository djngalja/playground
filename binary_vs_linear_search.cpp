/*
Binary vs. linear search
C++11 code by Galina - 24/03/2025
*/

#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

void test();
std::pair<int, int> linear(const std::vector<int>&, int);
std::pair<int, int> binary(const std::vector<int>&, int);
int get_input();
std::vector<int> get_data();
void binary_vs_linear();


int main() {
    //test();
    binary_vs_linear();
    return 0;
}


void binary_vs_linear() {
    std::vector<int> data = get_data();
    std::sort(data.begin(), data.end());
    int target = get_input();
    auto res_b = binary(data, target);
    if (res_b.first == -1) {
        std::cout << "Number not found. Try again.\n";
        binary_vs_linear();
    } else {
        auto res_l = linear(data, target);
        std::cout << "\nYour number is " << target
            << ".\nIt took " << res_b.second << " step(s) to find it using binary search.\nIt took "
            << res_l.second << " step(s) to find it using linear search.\n";
    }
}

std::vector<int> get_data() {
    std::default_random_engine eng {};
    std::uniform_int_distribution<int> dist {0, 1000};
    std::vector<int> data;
    for (std::size_t i=0; i<1000; ++i) {
        data.push_back(dist(eng));
    }
    return data;
}

int get_input() {
    int target {};
    std::cout << "Enter an integer between 0 and 1000\n";
    std::cin >> target;
    if (target < 0 || target > 1000) {
        std::cout << "Invalid input\n";
        target = get_input();
    }
    return target;

}

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

std::pair<int, int> linear(const std::vector<int>& data, int target) {
    for (std::size_t i=0; i!=data.size()-1; ++i) {
        if (data[i] == target) {
            return {i, i + 1};
        }
    }
    return {-1, data.size()};
}


void test() {
    std::vector<int> vec = {0, 3, 5, 7, 13, 17, 25, 30, 33, 39, 45, 50};
    auto res = binary(vec, 5);
    if (!(res.first == 2 && res.second == 2)) {
        std::cout << "Binary search failed\n";
    }
    res = binary(vec, 2);
    if (!(res.first == -1 && res.second == 4)) {
        std::cout << "Binary search failed\n";
    }
    res = linear(vec, 5);
    if (!(res.first == 2 && res.second == 3)) {
        std::cout << "Linear search failed\n";
    }
    res = linear(vec, 2);
    if (!(res.first == -1 && res.second == 12)) {
        std::cout << "Linear search failed\n";
    }
}
