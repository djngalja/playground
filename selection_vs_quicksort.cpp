// Selection sort vs. Quicksort

#include <iostream>
#include <vector>
#include <chrono>

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

void quicksort_rec(std::vector<int>& vec, int low, int high) {
    if ((vec.size() < 2) || (low >= high)) {
        return;
    }
    int pivot = vec[high];
    int index = low;
    for (int i=low; i<high; ++i) {
        if (vec[i] < pivot) {
            std::swap(vec[i], vec[index++]);
        }
    }
    std::swap(vec[high], vec[index]);
    quicksort_rec(vec, low, index-1);
    quicksort_rec(vec, index+1, high);
}

void quicksort(std::vector<int>& vec) {
    quicksort_rec(vec, 0, vec.size()-1);
}

void print_vec(const std::vector<int>& vec) {
    for (int i : vec) {
        std::cout << i << ' ';
    }
    std::cout << '\n';
}


int main() {
    std::vector<int> vec = {8, 23, 1, -5, -4, 25, 3, 5, 5, 67, 13, 13, 0, 17, 44, 8, -12, 34, 57, 12, 11, 17};
    auto vec_copy {vec}; // copy for quicksort
    print_vec(vec); // initial vector

    auto t0 = std::chrono::system_clock::now();
    selection_sort(vec);
    auto t1 = std::chrono::system_clock::now();
    std::cout << "\n\nSelection sort took "
        << std::chrono::duration_cast<std::chrono::nanoseconds>(t1 - t0).count() << "ns\n";


    t0 = std::chrono::system_clock::now();
    quicksort(vec_copy);
    t1 = std::chrono::system_clock::now();
    std::cout << "Quicksort took "
        << std::chrono::duration_cast<std::chrono::nanoseconds>(t1 - t0).count() << "ns\n\n";

    print_vec(vec_copy); // sorted vector

    return 0;
}
