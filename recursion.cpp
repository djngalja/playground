// Recursion

#include <iostream>
#include <vector>

int sum(const std::vector<int>& vec, int len) {
    if (!len) { return 0; }
    return vec[len-1] + sum(vec, len-1);
}

int find_max(const std::vector<int>& vec, int len) {
    if (len == 2) {
        return vec[0] > vec[1] ? vec[0] : vec[1];
    }
    int max_num = find_max(vec, len-1);
    return vec[len-1] > max_num ? vec[len-1] : max_num;
}

int find_min(const std::vector<int>& vec, int len) {
    if (len == 2) {
        return vec[0] < vec[1] ? vec[0] : vec[1];
    }
    int min_num = find_min(vec, len-1);
    return vec[len-1] < min_num ? vec[len-1] : min_num;
}


int main(){
    std::vector<int> vec = {1, 4, 2, 6, -1, 0, 3}; // sum == 15
    std::cout << "Vector: ";
    for (int i : vec) { std::cout << i << ' '; }
    std::cout << "\n\nsum = " << sum(vec, vec.size());
    std::cout << "\nmax_num = " << find_max(vec, vec.size());
    std::cout << "\nmin_num = " << find_min(vec, vec.size()) << '\n';
    return 0;
}
