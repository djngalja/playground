// Selection sort vs. Quicksort

#include <iostream>
#include <vector>
#include <chrono>

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

void quicksort(std::vector<int>& vec, int low, int high) {
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
    quicksort(vec, low, index-1);
    quicksort(vec, index+1, high);
}

void print_vec(const std::vector<int>& vec) {
    for (int i : vec) {
        std::cout << i << ' ';
    }
    std::cout << '\n';
}


int main() {
    std::vector<int> vec = {8, 23, 1, -5, -4, 25, 3, 5, 5, 67, 13, 13, 0, 17, 44, 8, -12, 34, 57, 12, 11, 17};
    auto vec1 {vec}; // copy for quicksort
    print_vec(vec); // initial vector

    auto t0 = std::chrono::system_clock::now();
    auto sorted = selection_sort(vec);
    auto t1 = std::chrono::system_clock::now();
    std::cout << "\n\nSelection sort took "
        << std::chrono::duration_cast<std::chrono::nanoseconds>(t1 - t0).count() << "ns\n";


    t0 = std::chrono::system_clock::now();
    quicksort(vec1, 0, vec1.size()-1);
    t1 = std::chrono::system_clock::now();
    std::cout << "Quicksort took "
        << std::chrono::duration_cast<std::chrono::nanoseconds>(t1 - t0).count() << "ns\n\n";

    print_vec(vec1); // sorted vector

    return 0;
}
