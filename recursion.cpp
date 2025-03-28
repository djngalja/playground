// Recursion

#include <iostream>
#include <vector>
#include <algorithm>

void print_bs_res(const std::vector<int>&);
void print_vec(const std::vector<int>&);

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

int binary_s(const std::vector<int>& vec, int target, int min_val, int max_val) {
    if (min_val <= max_val) {
        int mid_val = (min_val + max_val) / 2;
        if (vec[mid_val] == target) {
            return mid_val;
        }
        if (vec[mid_val] < target) {
            return binary_s(vec, target, mid_val+1, max_val);
        }
        return binary_s(vec, target, min_val, mid_val-1);
    }
    return -1;
}



int main(){
    std::vector<int> vec = {1, 4, 2, 6, -1, 0, 3}; // sum == 15
    std::cout << "Vector: ";
    print_vec(vec);
    std::cout << "\n\nsum = " << sum(vec, vec.size())
        << "\nmax_num = " << find_max(vec, vec.size())
        << "\nmin_num = " << find_min(vec, vec.size());
    std::sort(vec.begin(), vec.end());
    std::cout << "\n\nSorted vector: ";
    print_vec(vec);
    print_bs_res(vec);
    return 0;
}


void print_vec(const std::vector<int>& vec) {
    for (int i : vec) { std::cout << i << ' '; }
}

void print_bs_res(const std::vector<int>& vec) {
    std::cout << "\n\nBinary search results: \n\n";
    std::vector<int> test = { -1, 6, 2, 7, -2};
    for (int i : test) {
        int pos = binary_s(vec, i, 0, vec.size());
        if (pos == -1) {
            std::cout << i << " not found\n";
        } else {
            std::cout << i << " found at index " << pos << '\n';
        }
    }
}
