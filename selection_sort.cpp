// Selection sort

#include <iostream>
#include <vector>

auto smallest_it(const std::vector<int>& vec) {
    int smallest = vec.front();
    auto it = vec.begin();
    for (auto i=vec.begin()+1; i!=vec.end(); ++i) {
        if (*i < smallest) {
            smallest = *i;
            it = i;
        }
    }
    return it;
}

std::vector<int> selection_sort(std::vector<int>& vec) {
    std::vector<int> new_vec;
    while (vec.size()) {
        auto it = smallest_it(vec);
        new_vec.push_back(*it);
        vec.erase(it);
    }
    return new_vec;
}

void test_selection_sort() {
    std::vector<int> vec = {3, 5, 1, 8, 1, 4, -1, 0};
    std::vector<int> vec_sorted = {-1, 0, 1, 1, 3, 4, 5, 8};
    if (vec_sorted != selection_sort(vec)) {
        std::cout << "Test failed\n";
    } else { std::cout << "Success\n"; }
}

int main() {
    test_selection_sort();
    return 0;
}
