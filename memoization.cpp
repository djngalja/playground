#include <iostream>
#include <stdexcept>
#include <map>
#include <chrono>
#include <functional>

int fib(int n) {
    if (n < 0) {
        throw std::invalid_argument("n is not expected to be negative");
    }
    if (n == 0) { return 0; }
    if (n == 1) { return 1; }
    return fib(n - 1) + fib(n - 2);
}


// Using memoization
int fib_mem_rec(int n, std::map<int, int>& memo) {
    if (n == 0) { return 0; }
    if (n == 1) { return 1; }
    if (memo.find(n) != memo.end()) {
        return memo[n];
    }
    memo[n] = fib_mem_rec(n - 1, memo) + fib_mem_rec(n - 2, memo);
    return memo[n];
}

int fib_mem(int n) {
    if (n < 0) {
        throw std::invalid_argument("n is not expected to be negative");
    }
    std::map<int, int> memo;
    return fib_mem_rec(n, memo);
}


void measure(int n, std::function<int(int)> f) {
    auto t0 = std::chrono::system_clock::now();
    f(n);
    auto t1 = std::chrono::system_clock::now();
    std::cout << "the duration is " << std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0).count() << " microseconds.\n";
}



int main() {
    int n = 45;
    std::cout << 'F' << n << " = " << fib_mem(n) << '\n';
    std::cout << "Using recursion: ";
    measure(n, &fib);
    std::cout << "Optimization using memoization: ";
    measure(n, &fib_mem);
    return 0;
}
