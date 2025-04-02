// Selection sort

#include <iostream>
#include <vector>

void selection_sort(std::vector<int>& vec) {
    for (std::size_t i=0; i<vec.size()-1; ++i) {
        std::size_t smallest_index {i};
        for (std::size_t j=i+1; j<vec.size(); ++j) {
            if (vec[j] < vec[smallest_index]) {
                smallest_index = j;
            }
        }
        std::swap(vec[i], vec[smallest_index]);
    }
}

void test_selection_sort() {
    std::vector<int> vec = {3, 5, 1, 8, 1, 4, -1, 0};
    selection_sort(vec);
    std::vector<int> vec_sorted = {-1, 0, 1, 1, 3, 4, 5, 8};
    if (vec_sorted != vec) {
        std::cout << "Test failed\n";
    } else { std::cout << "Success\n"; }
}


int main() {
    test_selection_sort();
    return 0;
}
